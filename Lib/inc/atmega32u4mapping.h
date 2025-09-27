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
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <inttypes.h>

/*********************************************************/
/****************** Include Switches  ********************/
/*********************************************************/
// To be Selected by the User
// MODULES
#define _EEPROM_MODULE_

/*********************************************************/
/******************** USER Includes **********************/
/*********************************************************/
// MODULES
#ifdef _ANALOG_MODULE_
#include "atmega32u4analog.h"
//#else
//	#warning "NO ANALOG MODULE"
#endif
#ifdef _EEPROM_MODULE_
#include "atmegaeeprom.h"
//#else
//	#warning "NO EEPROM MODULE"
#endif
#ifdef _INTERRUPT_MODULE_
#include "atmega32u4interrupt.h"
//#else
//	#warning "NO INTERRUPT MODULE"
#endif
#ifdef _TIMER_MODULE_
#include "atmega32u4timer.h"
//#else
//	#warning "NO TIMER MODULE"
#endif
#ifdef _TWI_MODULE_
#include "atmega32u4twi.h"
//#else
//	#warning "NO TWI MODULE"
#endif
#ifdef _SPI_MODULE_
#include "atmega32u4spi.h"
//#else
//	#warning "NO SPI MODULE"
#endif
#ifdef _USART1_MODULE_
#include "atmega32u4uart.h"
//#else
//	#warning "NO UART MODULE"
#endif
/*******************************************************************/
/*******************************************************************/
// ATMEGA 32U4 IMAGE
typedef struct {
	//		Second Layer
	Atmega32U4_GPIAR* gpiar;
	Atmega32U4_AnalogComparator* ac;
	Atmega32U4_AnalogToDigitalConverter* adc;
	#if defined(_ANALOG_MODULE_)
		ANALOG (*adc_enable)( uint8_t Vreff, uint8_t Divfactor, int n_channel, ... );
	#endif
	Atmega32U4_Bootloader* boot_load;
	Atmega32U4_CPURegister* cpu;
	Atmega32U4_Eeprom* eeprom;
	#if defined(_EEPROM_MODULE_)
		EEPROM (*eeprom_enable)(void);
	#endif
	Atmega32U4_ExternalInterrupt* exint;
	#if defined(_INTERRUPT_MODULE_)
		INTERRUPT (*exint_enable)(void);
	#endif
	Atmega32U4_PORTB* portb;
	Atmega32U4_PORTC* portc;
	Atmega32U4_PORTD* portd;
	Atmega32U4_PORTE* porte;
	Atmega32U4_PORTF* portf;
	Atmega32U4_JtagInterface* jtag;
	Atmega32U4_PhaseLockedLoop* pll;
	Atmega32U4_SerialPeripherialInterface* spi;
	#if defined(_SPI_MODULE_)
		SPI (*spi_enable)(uint8_t master_slave_select, uint8_t data_order,  uint8_t data_modes, uint8_t prescaler);
	#endif
	Atmega32U4_TimerCounter4* tc4;
	#if defined(_TIMER_MODULE_)
		TIMER_COUNTER4 (*tc4_enable)(unsigned char wavegenmode, unsigned char interrupt);
	#endif
	Atmega32U4_TimerCounter1* tc1;
	#if defined(_TIMER_MODULE_)
		TIMER_COUNTER1 (*tc1_enable)(unsigned char wavegenmode, unsigned char interrupt);
	#endif
	Atmega32U4_TimerCounter3* tc3;
	#if defined(_TIMER_MODULE_)
		TIMER_COUNTER3 (*tc3_enable)(unsigned char wavegenmode, unsigned char interrupt);
	#endif
	Atmega32U4_TimerCounter0* tc0;
	#if defined(_TIMER_MODULE_)
		TIMER_COUNTER0 (*tc0_enable)(unsigned char wavegenmode, unsigned char interrupt);
	#endif
	Atmega32U4_TwoWireSerialInterface* twi;
	#if defined(_TWI_MODULE_)
		TWI (*twi_enable)(uint8_t atmega_ID, uint8_t prescaler);
	#endif
	Atmega32U4_Usart1* usart1;
	#if defined(_USART1_MODULE_)
		UART (*usart1_enable)(unsigned int baudrate, unsigned int FDbits, unsigned int Stopbits, unsigned int Parity );
	#endif
	Atmega32U4_UsbDeviceRegister* usb_device;
	Atmega32U4_WatchdogTimer* wdt;
	//		Function Pointer
	uint16_t (*readhlbyte)(U_word reg);
	uint16_t (*readlhbyte)(U_word reg);
	U_word (*writehlbyte)(uint16_t val);
	U_word (*writelhbyte)(uint16_t val);
	uint16_t (*swapbyte)(uint16_t num);
	uint8_t (*byte_mask)(uint8_t target, uint8_t mask);
	void (*byte_set)(uint8_t* target, uint8_t set);
	void (*byte_clear)(uint8_t* target, uint8_t clear);
	uint8_t (*byte_shiftright)(uint8_t target, uint8_t shift);
	uint8_t (*byte_shiftleft)(uint8_t target, uint8_t shift);
	/******/
	void (*Clock_Prescaler_Select)(volatile uint8_t prescaler);
	void (*Move_Interrupts_To_Boot)(void);
	void (*Move_Interrupts_To_Sram)(void);
} ATMEGA32U4;

/*** Global Header ***/
ATMEGA32U4 ATMEGA32U4enable(void);

#endif
/***EOF***/

