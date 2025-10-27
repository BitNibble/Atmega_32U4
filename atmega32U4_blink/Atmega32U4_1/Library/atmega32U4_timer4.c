/**********************************************************************
    ATMEGA32U4_TIMER4
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega32U4
Date:     27/10/2025
**********************************************************************/

/*** Library ***/
#include "atmega32U4_timer4.h"

/*** Procedure declarations ***/
void TIMER_COUNTER4_wavegenmode(unsigned char mode);
void TIMER_COUNTER4_clear_wavegenmode(void);
void TIMER_COUNTER4_interrupt(unsigned char interrupt);
void TIMER_COUNTER4_clear_interrupt(void);
void TIMER_COUNTER4_compoutmodeA(unsigned char mode);
void TIMER_COUNTER4_compoutmodeB(unsigned char mode);
void TIMER_COUNTER4_compoutmodeD(unsigned char mode);
void TIMER_COUNTER4_clear_compoutmode(void);
void TIMER_COUNTER4_compareA(uint16_t compare);
void TIMER_COUNTER4_compareB(uint16_t compare);
void TIMER_COUNTER4_compareC(uint16_t compare);
void TIMER_COUNTER4_compareD(uint16_t compare);
uint8_t TIMER_COUNTER4_start(uint16_t prescaler);
uint8_t TIMER_COUNTER4_stop(void);

/*** Internal State ***/
static TC4_Handler atmega32u4_tc4_setup = {
    // Callback
    .callback = {
        .compa_vect = NULL,
        .compb_vect = NULL,
        .compc_vect = NULL,
        .compd_vect = NULL,
        .ovf_vect   = NULL
    },
    // V-table
    .wavegenmode = TIMER_COUNTER4_wavegenmode,
	.clear_wavegenmode = TIMER_COUNTER4_clear_wavegenmode,
    .interrupt = TIMER_COUNTER4_interrupt,
	.clear_interrupt = TIMER_COUNTER4_clear_interrupt,
    .compoutmodeA = TIMER_COUNTER4_compoutmodeA,
    .compoutmodeB = TIMER_COUNTER4_compoutmodeB,
    .compoutmodeD = TIMER_COUNTER4_compoutmodeD,
	.clear_compoutmode = TIMER_COUNTER4_clear_compoutmode,
    .compareA = TIMER_COUNTER4_compareA,
    .compareB = TIMER_COUNTER4_compareB,
	.compareC = TIMER_COUNTER4_compareC,
    .compareD = TIMER_COUNTER4_compareD,
    .start = TIMER_COUNTER4_start,
    .stop  = TIMER_COUNTER4_stop
};
uint8_t timer4_state;

/*** Handler ***/
void tc4_enable(uint8_t wavegenmode, uint8_t interrupt)
{
	timer4_state = 0;

	// Power up Timer4
	dev()->cpu->prr0.var &= ~(1 << 4);

	TIMER_COUNTER4_clear_wavegenmode();
	TIMER_COUNTER4_clear_interrupt();
	TIMER_COUNTER4_clear_compoutmode();

	// Clear compare registers
	dev()->tc4->tc4h.var = 0x03;
	dev()->tc4->ocr4a.var = 0xFF;
	dev()->tc4->ocr4b.var = 0xFF;
	dev()->tc4->ocr4d.var = 0xFF;

	TIMER_COUNTER4_wavegenmode(wavegenmode);
	TIMER_COUNTER4_interrupt(interrupt);
}

TC4_Handler* tc4(void){ return &atmega32u4_tc4_setup; }

/*** Waveform Generation ***/
void TIMER_COUNTER4_wavegenmode(unsigned char mode)
{
	switch(mode){
		// Normal - OCR4C Immediate TOP
		case 4:
			dev()->tc4->tccr4b.par.pwm4x = 0;
			break;
		// Fast PWM - OCR4C TOP TOP
		case 0:
			dev()->tc4->tccr4b.par.pwm4x = 1;
			break;
		// Phase and Frequency Correct PWM - OCR4C BOTTOM BOTTOM
		case 1:
			dev()->tc4->tccr4b.par.pwm4x = 1;
			dev()->tc4->tccr4d.var |= (1 << WGM40);
			break;
		// PWM6 / Single-slope - OCR4C TOP TOP
		case 2:
			dev()->tc4->tccr4b.par.pwm4x = 1;
			dev()->tc4->tccr4d.var |= (1 << WGM41);
			break;
		// PWM6 / Dual-slope - OCR4C BOTTOM BOTTOM
		case 3:
			dev()->tc4->tccr4b.par.pwm4x = 1;
			dev()->tc4->tccr4d.var |= ((1 << WGM41) | (1 << WGM40));
			break;
		default:
		break;
	}
}
void TIMER_COUNTER4_clear_wavegenmode(void)
{
	dev()->tc4->tccr4d.var &= ~((1 << WGM41) | (1 << WGM40));
}

/*** Interrupts ***/
void TIMER_COUNTER4_interrupt(unsigned char interrupt)
{
	switch(interrupt){
		case 0: break;
		case 1: dev()->tc4->timsk4.var |= (1 << TOIE4); break;
		case 2: dev()->tc4->timsk4.var |= (1 << OCIE4A); break;
		case 3: dev()->tc4->timsk4.var |= (1 << OCIE4B); break;
		case 4: dev()->tc4->timsk4.var |= (1 << OCIE4D); break;
		default: break;
	}
	dev()->cpu->sreg.var |= (1 << 7);
}
void TIMER_COUNTER4_clear_interrupt(void)
{
	dev()->tc4->timsk4.var &= ~((1 << OCIE4A)|(1 << OCIE4B)|(1 << OCIE4D)|(1 << TOIE4));
}

