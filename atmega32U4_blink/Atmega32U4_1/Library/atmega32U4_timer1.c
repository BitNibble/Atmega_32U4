/**********************************************************************
    ATMEGA32U4_TIMER1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega32U4
Date:     26/10/2025
**********************************************************************/
/*** Library ***/
#include "atmega32U4_timer1.h"

/*** Procedure and Function declaration ***/
void TIMER_COUNTER1_wavegenmode(unsigned char wavegenmode);
void TIMER_COUNTER1_clear_wavegenmode(void);
void TIMER_COUNTER1_interrupt(unsigned char interrupt);
void TIMER_COUNTER1_clear_interrupt(void);
void TIMER_COUNTER1_compoutmodeA(unsigned char compoutmode);
void TIMER_COUNTER1_compoutmodeB(unsigned char compoutmode);
void TIMER_COUNTER1_compoutmodeC(unsigned char compoutmode);
void TIMER_COUNTER1_clear_compoutmode(void);
void TIMER_COUNTER1_compareA(uint16_t compare);
void TIMER_COUNTER1_compareB(uint16_t compare);
void TIMER_COUNTER1_compareC(uint16_t compare);
uint8_t TIMER_COUNTER1_start(unsigned int prescaler);
uint8_t TIMER_COUNTER1_stop(void);

/*** Internal State ***/
static TC1_Handler atmega32u4_tc1_setup = {
    // Callback
    .callback = {
        .capt_vect = NULL,
        .compa_vect = NULL,
        .compb_vect = NULL,
        .compc_vect = NULL,
        .ovf_vect  = NULL
    },
    // V-table
    .wavegenmode = TIMER_COUNTER1_wavegenmode,
	.clear_wavegenmode = TIMER_COUNTER1_clear_wavegenmode,
    .interrupt   = TIMER_COUNTER1_interrupt,
	.clear_interrupt   = TIMER_COUNTER1_clear_interrupt,
    .compoutmodeA = TIMER_COUNTER1_compoutmodeA,
    .compoutmodeB = TIMER_COUNTER1_compoutmodeB,
    .compoutmodeC = TIMER_COUNTER1_compoutmodeC,
	.clear_compoutmode = TIMER_COUNTER1_clear_compoutmode,
    .compareA = TIMER_COUNTER1_compareA,
    .compareB = TIMER_COUNTER1_compareB,
    .compareC = TIMER_COUNTER1_compareC,
    .start = TIMER_COUNTER1_start,
    .stop  = TIMER_COUNTER1_stop
};
uint8_t timer1_state;

/*** Handler ***/
void tc1_enable(unsigned char wavegenmode, unsigned char interrupt)
{
    timer1_state = 0;
	
	// Power up Timer 1
	dev()->cpu->prr0.var &= ~(1 << 3); // 0n

	/* Clear Waveform Generation Mode */
	TIMER_COUNTER1_clear_wavegenmode();
	
	/* Clear interrupts */
	TIMER_COUNTER1_clear_interrupt();
	
	/* Clear Compare Output Mode */
	TIMER_COUNTER1_clear_compoutmode();

    /* Clear Output Compare Registers */
    dev()->tc1->ocr1a = WriteHLByte(~0);
    dev()->tc1->ocr1b = WriteHLByte(~0);
    dev()->tc1->ocr1c = WriteHLByte(~0);
	
	TIMER_COUNTER1_wavegenmode(wavegenmode);
	TIMER_COUNTER1_interrupt(interrupt);
}
TC1_Handler* tc1(void){ return &atmega32u4_tc1_setup; }

