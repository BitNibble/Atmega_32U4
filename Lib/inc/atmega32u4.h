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

/*** Library ***/
#include <avr/io.h>
#include "atmega32U4_instance.h"
#include <avr/boot.h>
#include <avr/fuse.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*******************************************************************/
/********************** ATMEGA 32U4 IMAGE **************************/
/*******************************************************************/
typedef struct {
	//		Second Layer
	Atmega32U4_GPIAR* const gpiar;
	Atmega32U4_AnalogComparator* const ac;
	Atmega32U4_AnalogToDigitalConverter* const adc;
	Atmega32U4_Bootloader* const boot_load;
	Atmega32U4_CPURegister* const cpu;
	Atmega32U4_Eeprom* const eeprom;
	Atmega32U4_ExternalInterrupt* const exint;
	Atmega32U4_PORTB* const portb;
	Atmega32U4_PORTC* const portc;
	Atmega32U4_PORTD* const portd;
	Atmega32U4_PORTE* const porte;
	Atmega32U4_PORTF* const portf;
	Atmega32U4_JtagInterface* const jtag;
	Atmega32U4_PhaseLockedLoop* const pll;
	Atmega32U4_SerialPeripherialInterface* const spi;
	Atmega32U4_TimerCounter4* const tc4;
	Atmega32U4_TimerCounter1* const tc1;
	Atmega32U4_TimerCounter3* const tc3;
	Atmega32U4_TimerCounter0* const tc0;
	Atmega32U4_TwoWireSerialInterface* const twi;
	Atmega32U4_Usart1* const usart1;
	Atmega32U4_UsbDeviceRegister* const usb_device;
	Atmega32U4_WatchdogTimer* const wdt;
} ATMEGA32U4;

/*** Global Header ***/
ATMEGA32U4* dev(void);

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

