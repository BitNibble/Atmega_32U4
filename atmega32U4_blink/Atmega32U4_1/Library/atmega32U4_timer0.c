/**********************************************************************
    ATMEGA32U4_TIMER0
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega32U4
Date:     27/10/2025
**********************************************************************/
/*** Library ***/
#include "atmega32U4_timer0.h"

/*** Procedure and Function declaration ***/
void TIMER_COUNTER0_wavegenmode(uint8_t wavegenmode);
void TIMER_COUNTER0_clear_wavegenmode(void);
void TIMER_COUNTER0_interrupt(uint8_t interrupt);
void TIMER_COUNTER0_clear_interrupt(void);
void TIMER_COUNTER0_compoutmodeA(uint8_t compoutmode);
void TIMER_COUNTER0_compoutmodeB(uint8_t compoutmode);
void TIMER_COUNTER0_clear_compoutmode(void);
void TIMER_COUNTER0_compareA(uint8_t compare);
void TIMER_COUNTER0_compareB(uint8_t compare);
uint8_t TIMER_COUNTER0_start(uint16_t prescaler);
uint8_t TIMER_COUNTER0_stop(void);

/*** Internal State ***/
static TC0_Handler atmega32u4_tc0_setup = {
    // Callback
    .callback = {
        .compa_vect = NULL,
        .compb_vect = NULL,
        .ovf_vect  = NULL
    },
    // V-table
    .wavegenmode = TIMER_COUNTER0_wavegenmode,
	.clear_wavegenmode = TIMER_COUNTER0_clear_wavegenmode,
    .interrupt   = TIMER_COUNTER0_interrupt,
	.clear_interrupt   = TIMER_COUNTER0_clear_interrupt,
    .compoutmodeA = TIMER_COUNTER0_compoutmodeA,
    .compoutmodeB = TIMER_COUNTER0_compoutmodeB,
	.clear_compoutmode = TIMER_COUNTER0_clear_compoutmode,
    .compareA = TIMER_COUNTER0_compareA,
    .compareB = TIMER_COUNTER0_compareB,
    .start = TIMER_COUNTER0_start,
    .stop  = TIMER_COUNTER0_stop
};
uint8_t timer0_state;

/*** Handler ***/
void tc0_enable(uint8_t wavegenmode, uint8_t interrupt)
{
    timer0_state = 0;

	// Power up Timer 0
	dev()->cpu->prr0.var &= ~(1 << 5); // PRTIM0 = bit 5

	/* Clear Waveform Generation Mode */
	TIMER_COUNTER0_clear_wavegenmode();

	/* Clear interrupts */
	TIMER_COUNTER0_clear_interrupt();

	/* Clear Compare Output Mode */
	TIMER_COUNTER0_clear_compoutmode();

    /* Clear Output Compare Registers */
    dev()->tc0->ocr0a.var = 0xFF;
    dev()->tc0->ocr0b.var = 0xFF;

	TIMER_COUNTER0_wavegenmode(wavegenmode);
	TIMER_COUNTER0_interrupt(interrupt);
}
TC0_Handler* tc0(void){ return &atmega32u4_tc0_setup; }

/*** Procedure and Function definition ***/
void TIMER_COUNTER0_wavegenmode(uint8_t wavegenmode)
{
    switch(wavegenmode){
		// Normal - 0xFF Immediate MAX
        case 0: break;
		// PWM, Phase Correct - 0xFF TOP BOTTOM
        case 1: 
			dev()->tc0->tccr0a.var |= (1 << WGM00); 
			break;
		// CTC - OCRA Immediate MAX
        case 2: 
			dev()->tc0->tccr0a.var |= (1 << WGM01); 
			break;
		// Fast PWM - 0xFF TOP MAX
        case 3: 
			dev()->tc0->tccr0a.var |= ((1 << WGM00) | (1 << WGM01)); 
			break;
		// PWM, Phase Correct - OCRA TOP BOTTOM
        case 5:
            dev()->tc0->tccr0a.var |= ((1 << WGM00) | (1 << WGM02));
            break;
		// Fast PWM - OCRA TOP TOP
        case 7:
			dev()->tc0->tccr0a.var |= ((1 << WGM00) | (1 << WGM01) | (1 << WGM02));
			break;
        default: break;
    }
}
void TIMER_COUNTER0_clear_wavegenmode(void)
{
	dev()->tc0->tccr0a.var &= ~((1 << WGM01) | (1 << WGM00));
	dev()->tc0->tccr0b.var &= ~(1 << WGM02);
}

