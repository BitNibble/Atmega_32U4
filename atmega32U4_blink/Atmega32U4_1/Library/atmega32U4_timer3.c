/**********************************************************************
    ATMEGA32U4_TIMER3
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega32U4
Date:     27/10/2025
**********************************************************************/
/*** Library ***/
#include "atmega32U4_timer3.h"

/*** Procedure and Function declaration ***/
void TIMER_COUNTER3_wavegenmode(unsigned char wavegenmode);
void TIMER_COUNTER3_clear_wavegenmode(void);
void TIMER_COUNTER3_interrupt(unsigned char interrupt);
void TIMER_COUNTER3_clear_interrupt(void);
void TIMER_COUNTER3_compoutmodeA(uint8_t compoutmode);
void TIMER_COUNTER3_compoutmodeB(uint8_t compoutmode);
void TIMER_COUNTER3_compoutmodeC(uint8_t compoutmode);
void TIMER_COUNTER3_clear_compoutmode(void);
void TIMER_COUNTER3_compareA(uint16_t compare);
void TIMER_COUNTER3_compareB(uint16_t compare);
void TIMER_COUNTER3_compareC(uint16_t compare);
uint8_t TIMER_COUNTER3_start(uint16_t prescaler);
uint8_t TIMER_COUNTER3_stop(void);

/*** Internal State ***/
static TC3_Handler atmega32u4_tc3_setup = {
    // Callback
    .callback = {
        .capt_vect = NULL,
        .compa_vect = NULL,
        .compb_vect = NULL,
        .compc_vect = NULL,
        .ovf_vect  = NULL
    },
    // V-table
    .wavegenmode = TIMER_COUNTER3_wavegenmode,
	.clear_wavegenmode = TIMER_COUNTER3_clear_wavegenmode,
    .interrupt   = TIMER_COUNTER3_interrupt,
	.clear_interrupt   = TIMER_COUNTER3_clear_interrupt,
    .compoutmodeA = TIMER_COUNTER3_compoutmodeA,
    .compoutmodeB = TIMER_COUNTER3_compoutmodeB,
    .compoutmodeC = TIMER_COUNTER3_compoutmodeC,
	.clear_compoutmode = TIMER_COUNTER3_clear_compoutmode,
    .compareA = TIMER_COUNTER3_compareA,
    .compareB = TIMER_COUNTER3_compareB,
    .compareC = TIMER_COUNTER3_compareC,
    .start = TIMER_COUNTER3_start,
    .stop  = TIMER_COUNTER3_stop
};
uint8_t timer3_state;

/*** Handler ***/
void tc3_enable(unsigned char wavegenmode, unsigned char interrupt)
{
    timer3_state = 0;
	
	/* Power up Timer 3
	   Replace (1 << 4) with your project's PRTIM3 macro if available.
	   This follows the same pattern as your Timer0/1 drivers.
	*/
	dev()->cpu->prr0.var &= ~(1 << 4);

	/* Clear Waveform Generation Mode */
	TIMER_COUNTER3_clear_wavegenmode();
	
	/* Clear interrupts */
	TIMER_COUNTER3_clear_interrupt();
	
	/* Clear Compare Output Mode */
	TIMER_COUNTER3_clear_compoutmode();

    /* Clear Output Compare Registers (atomic concerns should be handled by caller if needed) */
    dev()->tc3->ocr3a = WriteHLByte(0xFFFF);
    dev()->tc3->ocr3b = WriteHLByte(0xFFFF);
    dev()->tc3->ocr3c = WriteHLByte(0xFFFF);
	
	TIMER_COUNTER3_wavegenmode(wavegenmode);
	TIMER_COUNTER3_interrupt(interrupt);
}
TC3_Handler* tc3(void){ return &atmega32u4_tc3_setup; }

/*** Procedure and Function definition ***/
void TIMER_COUNTER3_wavegenmode(unsigned char wavegenmode)
{
	switch (wavegenmode) {
		// Normal - 0xFFFF Immediate MAX
		case 0: break;
		// PWM, Phase Correct, 8-bit - 0x00FF TOP BOTTOM
		case 1: dev()->tc3->tccr3a.var |= (1 << WGM30); break;
		// PWM, Phase Correct, 9-bit - 0x01FF TOP BOTTOM
		case 2: dev()->tc3->tccr3a.var |= (1 << WGM31); break;
		// CTC - OCRnA Immediate MAX
		case 4: dev()->tc3->tccr3b.var |= (1 << WGM32); break;
		// PWM, Phase and Frequency Correct - ICRn BOTTOM BOTTOM
		case 8: dev()->tc3->tccr3b.var |= (1 << WGM33); break;
		default: break;
	}
}
void TIMER_COUNTER3_clear_wavegenmode(void)
{
	/* Clear Waveform Generation Mode */
	dev()->tc3->tccr3a.var &= ~((1 << WGM11) | (1 << WGM10));
	dev()->tc3->tccr3b.var &= ~((1 << WGM13) | (1 << WGM12));
}

void TIMER_COUNTER3_interrupt(unsigned char interrupt)
{
    switch(interrupt){
        case 0: break;
        case 1:
            dev()->tc3->timsk3.var |= (1 << TOIE3);
            break;
        case 2:
            dev()->tc3->timsk3.var |= (1 << OCIE3A);
            break;
        case 3:
            dev()->tc3->timsk3.var |= (1 << OCIE3B);
            break;
        case 4:
            dev()->tc3->timsk3.var |= (1 << OCIE3C);
            break;
        case 5:
			dev()->tc3->timsk3.var |= (1 << ICIE3);
			break;
        default:
		    dev()->tc3->timsk3.var |= (1 << TOIE3);
			break;
    }
	dev()->cpu->sreg.var |= 1 << 7;
}
void TIMER_COUNTER3_clear_interrupt(void)
{
	/* Clear interrupts */
	dev()->tc3->timsk3.var &= ~ ((1 << OCIE3A) | (1 << OCIE3B) | (1 << OCIE3C) | (1 << TOIE3) | (1 << ICIE3));
}