/*** Procedure and Function definition ***/
void TIMER_COUNTER1_wavegenmode(unsigned char wavegenmode)
{
    switch(wavegenmode){
		// Normal - 0xFFFF Immediate MAX
        case 0: break;
		// PWM, Phase Correct, 8-bit - 0x00FF TOP BOTTOM
        case 1: dev()->tc1->tccr1a.var |= (1 << WGM10); break;
		// PWM, Phase Correct, 9-bit - 0x01FF TOP BOTTOM
        case 2: dev()->tc1->tccr1a.var |= (1 << WGM11); break;
		// CTC - OCRnA Immediate MAX
        case 3: dev()->tc1->tccr1b.var |= (1 << WGM12); break;
		// PWM, Phase and Frequency Correct - ICRn BOTTOM BOTTOM
        case 4: dev()->tc1->tccr1b.var |= (1 << WGM13); break; // ICR
        default: break;
    }
}
void TIMER_COUNTER1_clear_wavegenmode(void)
{
	/* Clear Waveform Generation Mode */
	dev()->tc1->tccr1a.var &= ~((1 << WGM11) | (1 << WGM10));
	dev()->tc1->tccr1b.var &= ~((1 << WGM13) | (1 << WGM12));
}

void TIMER_COUNTER1_interrupt(unsigned char interrupt)
{
    switch(interrupt){
        case 0: break;
        case 1:
            dev()->tc1->timsk1.var |= (1 << TOIE1);
            break;
        case 2:
            dev()->tc1->timsk1.var |= (1 << OCIE1A);
            break;
        case 3:
            dev()->tc1->timsk1.var |= (1 << OCIE1B);
            break;
        case 4:
            dev()->tc1->timsk1.var |= (1 << OCIE1C);
            break;
        case 5:
			dev()->tc1->timsk1.var |= (1 << ICIE1);
			break;
        default:
			break;
    }
	dev()->cpu->sreg.var |= 1 << 7;
}
void TIMER_COUNTER1_clear_interrupt(void)
{
	/* Clear interrupts */
	dev()->tc1->timsk1.var &= ~ ((1 << OCIE1A) | (1 << OCIE1B) | (1 << OCIE1C) | (1 << TOIE1));
}

uint8_t TIMER_COUNTER1_start(unsigned int prescaler)
{
    if(!timer1_state){
        dev()->tc1->tccr1b.var &= ~(7 << CS10); /* stop timer */
        switch(prescaler){
            case 1: dev()->tc1->tccr1b.var |= (1 << CS10); break;
            case 8: dev()->tc1->tccr1b.var |= (1 << CS11); break;
            case 64: dev()->tc1->tccr1b.var |= (3 << CS10); break;
            case 256: dev()->tc1->tccr1b.var |= (1 << CS12); break;
            case 1024: dev()->tc1->tccr1b.var |= (5 << CS10); break;
            case 6: dev()->tc1->tccr1b.var |= (6 << CS10); break; /* ext clock falling */
            case 7: dev()->tc1->tccr1b.var |= (7 << CS10); break; /* ext clock rising */
            default: dev()->tc1->tccr1b.var |= (5 << CS10); break;
        }
        timer1_state = 85;
    }
    return timer1_state;
}

