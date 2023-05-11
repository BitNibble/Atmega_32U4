/***
 * main.c
 *
 * Created: 11/29/2022 7:54:12 PM
 *  Author: sergi
 *	License: GNU General Public License
 ***/ 
/*** Working Frequency ***/
#define F_CPU 8000000UL

/*** Compiler ***/
//#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
//	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
//#endif

/*
** library
*/
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "atmega32u4mapping.h"
#include "explode.h"
#include "keypad.h"

ATMEGA32U4 mega;
void PORTINIC(void);

// CODE AREA
int main(void)
{
	mega = ATMEGA32U4enable();
	PORTINIC();
	// Power up Timer 1
	mega.cpu.reg->prr0 &= ~(1 << 3);
	// Timer 1
	// wavegenmode normal
	mega.tc1.reg->tccr1a &= ~((1 << WGM11) | (1 << WGM10));
	mega.tc1.reg->tccr1b &= ~((1 << WGM13) | (1 << WGM12));
	// interrupt overflow
	mega.tc1.reg->mask->timsk1 |= (1 << TOIE1);
	// compoutmodeA disconnected
	mega.tc1.reg->tccr1a &= ~((1 << COM1A0) | (1 << COM1A1));
	// compoutmodeB disconnected
	mega.tc1.reg->tccr1a &= ~((1 << COM1B0) | (1 << COM1B1));
	// compoutmodeB disconnected
	mega.tc1.reg->tccr1a &= ~((1 << COM1C0) | (1 << COM1C1));
	// compareA
	//mega.tc1.reg->ocr1a = mega.writehlbyte(0x00FF);
	// compareB
	//mega.tc1.reg->ocr1b = mega.writehlbyte(0x00FF);
	// compareC
	//mega.tc1.reg->ocr1c = mega.writehlbyte(0x00FF);
	// prescaler
	//mega.tc1.reg->tccr1b |= (5 << CS10); // 1024
	mega.tc1.reg->tccr1b |= (1 << CS10); // 1

	// Turn on all Interrupt Hnadler
	mega.cpu.reg->sreg |= (1 << 7);
	
	/***LOOP***/
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

void PORTINIC(void){
	mega.portb.reg->ddr |= (1 << 7);
	mega.portb.reg->port |= (1 << 7);
}

ISR(TIMER1_OVF_vect){
	mega.portb.reg->port ^= (1 << 7);
}