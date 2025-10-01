/********************************************************************
	ATMEGA 32U4 MAPPING
Author: <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega32U4
Date: 26092025
********************************************************************/
#ifndef _ATMEGA32U4_H_
	#define _ATMEGA32U4_H_
	
/*** Compiler ***/
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

/*** Global Library ***/
#include "atmega32U4_instance.h"

/*** Global Header ***/
ATMEGA32U4* atmega32u4(void);

/*** Common ***/
uint16_t ReadHLByte(U_word reg);
uint16_t ReadLHByte(U_word reg);
U_word WriteHLByte(uint16_t val);
U_word WriteLHByte(uint16_t val);
uint16_t SwapByte(uint16_t num);
uint8_t ByteMask(uint8_t target, uint8_t mask);
void ByteSet(uint8_t* target, uint8_t set);
void ByteClear(uint8_t* target, uint8_t clear);
uint8_t ByteShiftright(uint8_t target, uint8_t shift);
uint8_t ByteShiftleft(uint8_t target, uint8_t shift);
/******/
void ClockPrescalerSelect(volatile uint8_t prescaler);
void MoveInterruptsToBoot(void);
void MoveInterruptsToSram(void);

#endif
/***EOF***/