void TIMER_COUNTER1_compoutmodeA(unsigned char compoutmode)
{
    switch(compoutmode){
		// Normal port operation, OCnA/OCnB/OCnC disconnected
        case 0: break;
		// Toggle OCnA/OCnB/OCnC on compare match
        case 1:
            dev()->portb->ddr.var |= 0x20; /* PB5 OC1A */
            dev()->tc1->tccr1a.var |= (1 << COM1A0);
            break;
		// Clear OCnA/OCnB/OCnC on compare match (set output to low level)
        case 2:
            dev()->portb->ddr.var |= 0x20;
            dev()->tc1->tccr1a.var |= (1 << COM1A1);
            break;
		// Set OCnA/OCnB/OCnC on compare match (set output to high level)
        case 3:
			dev()->portb->ddr.var |= 0x20;
			dev()->tc1->tccr1a.var |= ((1 << COM1A0) | (1 << COM1A1));
			break;
        default: break;
    }
}
void TIMER_COUNTER1_compoutmodeB(unsigned char compoutmode)
{
    switch(compoutmode){
		// Normal port operation, OCnA/OCnB/OCnC disconnected
        case 0: break;
		// Toggle OCnA/OCnB/OCnC on compare match
        case 1:
            dev()->portb->ddr.var |= 0x40; /* PB6 OC1B */
            dev()->tc1->tccr1a.var |= (1 << COM1B0);
            break;
		// Clear OCnA/OCnB/OCnC on compare match (set output to low level)
        case 2:
            dev()->portb->ddr.var |= 0x40;
            dev()->tc1->tccr1a.var |= (1 << COM1B1);
            break;
		// Set OCnA/OCnB/OCnC on compare match (set output to high level)
        case 3:
			dev()->portb->ddr.var |= 0x40;
			dev()->tc1->tccr1a.var |= ((1 << COM1B0) | (1 << COM1B1));
			break;
        default: break;
    }
}
void TIMER_COUNTER1_compoutmodeC(unsigned char compoutmode)
{
    switch(compoutmode){
		// Normal port operation, OCnA/OCnB/OCnC disconnected
        case 0: break;
		// Toggle OCnA/OCnB/OCnC on compare match
        case 1:
            dev()->portb->ddr.var |= 0x80; /* PB7 OC1C */
            dev()->tc1->tccr1a.var |= (1 << COM1C0);
            break;
		// Clear OCnA/OCnB/OCnC on compare match (set output to low level)
        case 2:
            dev()->portb->ddr.var |= 0x80;
            dev()->tc1->tccr1a.var |= (1 << COM1C1);
            break;
		// Set OCnA/OCnB/OCnC on compare match (set output to high level)
        case 3:
			dev()->portb->ddr.var |= 0x80;
			dev()->tc1->tccr1a.var |= ((1 << COM1C0) | (1 << COM1C1));
			break;
        default: break;
    }
}
void TIMER_COUNTER1_clear_compoutmode(void)
{
	/* Clear Compare Output Mode */
	dev()->tc1->tccr1a.var &= ~(3 << COM1A0);
	dev()->tc1->tccr1a.var &= ~(3 << COM1B0);
	dev()->tc1->tccr1a.var &= ~(3 << COM1C0);
}

void TIMER_COUNTER1_compareA(uint16_t compare)
{
    dev()->tc1->ocr1a = WriteHLByte(compare);
}
void TIMER_COUNTER1_compareB(uint16_t compare)
{
    dev()->tc1->ocr1b = WriteHLByte(compare);
}
void TIMER_COUNTER1_compareC(uint16_t compare)
{
    dev()->tc1->ocr1c = WriteHLByte(compare);
}

uint8_t TIMER_COUNTER1_stop(void)
{
    dev()->tc1->tccr1b.var &= ~(7 << CS10); /* No clock source (stop) */
    timer1_state = 0;
    return timer1_state;
}

/*** Interrupts (AVR-GCC ISR names kept identical) ***/
ISR(TIMER1_CAPT_vect)
{
    if(atmega32u4_tc1_setup.callback.capt_vect){ atmega32u4_tc1_setup.callback.capt_vect(); }
}
ISR(TIMER1_COMPA_vect)
{
    if(atmega32u4_tc1_setup.callback.compa_vect){ atmega32u4_tc1_setup.callback.compa_vect(); }
}
ISR(TIMER1_COMPB_vect)
{
    if(atmega32u4_tc1_setup.callback.compb_vect){ atmega32u4_tc1_setup.callback.compb_vect(); }
}
ISR(TIMER1_COMPC_vect)
{
    if(atmega32u4_tc1_setup.callback.compc_vect){ atmega32u4_tc1_setup.callback.compc_vect(); }
}
ISR(TIMER1_OVF_vect)
{
    if(atmega32u4_tc1_setup.callback.ovf_vect){ atmega32u4_tc1_setup.callback.ovf_vect(); }
}

/*** EOF ***/