void TIMER_COUNTER0_interrupt(uint8_t interrupt)
{
    switch(interrupt){
        case 0: break;
        case 1:
            dev()->tc0->timsk0.var |= (1 << TOIE0);
            break;
        case 2:
            dev()->tc0->timsk0.var |= (1 << OCIE0A);
            break;
        case 3:
            dev()->tc0->timsk0.var |= (1 << OCIE0B);
            break;
        default:
			break;
    }
	dev()->cpu->sreg.var |= 1 << 7;
}
void TIMER_COUNTER0_clear_interrupt(void)
{
	dev()->tc0->timsk0.var &= ~((1 << OCIE0A) | (1 << OCIE0B) | (1 << TOIE0));
}

uint8_t TIMER_COUNTER0_start(uint16_t prescaler)
{
    if(!timer0_state){
        dev()->tc0->tccr0b.var &= ~(7 << CS00); /* stop timer */
        switch(prescaler){
            case 1: dev()->tc0->tccr0b.var |= (1 << CS00); break;
            case 8: dev()->tc0->tccr0b.var |= (2 << CS00); break;
            case 64: dev()->tc0->tccr0b.var |= (3 << CS00); break;
            case 256: dev()->tc0->tccr0b.var |= (4 << CS00); break;
            case 1024: dev()->tc0->tccr0b.var |= (5 << CS00); break;
            case 6: dev()->tc0->tccr0b.var |= (6 << CS00); break; /* ext clock falling */
            case 7: dev()->tc0->tccr0b.var |= (7 << CS00); break; /* ext clock rising */
            default: dev()->tc0->tccr0b.var |= (5 << CS00); break;
        }
        timer0_state = 85;
    }
    return timer0_state;
}

void TIMER_COUNTER0_compoutmodeA(uint8_t compoutmode)
{
    switch(compoutmode){
        case 0: break;
        case 1:
            dev()->portb->ddr.var |= 0x80; /* PB7 (OC0A) */
            dev()->tc0->tccr0a.var |= (1 << COM0A0);
            break;
        case 2:
            dev()->portb->ddr.var |= 0x80;
            dev()->tc0->tccr0a.var |= (1 << COM0A1);
            break;
        case 3:
			dev()->portb->ddr.var |= 0x80;
			dev()->tc0->tccr0a.var |= ((1 << COM0A0) | (1 << COM0A1));
			break;
        default: break;
    }
}
void TIMER_COUNTER0_compoutmodeB(uint8_t compoutmode)
{
    switch(compoutmode){
        case 0: break;
        case 1:
            dev()->portd->ddr.var |= 0x01; /* PD0 (OC0B) */
            dev()->tc0->tccr0a.var |= (1 << COM0B0);
            break;
        case 2:
            dev()->portd->ddr.var |= 0x01;
            dev()->tc0->tccr0a.var |= (1 << COM0B1);
            break;
        case 3:
			dev()->portd->ddr.var |= 0x01;
			dev()->tc0->tccr0a.var |= ((1 << COM0B0) | (1 << COM0B1));
			break;
        default: break;
    }
}
void TIMER_COUNTER0_clear_compoutmode(void)
{
	dev()->tc0->tccr0a.var &= ~(3 << COM0A0);
	dev()->tc0->tccr0a.var &= ~(3 << COM0B0);
}

void TIMER_COUNTER0_compareA(uint8_t compare)
{
    dev()->tc0->ocr0a.var = compare;
}
void TIMER_COUNTER0_compareB(uint8_t compare)
{
    dev()->tc0->ocr0b.var = compare;
}

uint8_t TIMER_COUNTER0_stop(void)
{
    dev()->tc0->tccr0b.var &= ~(7 << CS00); /* No clock source (stop) */
    timer0_state = 0;
    return timer0_state;
}

/*** Interrupts (AVR-GCC ISR names kept identical) ***/
ISR(TIMER0_COMPA_vect)
{
    if(atmega32u4_tc0_setup.callback.compa_vect){ atmega32u4_tc0_setup.callback.compa_vect(); }
}
ISR(TIMER0_COMPB_vect)
{
    if(atmega32u4_tc0_setup.callback.compb_vect){ atmega32u4_tc0_setup.callback.compb_vect(); }
}
ISR(TIMER0_OVF_vect)
{
    if(atmega32u4_tc0_setup.callback.ovf_vect){ atmega32u4_tc0_setup.callback.ovf_vect(); }
}

/*** EOF ***/

