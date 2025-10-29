/*************************************************************************
		ANALOG
    Author:   <sergio.salazar.santos@gmail.com>
    License:  GNU GPL
    Hardware: ATmega32U4
    Date:     03/12/2023 (edited)
*************************************************************************/
#include "atmega32U4.h"
#include "atmega32U4_analog.h"
#include <stdarg.h>
#include <avr/io.h>    // for DIDR0 etc, if your dev() wrapper doesn't expose them

#ifndef GLOBAL_INTERRUPT_ENABLE
    #define GLOBAL_INTERRUPT_ENABLE 7
#endif

#define MAX_CHANNEL 8

#if defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__)
    #define MUX_MASK 15
    #define ANALOG_INTERRUPT ADC_vect
#else
    #error "Not ATmega32U4"
#endif

/* --- fixed types --- */
static volatile uint16_t ADC_VALUE[MAX_CHANNEL];
static volatile uint8_t  ADC_CHANNEL_LIST[MAX_CHANNEL];
static volatile uint8_t  ADC_N_CHANNEL;
static volatile uint8_t  ADC_SELECT_CHANNEL;

/* averaging */
static volatile uint32_t adc_accumulator;   // larger to avoid overflow
static volatile uint8_t  adc_n_sample_count; // counts collected samples

/* prototype */
int ANALOG_read(int selection);


/* Helper: start an ADC conversion (sets ADSC) */
static inline void adc_start_conversion(void) {
    dev()->adc->adcsra.var |= (1 << ADSC);
}

/* Initialize */
ANALOG ANALOGenable(uint8_t Vreff, uint8_t Divfactor, int n_channel, ...)
{
    va_list list;
    uint8_t savedSREG = dev()->cpu->sreg.var;

    /* disable global interrupts while we setup */
    dev()->cpu->sreg.var &= ~(1 << GLOBAL_INTERRUPT_ENABLE);

    /* bounds check */
    if (n_channel <= 0) n_channel = 1;
    if (n_channel > MAX_CHANNEL) n_channel = MAX_CHANNEL;

    ADC_N_CHANNEL = (uint8_t)n_channel;
    ADC_SELECT_CHANNEL = 0;
    adc_n_sample_count = 0;
    adc_accumulator = 0;

    va_start(list, n_channel);
    for (int i = 0; i < ADC_N_CHANNEL; ++i) {
        int ch = va_arg(list, int);
        if (ch < 0) ch = 0;
        /* store only low 8 bits */
        ADC_CHANNEL_LIST[i] = (uint8_t)ch;
    }
    va_end(list);

    ANALOG analog;
    analog.read = ANALOG_read;

    /* Configure reference (ADMUX REFS bits) */
    dev()->adc->admux.var &= ~(3 << REFS0);
    switch (Vreff) {
        case 1: dev()->adc->admux.var |= (1 << REFS0); analog.par.VREFF = 1; break; // AVcc
        case 3: dev()->adc->admux.var |= (3 << REFS0); analog.par.VREFF = 3; break; // internal
        case 0:
        default: analog.par.VREFF = 0; break; // AREF
    }

    /* Right adjust */
    dev()->adc->admux.var &= ~(1 << ADLAR);

    /* Disable digital input buffers on ADC pins to reduce noise */
#ifdef DIDR0
    /* If you only use ADC0..ADC7, disabling all is fine. Adjust if needed. */
    DIDR0 = 0xFF;
#endif

    /* Set initial channel in ADMUX (low bits) */
    dev()->adc->admux.var &= ~MUX_MASK;
    dev()->adc->admux.var |= (ADC_CHANNEL_LIST[ADC_SELECT_CHANNEL] & MUX_MASK);

    /* Enable ADC, clear ADATE (we'll use ISR-driven repeated conversions), enable interrupt */
    dev()->adc->adcsra.var |= (1 << ADEN);
    dev()->adc->adcsra.var &= ~(1 << ADATE);
    dev()->adc->adcsrb.var &= ~(7 << ADTS0);
    dev()->adc->adcsra.var |= (1 << ADIE);

    /* set prescaler */
    dev()->adc->adcsra.var &= ~(7 << ADPS0);
    switch (Divfactor) {
        case 2:  dev()->adc->adcsra.var |= (1 << ADPS0); analog.par.DIVISION_FACTOR = 2;  break;
        case 4:  dev()->adc->adcsra.var |= (1 << ADPS1); analog.par.DIVISION_FACTOR = 4;  break;
        case 8:  dev()->adc->adcsra.var |= (1 << ADPS1) | (1 << ADPS0); analog.par.DIVISION_FACTOR = 8;  break;
        case 16: dev()->adc->adcsra.var |= (1 << ADPS2); analog.par.DIVISION_FACTOR = 16; break;
        case 32: dev()->adc->adcsra.var |= (1 << ADPS2) | (1 << ADPS0); analog.par.DIVISION_FACTOR = 32; break;
        case 64: dev()->adc->adcsra.var |= (1 << ADPS2) | (1 << ADPS1); analog.par.DIVISION_FACTOR = 64; break;
        case 128:
        default: dev()->adc->adcsra.var |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); analog.par.DIVISION_FACTOR = 128; break;
    }

    /* restore SREG exactly as it was (do not forcibly enable interrupts) */
    dev()->cpu->sreg.var = savedSREG;

    /* Start the first conversion */
    adc_start_conversion();

#ifdef _ANALOG_MODULE_
    dev()->adc.run = analog;
#endif

    return analog;
}


/* Safely read a 16-bit ADC_VALUE (atomic) */
int ANALOG_read(int selection)
{
    if (selection < 0 || selection >= ADC_N_CHANNEL) return 0;

    /* make atomic copy of the 16-bit value */
    uint8_t sreg = dev()->cpu->sreg.var;
    dev()->cpu->sreg.var &= ~(1 << GLOBAL_INTERRUPT_ENABLE);

    uint16_t v = ADC_VALUE[selection];

    dev()->cpu->sreg.var = sreg;
    return (int)v;
}


/* ISR: collect sample, average, advance channel, start next conversion */
ISR(ANALOG_INTERRUPT)
{
    uint16_t sample = 0;
    sample = (uint16_t)ADCL;
    sample |= ((uint16_t)ADCH << 8);

    /* accumulate */
    adc_accumulator += sample;
    adc_n_sample_count++;

    if (adc_n_sample_count >= (1u << ADC_NUMBER_SAMPLE)) {
        /* compute average */
        uint16_t averaged = (uint16_t)(adc_accumulator >> ADC_NUMBER_SAMPLE);
        ADC_VALUE[ADC_SELECT_CHANNEL] = averaged;

        /* reset */
        adc_accumulator = 0;
        adc_n_sample_count = 0;

        /* advance channel index (correct wrap) */
        if (ADC_SELECT_CHANNEL < (ADC_N_CHANNEL - 1))
            ADC_SELECT_CHANNEL++;
        else
            ADC_SELECT_CHANNEL = 0;

        /* program next channel into ADMUX */
        dev()->adc->admux.var &= ~MUX_MASK;
        dev()->adc->admux.var |= (ADC_CHANNEL_LIST[ADC_SELECT_CHANNEL] & MUX_MASK);
    }

    /* Start next conversion so we continuously sample channels */
    dev()->adc->adcsra.var |= (1 << ADSC);
}

/*** EOF ***/


