/*************************************************************************
	ANALOG
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega32u4
Date: 03122023
Comment:
	Very Stable
*************************************************************************/
/*** File Library ***/
#include "atmega32u4mapping.h"
#include "atmega32u4analog.h"
#include <stdarg.h>

/*** File Constant & Macro ***/
#ifndef GLOBAL_INTERRUPT_ENABLE
	#define GLOBAL_INTERRUPT_ENABLE 7
#endif
// if using differential channels this value has to be greater than one
#define MAX_CHANNEL 8
#if defined(__AVR_ATmega16U4__) || \
	defined(__AVR_ATmega32U4__)
	#define MUX_MASK 15
	#define ANALOG_INTERRUPT ADC_vect
#else
 	#error "Not Atmega32u4"
#endif

/*** File Variable ***/
//ATMEGA32U4 atmega32u4;
static volatile int ADC_VALUE[MAX_CHANNEL];
static volatile int ADC_CHANNEL_GAIN[MAX_CHANNEL];
static volatile int ADC_N_CHANNEL;
static volatile int ADC_SELECTOR;
static volatile int adc_sample;
static volatile int adc_tmp;
static volatile unsigned char adc_n_sample;

/*** File Header ***/
int ANALOG_read(int selection);

/*** Procedure & Function ***/
ANALOG ANALOGenable( uint8_t Vreff, uint8_t Divfactor, int n_channel, ... )
// Interrupt running mode setup
// setup, and list of channels to be probed
{
	uint8_t tSREG;
	atmega32u4 = ATMEGA32U4enable();
	va_list list;
	int i;

	tSREG = atmega32u4.cpu.reg->sreg;
	atmega32u4.cpu.reg->sreg &= ~ (1 << GLOBAL_INTERRUPT_ENABLE);
	
	ADC_N_CHANNEL = n_channel;
	ADC_SELECTOR = 0;
	adc_n_sample = 0;

	ANALOG analog;
	//V table
	analog.read = ANALOG_read;
	
	atmega32u4.adc.reg->admux &= ~(3 << REFS0);
	switch( Vreff ){
		case 0:
			analog.par.VREFF = 0;
		break;
		case 1:
			atmega32u4.adc.reg->admux |=	(1 << REFS0);
			analog.par.VREFF = 1;
		break;
		case 3:
			atmega32u4.adc.reg->admux |=	(3 << REFS0);
			analog.par.VREFF = 3;
		break;
		default:
			analog.par.VREFF = 0;
		break;
	}
	
	atmega32u4.adc.reg->admux &= ~(1 << ADLAR);
	
	va_start(list, n_channel);
	for( i = 0; i < n_channel; i++ ){
		ADC_CHANNEL_GAIN[i] = va_arg(list, int);
	}
	va_end(list);
	atmega32u4.adc.reg->admux &= ~MUX_MASK;
	atmega32u4.adc.reg->admux |= (MUX_MASK & ADC_CHANNEL_GAIN[ADC_SELECTOR]);
	
	atmega32u4.adc.reg->adcsra |= (1 << ADEN);
	atmega32u4.adc.reg->adcsra |= (1 << ADSC);
	atmega32u4.adc.reg->adcsra &= ~(1 << ADATE);
	atmega32u4.adc.reg->adcsrb &= ~(7 << ADTS0);
	atmega32u4.adc.reg->adcsra |= (1 << ADIE);
	
	atmega32u4.adc.reg->adcsra &= ~(7 << ADPS0);
	switch( Divfactor ){
		case 2: // 1
			analog.par.DIVISION_FACTOR = 2;
		break;
		case 4: // 2
			atmega32u4.adc.reg->adcsra |= (1 << ADPS1);
			analog.par.DIVISION_FACTOR = 4;
		break;
		case 8: // 3
			atmega32u4.adc.reg->adcsra |= (3 << ADPS0);
			analog.par.DIVISION_FACTOR = 8;
		break;
		case 16: // 4
			atmega32u4.adc.reg->adcsra |= (1 << ADPS2);
			analog.par.DIVISION_FACTOR	=	16;
		break;
		case 32: // 5
			atmega32u4.adc.reg->adcsra |= (5 << ADPS0);
			analog.par.DIVISION_FACTOR = 32;
		break;
		case 64: // 6
			atmega32u4.adc.reg->adcsra |= (6 << ADPS0);
			analog.par.DIVISION_FACTOR = 64;
		break;
		case 128: // 7
			atmega32u4.adc.reg->adcsra |= (7 << ADPS0);
			analog.par.DIVISION_FACTOR = 128;
		break;
		default: // 7
			atmega32u4.adc.reg->adcsra |= (7 << ADPS0);
			analog.par.DIVISION_FACTOR = 128;
		break;
	}
	atmega32u4.cpu.reg->sreg = tSREG;
	atmega32u4.cpu.reg->sreg |= (1 << GLOBAL_INTERRUPT_ENABLE);
	
#ifdef _ANALOG_MODULE_
	atmega32u4.adc.run = analog;
#endif

	return analog;
}

int ANALOG_read(int selection)
// Returns selected Channel ADC_VALUE
{
	uint8_t ADSC_FLAG;
	ADSC_FLAG = (1 << ADSC);
	if( !(atmega32u4.adc.reg->adcsra & ADSC_FLAG) ){
		//ADC_SELECT
		atmega32u4.adc.reg->adcsra |= (1 << ADSC);
	}	
	return ADC_VALUE[selection];
}

/*** File Interrupt ***/
ISR(ANALOG_INTERRUPT)
// Function: ANALOG interrupt
// Purpose:  Read Analog Input
{
	adc_tmp = ADCL;
	adc_tmp |= (ADCH << 8);
	if(adc_n_sample < (1 << ADC_NUMBER_SAMPLE)){
		adc_n_sample++;
		adc_sample += adc_tmp;
	}else{
		ADC_VALUE[ADC_SELECTOR] = adc_sample >> ADC_NUMBER_SAMPLE;
		adc_n_sample=adc_sample = 0;
		/******/
		if(ADC_SELECTOR < ADC_N_CHANNEL)
			ADC_SELECTOR++;
		else
			ADC_SELECTOR = 0;
		atmega32u4.adc.reg->admux &= ~MUX_MASK;
		atmega32u4.adc.reg->admux |= (ADC_CHANNEL_GAIN[ADC_SELECTOR] & MUX_MASK);
	}		
}

/***EOF***/