uint8_t TIMER_COUNTER3_start(uint16_t prescaler)
{
    if(!timer3_state){
        dev()->tc3->tccr3b.var &= ~(7 << CS30); /* stop timer */
        switch(prescaler){
            case 1: dev()->tc3->tccr3b.var |= (1 << CS30); break;
            case 8: dev()->tc3->tccr3b.var |= (1 << CS31); break;
            case 64: dev()->tc3->tccr3b.var |= (3 << CS30); break;
            case 256: dev()->tc3->tccr3b.var |= (1 << CS32); break;
            case 1024: dev()->tc3->tccr3b.var |= (5 << CS30); break;
            case 6: dev()->tc3->tccr3b.var |= (6 << CS30); break; /* ext clock falling */
            case 7: dev()->tc3->tccr3b.var |= (7 << CS30); break; /* ext clock rising */
            default: dev()->tc3->tccr3b.var |= (5 << CS30); break;
        }
        timer3_state = 85;
    }
    return timer3_state;
}

void TIMER_COUNTER3_compoutmodeA(unsigned char compoutmode)
{
    switch(compoutmode){
        case 0: break;
        case 1:
            /* OC3A pin DDR should be set to output when enabling compare */
            /* Adjust port/bit if your board routes OC3A elsewhere */
            dev()->portc->ddr.var |= 0x04; /* example: PC2 = OC3A (adjust as needed) */
            dev()->tc3->tccr3a.var |= (1 << COM3A0);
            break;
        case 2:
            dev()->portc->ddr.var |= 0x04;
            dev()->tc3->tccr3a.var |= (1 << COM3A1);
            break;
        case 3:
			dev()->portc->ddr.var |= 0x04;
			dev()->tc3->tccr3a.var |= ((1 << COM3A0) | (1 << COM3A1));
			break;
        default: break;
    }
}
void TIMER_COUNTER3_compoutmodeB(unsigned char compoutmode)
{
    switch(compoutmode){
        case 0: break;
        case 1:
            dev()->portc->ddr.var |= 0x08; /* example: PC3 = OC3B (adjust as needed) */
            dev()->tc3->tccr3a.var |= (1 << COM3B0);
            break;
        case 2:
            dev()->portc->ddr.var |= 0x08;
            dev()->tc3->tccr3a.var |= (1 << COM3B1);
            break;
        case 3:
			dev()->portc->ddr.var |= 0x08;
			dev()->tc3->tccr3a.var |= ((1 << COM3B0) | (1 << COM3B1));
			break;
        default: break;
    }
}
void TIMER_COUNTER3_compoutmodeC(unsigned char compoutmode)
{
    switch(compoutmode){
        case 0: break;
        case 1:
            dev()->portc->ddr.var |= 0x10; /* example: PC4 = OC3C (adjust as needed) */
            dev()->tc3->tccr3a.var |= (1 << COM3C0);
            break;
        case 2:
            dev()->portc->ddr.var |= 0x10;
            dev()->tc3->tccr3a.var |= (1 << COM3C1);
            break;
        case 3:
			dev()->portc->ddr.var |= 0x10;
			dev()->tc3->tccr3a.var |= ((1 << COM3C0) | (1 << COM3C1));
			break;
        default: break;
    }
}
void TIMER_COUNTER3_clear_compoutmode(void)
{
	/* Clear Compare Output Mode */
	dev()->tc3->tccr3a.var &= ~(3 << COM3A0);
	dev()->tc3->tccr3a.var &= ~(3 << COM3B0);
	dev()->tc3->tccr3a.var &= ~(3 << COM3C0);
}

void TIMER_COUNTER3_compareA(uint16_t compare)
{
    dev()->tc3->ocr3a = WriteHLByte(compare);
}
void TIMER_COUNTER3_compareB(uint16_t compare)
{
    dev()->tc3->ocr3b = WriteHLByte(compare);
}
void TIMER_COUNTER3_compareC(uint16_t compare)
{
    dev()->tc3->ocr3c = WriteHLByte(compare);
}

uint8_t TIMER_COUNTER3_stop(void)
{
    dev()->tc3->tccr3b.var &= ~(7 << CS30); /* No clock source (stop) */
    timer3_state = 0;
    return timer3_state;
}

/*** Interrupts (AVR-GCC ISR names kept identical) ***/
ISR(TIMER3_CAPT_vect)
{
    if(atmega32u4_tc3_setup.callback.capt_vect){ atmega32u4_tc3_setup.callback.capt_vect(); }
}
ISR(TIMER3_COMPA_vect)
{
    if(atmega32u4_tc3_setup.callback.compa_vect){ atmega32u4_tc3_setup.callback.compa_vect(); }
}
ISR(TIMER3_COMPB_vect)
{
    if(atmega32u4_tc3_setup.callback.compb_vect){ atmega32u4_tc3_setup.callback.compb_vect(); }
}
ISR(TIMER3_COMPC_vect)
{
    if(atmega32u4_tc3_setup.callback.compc_vect){ atmega32u4_tc3_setup.callback.compc_vect(); }
}
ISR(TIMER3_OVF_vect)
{
    if(atmega32u4_tc3_setup.callback.ovf_vect){ atmega32u4_tc3_setup.callback.ovf_vect(); }
}

/*** EOF ***/

