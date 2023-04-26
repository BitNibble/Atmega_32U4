/************************************************************************
	ATMEGA 32U4 REGISTERS
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega328 by ETT ET-BASE
Date: 04122022
Comment: 
	Virtual Image Atmega 32U4.
************************************************************************/
#ifndef _ATMEGA32U4_H_
	#define _ATMEGA32U4_H_

/*** Compiler ***/
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

/*** Working Frequency ***/
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

/*** Global Library ***/
#include <inttypes.h>

/*** Global Variable ***/

// Low Byte High Byte
typedef struct {
	uint8_t L; // Lower address
	uint8_t H; // Higher address
} HighLowByte;

// MAIN HARDWARE LAYER

// GPWR
typedef struct {
	uint8_t r0;
	uint8_t r1;
	uint8_t r2;
	uint8_t r3;
	uint8_t r4;
	uint8_t r5;
	uint8_t r6;
	uint8_t r7;
	uint8_t r8;
	uint8_t r9;
	uint8_t r10;
	uint8_t r11;
	uint8_t r12;
	uint8_t r13;
	uint8_t r14;
	uint8_t r15;
	uint8_t r16;
	uint8_t r17;
	uint8_t r18;
	uint8_t r19;
	uint8_t r20;
	uint8_t r21;
	uint8_t r22;
	uint8_t r23;
	uint8_t r24;
	uint8_t r25;
	uint8_t xl;
	uint8_t xh;
	uint8_t yl;
	uint8_t yh;
	uint8_t zl;
	uint8_t zh;
}Atmega32u4GPWR_TypeDef;

// Analog Comparator (AC)
typedef struct {
	uint8_t acsr; // 0x50
	uint8_t fill[42]; // (0x7B - 0x50) - 1
	uint8_t adcsrb; // 0x7B
	uint8_t didr1; // 0x7F
}Atmega32u4AnalogComparator_TypeDef;

// Analog to Digital Converter (ADC)
typedef struct {
	HighLowByte adc; // 0x78 0x79
	uint8_t adcsra; // 0x7A
	uint8_t adscrb; // 0x7B
	uint8_t admux; // 0x7C
	uint8_t didr2; // 0x7D
	uint8_t didr0; // 0x7E
} Atmega32u4AnalogToDigitalConverter_TypeDef;

// Bootloader (BOOT_LOAD)
typedef struct {
	HighLowByte spmcsr; // 0x57 
} Atmega32u4Bootloader_TypeDef;

// CPU Register (CPU)
typedef struct {
	uint8_t gpior0; // 0x3E
	uint8_t fill1[11]; // (4A - 3E) - 1
	uint8_t gpior1; // 0x4A
	uint8_t gpior2; // 0x4B
	uint8_t fill2[7]; // (53 4B) - 1
	uint8_t smcr; // 0x53
	uint8_t mcusr; // 0x54
	uint8_t mcucr; // 0x55
	uint8_t fill3[5]; // (5B - 55) - 1
	uint8_t rampz; // 0x5B
	uint8_t eind; // 0x5C
	HighLowByte sp; // 0x5D 0x5E
	uint8_t sreg; // 0x5F
	uint8_t fill4; // (61 - 5F) - 1
	uint8_t clkpr; // 0x61
	uint8_t fill5[2]; // (64 - 61) - 1
	uint8_t prr0; // 0x64
	uint8_t prr1; // 0x65
	uint8_t osccal; // 0x66
	uint8_t rcctrl; // 0x67
	uint8_t fill6[93]; // (C5 - 67) - 1
	uint8_t clksel0; // 0xC5
	uint8_t clksel1; // 0xC6
	uint8_t clksta; // 0xC7
} Atmega32u4CPURegister_TypeDef;

// EEPROM (EEPROM)
typedef struct {
	uint8_t eecr; // 0x3F
	uint8_t eedr; // 0x40
	uint16_t eear; // 0x41
} Atmega32u4Eeprom_TypeDef;

