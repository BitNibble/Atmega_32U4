/************************************************************************
	ATMEGA 32U4 INSTANCE
Author: <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega32U4 by Arduino
Date: 26092025
************************************************************************/
#ifndef _ATMEGA32U4_INSTANCE_H_
	#define _ATMEGA32U4_INSTANCE_H_

/*** Library ***/
#include "atmega32u4_register.h"
#include <avr/sfr_defs.h>

/*** Define & Macro ***/
#define Atmega32U4_GPWR_Address 0x0000
#define Atmega32U4_AnalogComparator_Address 0x0050
#define Atmega32U4_AnalogToDigitalConverter_Address 0x0078
#define Atmega32U4_Bootloader_Address 0x0057
#define Atmega32U4_CPURegister_Address 0x003E
#define Atmega32U4_Eeprom_Address 0x003F
#define Atmega32U4_ExternalInterrupt_Address 0x003B
#define Atmega32U4_PORTB_Address 0x0023
#define Atmega32U4_PORTC_Address 0x0026
#define Atmega32U4_PORTD_Address 0x0029
#define Atmega32U4_PORTE_Address 0x002C
#define Atmega32U4_PORTF_Address 0x002F
#define Atmega32U4_JtagInterface_Address 0x0051
#define Atmega32U4_PhaseLockedLoop_Address 0x0049
#define Atmega32U4_SerialPeripherialInterface_Address 0x004C
#define Atmega32U4_TimerCounter4_Address 0x0039
#define Atmega32U4_TimerCounter1_Address 0x0036
#define Atmega32U4_TimerCounter3_Address 0x0038
#define Atmega32U4_TimerCounter0_Address 0x0035
#define Atmega32U4_TwoWireSerialInterface_Address 0x00B8
#define Atmega32U4_Usart1_Address 0x00C8
#define Atmega32U4_UsbDeviceRegister_Address 0x00D7
#define Atmega32U4_WatchdogTimer_Address 0x0060

//		MAIN HARDWARE LAYER
// GPWR
typedef volatile struct {
	uint8_t r0; // 0x00
	uint8_t r1; // 0x01
	uint8_t r2; // 0x02
	uint8_t r3; // 0x03
	uint8_t r4; // 0x04
	uint8_t r5; // 0x05
	uint8_t r6; // 0x06
	uint8_t r7; // 0x07
	uint8_t r8; // 0x08
	uint8_t r9; // 0x09
	uint8_t r10; // 0x0A
	uint8_t r11; // 0x0B
	uint8_t r12; // 0x0C
	uint8_t r13; // 0x0D
	uint8_t r14; // 0x0E
	uint8_t r15; // 0x0F
	uint8_t r16; // 0x10
	uint8_t r17; // 0x11
	uint8_t r18; // 0x12
	uint8_t r19; // 0x13
	uint8_t r20; // 0x14
	uint8_t r21; // 0x15
	uint8_t r22; // 0x16
	uint8_t r23; // 0x17
	uint8_t r24; // 0x18
	uint8_t r25; // 0x19
	U_word X; // 0x1A 0x1B
	U_word Y; // 0x1C 0x1D
	U_word Z; // 0x1E 0x1F
} Atmega32U4GPWR_TypeDef;

// I/O Port (PORTB)
typedef volatile struct {
	PINB_type pin; // 0x23
	DDRB_type ddr; // 0x24
	PORTB_type port; //0x25
} Atmega32U4PORTB_TypeDef;

// I/O Port (PORTC)
typedef volatile struct {
	PINC_type pin; // 0x26
	DDRC_type ddr; // 0x27
	PORTC_type port; // 0x28
} Atmega32U4PORTC_TypeDef;

// I/O Port (PORTD)
typedef volatile struct {
	PIND_type pin; // 0x29
	DDRD_type ddr; // 0x2A
	PORTD_type port; // 0x2B
} Atmega32U4PORTD_TypeDef;

// I/O Port (PORTE)
typedef volatile struct {
	PINE_type pin; // 0x2C
	DDRE_type ddr; // 0x2D
	PORTE_type port; // 0x2E
} Atmega32U4PORTE_TypeDef;

// I/O Port (PORTF)
typedef volatile struct {
	PINF_type pin; // 0x2F
	DDRF_type ddr; // 0x30
	PORTF_type port; // 0x31
} Atmega32U4PORTF_TypeDef;

// EEPROM (EEPROM)
typedef volatile struct {
	EECR_type eecr; // 0x3F
	EEDR_type eedr; // 0x40
	EEAR_type eear; // 0x41 0x42
} Atmega32U4Eeprom_TypeDef;