/*** Compare Outputs ***/
void TIMER_COUNTER4_compoutmodeA(unsigned char mode)
{
	switch(mode){
		// Normal Mode - Normal port operation - Disconnected Disconnected
		case 0: break;
		// Normal Mode - Toggle on Compare Match - Connected Disconnected
		case 1: dev()->portc->ddr.var |= (1 << 7); dev()->tc4->tccr4a.var |= (1 << COM4A0); break; // PC7
		// Normal Mode - Clear on Compare Match - Connected Disconnected
		case 2: dev()->portc->ddr.var |= (1 << 7); dev()->tc4->tccr4a.var |= (1 << COM4A1); break;
		// Normal Mode - Set on Compare Match - Connected Disconnected
		case 3: dev()->portc->ddr.var |= (1 << 7); dev()->tc4->tccr4a.var |= ((1 << COM4A0) | (1 << COM4A1)); break;
		default: break;
	}
}
void TIMER_COUNTER4_compoutmodeB(unsigned char mode)
{
	switch(mode){
		case 0: break;
		case 1: dev()->portb->ddr.var |= (1 << 6); dev()->tc4->tccr4a.var |= (1 << COM4B0); break; // PB6
		case 2: dev()->portb->ddr.var |= (1 << 6); dev()->tc4->tccr4a.var |= (1 << COM4B1); break;
		case 3: dev()->portb->ddr.var |= (1 << 6); dev()->tc4->tccr4a.var |= ((1 << COM4B0) | (1 << COM4B1)); break;
		default: break;
	}
}
void TIMER_COUNTER4_compoutmodeD(unsigned char mode)
{
	switch(mode){
		case 0: break;
		case 1: dev()->portd->ddr.var |= (1 << 7); dev()->tc4->tccr4c.var |= (1 << COM4D0); break; // PD7
		case 2: dev()->portd->ddr.var |= (1 << 7); dev()->tc4->tccr4c.var |= (1 << COM4D1); break;
		case 3: dev()->portd->ddr.var |= (1 << 7); dev()->tc4->tccr4c.var |= ((1 << COM4D0) | (1 << COM4D1)); break;
		default: break;
	}
}
void TIMER_COUNTER4_clear_compoutmode(void)
{
	dev()->tc4->tccr4a.var &= ~((3 << COM4A0)|(3 << COM4B0));
	dev()->tc4->tccr4c.var &= ~((3 << COM4D0));
}

/*** Compare Registers ***/
void TIMER_COUNTER4_compareA(uint16_t compare){
	U_word hl = WriteHLByte(compare);
	dev()->tc4->tc4h.var = hl.par.h.var;
	dev()->tc4->ocr4a.var = hl.par.l.var;
}
void TIMER_COUNTER4_compareB(uint16_t compare){
	U_word hl = WriteHLByte(compare);
	dev()->tc4->tc4h.var = hl.par.h.var;
	dev()->tc4->ocr4b.var = hl.par.l.var;
}
void TIMER_COUNTER4_compareC(uint16_t compare){
	U_word hl = WriteHLByte(compare);
	dev()->tc4->tc4h.var = hl.par.h.var;
	dev()->tc4->ocr4c.var = hl.par.l.var;
}
void TIMER_COUNTER4_compareD(uint16_t compare){
	U_word hl = WriteHLByte(compare);
	dev()->tc4->tc4h.var = hl.par.h.var;
	dev()->tc4->ocr4d.var = hl.par.l.var; 
}

/*** Start / Stop ***/
uint8_t TIMER_COUNTER4_start(uint16_t prescaler)
{
	if(!timer4_state){
		dev()->tc4->tccr4b.var &= ~(7 << CS40);
		switch(prescaler){
			case 1: dev()->tc4->tccr4b.var |= (1 << CS40); break;
			case 2: dev()->tc4->tccr4b.var |= (1 << CS41); break;
			case 4: dev()->tc4->tccr4b.var |= (2 << CS40); break;
			case 8: dev()->tc4->tccr4b.var |= (3 << CS40); break;
			case 16: dev()->tc4->tccr4b.var |= (4 << CS40); break;
			case 32: dev()->tc4->tccr4b.var |= (5 << CS40); break;
			case 64: dev()->tc4->tccr4b.var |= (6 << CS40); break;
			case 128: dev()->tc4->tccr4b.var |= (7 << CS40); break;
			default: dev()->tc4->tccr4b.var |= (7 << CS40); break;
		}
		timer4_state = 85;
	}
	return timer4_state;
}
uint8_t TIMER_COUNTER4_stop(void)
{
	dev()->tc4->tccr4b.var &= ~(7 << CS40);
	timer4_state = 0;
	return timer4_state;
}

/*** Interrupts ***/
ISR(TIMER4_COMPA_vect){ if(atmega32u4_tc4_setup.callback.compa_vect){ atmega32u4_tc4_setup.callback.compa_vect(); } }
ISR(TIMER4_COMPB_vect){ if(atmega32u4_tc4_setup.callback.compb_vect){ atmega32u4_tc4_setup.callback.compb_vect(); } }
ISR(TIMER4_COMPD_vect){ if(atmega32u4_tc4_setup.callback.compd_vect){ atmega32u4_tc4_setup.callback.compd_vect(); } }
ISR(TIMER4_OVF_vect){  if(atmega32u4_tc4_setup.callback.ovf_vect){ atmega32u4_tc4_setup.callback.ovf_vect(); } }

/*** EOF ***/