// External Interrupts (EXINT)
typedef struct {
	uint8_t pcifr; // 0x3B
	uint8_t eifr; // 0x3C
	uint8_t eimsk; // 0x3D
	uint8_t fill1[42]; // (68 - 3d) - 1
	uint8_t pcicr; // 0x68
	uint8_t eicra; // 0x69
	uint8_t eicrb; // 0x6A
	uint8_t pcmsk0; // 0x6B
} Atmega32u4ExternalInterrupts_TypeDef;

// I/O Port (PORTB)
typedef struct {
	uint8_t pin; // 0x23
	uint8_t ddr; // 0x24
	uint8_t port; //0x25
}Atmega32u4PORTB_TypeDef;

// I/O Port (PORTC)
typedef struct {
	uint8_t pin; // 0x26
	uint8_t ddr; // 0x27
	uint8_t port; // 0x28
}Atmega32u4PORTC_TypeDef;

// I/O Port (PORTD)
typedef struct {
	uint8_t pin; // 0x29
	uint8_t ddr; // 0x2A
	uint8_t port; // 0x2B
}Atmega32u4PORTD_TypeDef;

// I/O Port (PORTE)
typedef struct {
	uint8_t pin; // 0x2C
	uint8_t ddr; // 0x2D
	uint8_t port; // 0x2E
}Atmega32u4PORTE_TypeDef;

// I/O Port (PORTF)
typedef struct {
	uint8_t pin; // 0x2F
	uint8_t ddr; // 0x30
	uint8_t port; // 0x31
}Atmega32u4PORTF_TypeDef;

// JTAG Interface (JTAG)
typedef struct {
	uint8_t ocdr; // 0x51
	uint8_t fill1[2]; // (54 - 51) - 1
	uint8_t mcusr; // 0x54
	uint8_t mcucr; // 0x55
}Atmega32u4JtagInterface_TypeDef;

// Phase Locked Loop (PLL)
typedef struct {
	uint8_t pllcsr; // 0x49
	uint8_t fill1[2]; // (52 - 49) - 1
	uint8_t pllfrq; // 0x52
}Atmega32u4PhaseLockedLoop_TypeDef;

// Serial Peripheral Interface (SPI)
typedef struct {
	uint8_t spcr; // 0x4C
	uint8_t spsr; // 0x4D
	uint8_t spdr; // 0x4E
} Atmega32u4SerialPeripherialInterface_TypeDef;

// Timer/Counter, 10-bit (TC4)
typedef struct {
	uint8_t tifr4; // 0x39
	uint8_t fill1[56]; // (72 - 39) - 1
	uint8_t timsk4; // 0x72
	uint8_t fill2[75];// (BE - 72) - 1
	uint8_t tcnt4; // 0xBE
	uint8_t tc4h; // 0xBF
	uint8_t tccr4a; // 0xC0
	uint8_t tccr4b; // 0xC1
	uint8_t tccr4c; // 0xC2
	uint8_t tccr4d; // 0xC3
	uint8_t tccr4e; // 0xC4
	uint8_t fill3[10]; // (CF - C4) - 1
	uint8_t ocr4a; // 0xCF
	uint8_t ocr4b; // 0xD0
	uint8_t ocr4c; // 0xD1
	uint8_t ocr4d; // 0xD2
	uint8_t fill4; // (D4 - D2) - 1
	uint8_t dt4; // 0xD4
} Atmega32u4TimerCounter4_TypeDef;

// Timer/Counter, 16-bit (TC1)
typedef struct {
	uint8_t tifr1; // 0x36
	uint8_t fill1[56]; // (6F - 36) - 1
	uint8_t timsk1; // 0x6F
	uint8_t fill2[16]; // (80 - 6F) - 1
	uint8_t tccr1a; // 0x80
	uint8_t tccr1b; // 0x81
	uint8_t tccr1c; // 0x82
	uint8_t fill3; // (84 - 82) - 1
	HighLowByte tcnt1; // 0x84 0x85
	HighLowByte icr1; // 0x86 0x87
	HighLowByte ocr1a; // 0x88 0x89
	HighLowByte ocr1b; // 0x8A 0x8B
	HighLowByte ocr1c; // 0x8C 0x8D
} Atmega32u4TimerCounter1_TypeDef;