// Timer/Counter, 8-bit (TC0)
typedef volatile struct {
	TIFR0_type tifr0; // 0x35
	uint8_t fill1[13];
	GTCCR_type gtccr; // 0x43
	TCCR0A_type tccr0a; // 0x44
	TCCR0B_type tccr0b; // 0x45
	TCNT0_type tcnt0; // 0x46
	OCR0A_type ocr0a; // 0x47
	OCR0B_type ocr0b; // 0x48
	uint8_t fill2[37];
	TIMSK0_type timsk0; // 0x6E
} Atmega32U4TimerCounter0_TypeDef;

// Serial Peripheral Interface (SPI)
typedef volatile struct {
	SPCR_type spcr; // 0x4C
	SPSR_type spsr; // 0x4D
	SPDR_type spdr; // 0x4E
} Atmega32U4SerialPeripherialInterface_TypeDef;

// Analog Comparator (AC)
typedef volatile struct {
	ACSR_type acsr; // 0x50
	uint8_t fill1[42];
	ADCSRB_type adcsrb; // 0x7B
	uint8_t fill2[3];
	DIDR1_type didr1; // 0x7F
} Atmega32U4AnalogComparator_TypeDef;

// JTAG Interface (JTAG)
typedef volatile struct {
	OCDR_type ocdr; // 0x51
	uint8_t fill[2];
	MCUSR_type mcusr; // 0x54
	MCUCR_type mcucr; // 0x55
} Atmega32U4JtagInterface_TypeDef;

// Phase Locked Loop (PLL)
typedef volatile struct {
	PLLCSR_type pllcsr; // 0x49
	uint8_t fill[8];
	PLLFRQ_type pllfrq; // 0x52
} Atmega32U4PhaseLockedLoop_TypeDef;

// CPU Register (CPU)
typedef volatile struct {
	GPIOR0_type gpior0; // 0x3E
	uint8_t fill1[11];
	GPIOR1_type gpior1; // 0x4A
	GPIOR2_type gpior2; //0x4B
	uint8_t fill2[7];
	SMCR_type smcr; // 0x53
	MCUSR_type mcusr; // 0x54
	MCUCR_type mcucr; // 0x55
	uint8_t fill3[5];
	RAMPZ_type rampz; // 0x5B
	uint8_t eind; // 0x5C
	SP_type sp; // 0x5D 0x5E
	SREG_type sreg; // 0x5F
	uint8_t fill4;
	CLKPR_type clkpr; // 0x61
	uint8_t fill5[2];
	PRR0_type prr0; // 0x64
	PRR1_type prr1; // 0x65
	OSCAL_type osccal; // 0x66
	RCCTRL_type rcctrl; // 0x67
	uint8_t fill6[93];
	CLKSEL0_type clksel0; // 0xC5
	CLKSEL1_type clksel1; // 0xC6
	CLKSTA_type clksta; // 0xC7
} Atmega32U4CPURegister_TypeDef;

// Boot loader (BOOT_LOAD)
typedef volatile struct {
	SPMCSR_type spmcsr; // 0x57
} Atmega32U4Bootloader_TypeDef;

// Watchdog Timer (WDT)
typedef volatile struct {
	WDTCSR_type wdtcr; // 0x60
} Atmega32U4WatchdogTimer_TypeDef;

// External Interrupts (EXINT)
typedef volatile struct {
	PCIFR_type pcifr; // 0x3B
	EIFR_type eifr; // 0x3C
	EIMSK_type eimsk; // 0x3D
	uint8_t fill[42];
	PCICR_type pcicr; // 0x68
	EICRA_type eicra; // 0x69
	EICRB_type eicrb; // 0x6A
	PCMSK0_type pcmsk0; // 0x6B
} Atmega32U4ExternalInterrupt_TypeDef;

// Analog to Digital Converter (ADC)
typedef volatile struct {
	ADC_type adc; // 0x78 0x79
	ADCSRA_type adcsra; // 0x7A
	ADCSRB_type adcsrb; // 0x7B
	ADMUX_type admux; // 0x7C
	DIDR2_type didr2; // 0x7D
	DIDR0_type didr0; // 0x7E
} Atmega32U4AnalogToDigitalConverter_TypeDef;

