/*********************************************************************
	ATMEGA 32U4 MAPPING
Author: <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega32U4
Date: 26092025
*********************************************************************/
#ifndef _ATMEGA32U4MAPPING_H_
	#define _ATMEGA32U4MAPPING_H_
	
/*** Compiler ***/
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

/*** Global Library ***/
#include "atmega32U4_instance.h"

// ATMEGA 32U4 IMAGE
typedef struct {
	//		Second Layer
	Atmega32U4_GPIAR* gpiar;
	Atmega32U4_AnalogComparator* ac;
	Atmega32U4_AnalogToDigitalConverter* adc;
	Atmega32U4_Bootloader* boot_load;
	Atmega32U4_CPURegister* cpu;
	Atmega32U4_Eeprom* eeprom;
	Atmega32U4_ExternalInterrupt* exint;
	Atmega32U4_PORTB* portb;
	Atmega32U4_PORTC* portc;
	Atmega32U4_PORTD* portd;
	Atmega32U4_PORTE* porte;
	Atmega32U4_PORTF* portf;
	Atmega32U4_JtagInterface* jtag;
	Atmega32U4_PhaseLockedLoop* pll;
	Atmega32U4_SerialPeripherialInterface* spi;
	Atmega32U4_TimerCounter4* tc4;
	Atmega32U4_TimerCounter1* tc1;
	Atmega32U4_TimerCounter3* tc3;
	Atmega32U4_TimerCounter0* tc0;
	Atmega32U4_TwoWireSerialInterface* twi;
	Atmega32U4_Usart1* usart1;
	Atmega32U4_UsbDeviceRegister* usb_device;
	Atmega32U4_WatchdogTimer* wdt;
} ATMEGA32U4;

/*** Global Header ***/
ATMEGA32U4 atmega32u4(void);

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