// Timer/Counter, 16-bit (TC3)
typedef struct {
	uint8_t tifr3; // 0x38
	uint8_t fill1[56]; // (71 - 38) - 1
	uint8_t timsk3; // 0x71
	uint8_t fill2[30]; // (90 - 71) - 1
	uint8_t tccr3a; // 0x90
	uint8_t tccr3b; // 0x91
	uint8_t tccr3c; // 0x92
	uint8_t fill3; // (94 - 92) - 1
	HighLowByte tcnt3; // 0x94 0x95
	HighLowByte icr3; // 0x96 0x97
	HighLowByte ocr3a; // 0x98 0x99
	HighLowByte ocr3b; // 0x9A 0x9B
	HighLowByte ocr3c; // 0x9C 0x9D
} Atmega32u4TimerCounter3_TypeDef;

// Timer/Counter, 8-bit (TC0)
typedef struct {
	uint8_t tifr0; // 0x35
	uint8_t fill1[13]; // (43 - 35) - 1
	uint8_t gtccr; // 0x43
	uint8_t tccr0a; // 0x44
	uint8_t tccr0b; // 0x45
	uint8_t tcnt0; // 0x46
	uint8_t ocr0a; // 0x47
	uint8_t ocr0b; // 0x48
	uint8_t fill2[37]; // (6E - 48) - 1
	uint8_t timsk0; // 0x6E
} Atmega32u4TimerCounter0_TypeDef;

// Two Wire Serial Interface (TWI)
typedef struct {
	uint8_t twbr; // 0xB8
	uint8_t twsr; // 0xB9
	uint8_t twar; // 0xBA
	uint8_t twdr; // 0xBB
	uint8_t twcr; // 0xBC
	uint8_t twamr; // 0xBD
} Atmega32u4TwoWireSerialInterface_TypeDef;

// USART (USART1)
typedef struct {
	uint8_t ucsr1a; // 0xC8
	uint8_t ucsr1b; // 0xC9
	uint8_t ucsr1c; // 0xCA
	uint8_t ucsr1d; // 0xCB
	HighLowByte ubrr1; // 0xCC 0xCD
	uint8_t udr1; // 0xCE
} Atmega32u4Usart_TypeDef;

// USB Device Register (USB_DEVICE)
typedef struct {
	uint8_t uhwcon; // 0xD7
	uint8_t usbcon; // 0xD8
	uint8_t usbsta; // 0xD9
	uint8_t usbint; // 0xDA
	uint8_t fill1[5]; // (E0 - DA) - 1
	uint8_t udcon; //0xE0
	uint8_t udint; // 0xE1
	uint8_t udien; // 0xE2
	uint8_t udaddr; // 0xE3
	HighLowByte udfnum; // 0xE4 0xE5
	uint8_t udmfn; // 0xE6
	uint8_t fill2; // (E8 - E6) - 1
	uint8_t ueintx; // 0xE8
	uint8_t uenum; // 0xE9
	uint8_t uerst; // 0xEA
	uint8_t ueconx; // 0xEB
	uint8_t uecfg0x; // 0xEC
	uint8_t uecfg1x; // 0xED
	uint8_t uesta0x; // 0xEE
	uint8_t uesta1x; // 0xEF
	uint8_t ueienx; // 0xF0
	uint8_t uedatx; // 0xF1
	uint8_t uebclx; // 0xF2
	uint8_t uebchx; // 0xF3
	uint8_t ueint; // 0xF4
} Atmega32u4UsbDeviceRegister_TypeDef;

// Watchdog Timer (WDT)
typedef struct {
	uint8_t wdtcr; // 0x60
} Atmega32u4WatchdogTimer_TypeDef;

#endif
/***EOF***/