// Timer/Counter, 16-bit (TC1)
typedef volatile struct {
	TIFR1_type tifr1; // 0x36
	uint8_t fill1[56];
	TIMSK1_type timsk1; // 0x6F
	uint8_t fill2[16];
	TCCR1A_type tccr1a; // 0x80
	TCCR1B_type tccr1b; // 0x81
	TCCR1C_type tccr1c; // 0x82
	uint8_t fill3;
	TCNT1_type tcnt1; // 0x84 0x85
	ICR1_type icr1; // 0x86 0x87
	OCR1A_type ocr1a; // 0x88 0x89
	OCR1B_type ocr1b; // 0x8A 0x8B
	OCR1C_type ocr1c; // 0x8C 0x8D
} Atmega32U4TimerCounter1_TypeDef;

// Timer/Counter, 16-bit (TC3)
typedef volatile struct {
	TIFR3_type tifr3; // 0x38
	uint8_t fill1[56];
	TIMSK3_type timsk3; // 0x71
	uint8_t fill2[30];
	TCCR3A_type tccr3a; // 0x90
	TCCR3B_type tccr3b; // 0x91
	TCCR3C_type tccr3c; // 0x92
	uint8_t fill3;
	TCNT3_type tcnt3; // 0x94 0x95
	ICR3_type icr3; // 0x96 0x97
	OCR3A_type ocr3a; // 0x98 0x99
	OCR3B_type ocr3b; // 0x9A 0x9B
	OCR3C_type ocr3c; // 0x9C 0x9D
} Atmega32U4TimerCounter3_TypeDef;

// Two Wire Serial Interface (TWI)
typedef volatile struct {
	TWBR_type twbr; // 0xB8
	TWSR_type twsr; // 0xB9
	TWAR_type twar; // 0xBA
	TWDR_type twdr; // 0xBB
	TWCR_type twcr; // 0xBC
	TWAMR_type twamr; // 0xBD
} Atmega32U4TwoWireSerialInterface_TypeDef;

// Timer/Counter, 10-bit (TC4)
typedef volatile struct {
	TIFR4_type tifr4; // 0x39
	uint8_t fill1[56];
	TIMSK4_type timsk4; // 0x72
	uint8_t fill2[75];
	TCNT4_type tcnt4; // 0xBE
	TCNT4H_type tc4h; // 0xBF
	TCCR4A_type tccr4a; // 0xC0
	TCCR4B_type tccr4b; // 0xC1
	TCCR4C_type tccr4c; // 0xC2
	TCCR4D_type tccr4d; // 0xC3
	TCCR4E_type tccr4e; // 0xC4
	uint8_t fill3[10];
	OCR4A_type ocr4a; // 0xCF
	OCR4B_type ocr4b; // 0xD0
	OCR4C_type ocr4c; // 0xD1
	OCR4D_type ocr4d; // 0xD2
	uint8_t fill4;
	DT4_type dt4; // 0xD4
} Atmega32U4TimerCounter4_TypeDef;

// USART (USART1)
typedef volatile struct {
	UCSR1A_type ucsr1a; // 0xC8
	UCSR1B_type ucsr1b; // 0xC9
	UCSR1C_type ucsr1c; // 0xCA
	UCSR1D_type ucsr1d; // 0xCB
	UBRR1_type ubrr1; // 0xCC 0xCD
	UDR1_type udr1; // 0xCE
} Atmega32U4Usart1_TypeDef;

// USB Device Register (USB_DEVICE)
typedef volatile struct {
	UHWCON_type uhwcon; // 0xD7
	USBCON_type usbcon; // 0xD8
	USBSTA_type usbsta; // 0xD9
	USBINT_type usbint; // 0xDA
	uint8_t fill1[5];
	UDCON_type udcon; //0xE0
	UDINT_type udint; // 0xE1
	UDIEN_type udien; // 0xE2
	UDADDR_type udaddr; // 0xE3
	UDFNUM_type udfnum; // 0xE4 0xE5
	UDMFN_type udmfn; // 0xE6
	uint8_t fill2;
	UEINTX_type ueintx; // 0xE8
	UENUM_type uenum; // 0xE9
	UERST_type uerst; // 0xEA
	UECONX_type ueconx; // 0xEB
	UECFG0X_type uecfg0x; // 0xEC
	UECFG1X_type uecfg1x; // 0xED
	UESTA0X_type uesta0x; // 0xEE
	UESTA1X_type uesta1x; // 0xEF
	UEIENX_type ueienx; // 0xF0
	UEDATX_type uedatx; // 0xF1
	UEBCLX_type uebclx; // 0xF2
	UEBCHX_type uebchx; // 0xF3
	UEINT_type ueint; // 0xF4
} Atmega32U4UsbDeviceRegister_TypeDef;

#endif
/***EOF***/

