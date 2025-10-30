/********************************************************************
	ATMEGA 32U4 REGISTER
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega32U4
Date:     26092025
********************************************************************/
#ifndef _ATMEGA32U4_REGISTER_H_
	#define _ATMEGA32U4_REGISTER_H_

/*** Library ***/
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

/*** Base Typedef ***/
typedef union {
	struct { 
		uint8_t bit0:1,bit1:1,bit2:1,bit3:1,bit4:1,bit5:1,bit6:1,bit7:1; 
	} par;
	uint8_t var;
} U_byte;

typedef union {
	struct{
		U_byte l, h;
	} par;
	uint16_t var;
} U_word;

/*** REGISTER ***/
// 0x20 - Reserved
// 0x21 - Reserved
// 0x22 - Reserved
// 0x23 - PINB (U_byte)
typedef U_byte PINB_type;
// 0x24 - DDRB (U_byte)
typedef U_byte DDRB_type;
// 0x25 - PORTB (U_byte)
typedef U_byte PORTB_type;
// 0x26 - PINC (U_byte)
typedef U_byte PINC_type;
// 0x27 - DDRC (U_byte)
typedef U_byte DDRC_type;
// 0x28 - PORTC (U_byte)
typedef U_byte PORTC_type;
// 0x29 - PIND (U_byte)
typedef U_byte PIND_type;
// 0x2A - DDRD (U_byte)
typedef U_byte DDRD_type;
// 0x2B - PORTD (U_byte)
typedef U_byte PORTD_type;
// 0x2C - PINE (U_byte)
typedef U_byte PINE_type;
// 0x2D - DDRE (U_byte)
typedef U_byte DDRE_type;
// 0x2E - PORTE (U_byte)
typedef U_byte PORTE_type;
// 0x2F - PINF (U_byte)
typedef U_byte PINF_type;
// 0x30 - DDRF (U_byte)
typedef U_byte DDRF_type;
// 0x31 - PORTF (U_byte)
typedef U_byte PORTF_type;
// 0x32 - Reserved
// 0x33 - Reserved
// 0x34 - Reserved
// 0x35 - TIFR0 (Timer/Counter0 Interrupt Flag Register)
typedef union {
	struct {
		uint8_t tov0 : 1;
		uint8_t ocf0a : 1;
		uint8_t ocf0b : 1;
		uint8_t       : 5;
	} par;
	uint8_t var;
} TIFR0_type;
// 0x36 - TIFR1 (Timer/Counter1 Interrupt Flag Register)
typedef union {
	struct {
		uint8_t tov1 : 1;
		uint8_t ocf1a : 1;
		uint8_t ocf1b : 1;
		uint8_t ocf1c : 1;
		uint8_t       : 1;
		uint8_t icf1 : 1;
		uint8_t      : 2;
	} par;
	uint8_t var;
} TIFR1_type;
// 0x37 - Reserved
// 0x38 - TIFR3 (Timer/Counter3 Interrupt Flag Register)
typedef union {
	struct {
		uint8_t tov3 : 1;
		uint8_t ocf3a : 1;
		uint8_t ocf3b : 1;
		uint8_t ocf3c : 1;
		uint8_t       : 1;
		uint8_t icf3 : 1;
		uint8_t      : 2;
	} par;
	uint8_t var;
} TIFR3_type;
// 0x39 - TIFR4 (Timer/Counter4 Interrupt Flag Register)
typedef union {
	struct {
		uint8_t      : 2;
		uint8_t tov4 : 1;
		uint8_t      : 2;
		uint8_t ocf4b : 1;
		uint8_t ocf4a : 1;
		uint8_t ocf4d : 1;
	} par;
	uint8_t var;
} TIFR4_type;
// 0x3A - Reserved
// 0x3B - PCIFR (Pin Change Interrupt Flag Register)
typedef union {
	struct {
		uint8_t pcif0 : 1;
		uint8_t       : 7;
	} par;
	uint8_t var;
} PCIFR_type;
// 0x3C - EIFR (External Interrupt Flag Register)
typedef union {
	struct {
		uint8_t intf0 : 1;
		uint8_t intf1 : 1;
		uint8_t intf2 : 1;
		uint8_t intf3 : 1;
		uint8_t       : 2;
		uint8_t intf6 : 1;
		uint8_t       : 1;
	} par;
	uint8_t var;
} EIFR_type;
// 0x3D - EIMSK (External Interrupt Mask Register)
typedef union {
	struct {
		uint8_t int0 : 1;
		uint8_t int1 : 1;
		uint8_t int2 : 1;
		uint8_t int3 : 1;
		uint8_t      : 2;
		uint8_t int6 : 1;
		uint8_t      : 1;
	} par;
	uint8_t var;
} EIMSK_type;
// 0x3E - GPIOR0 (General Purpose IO Register 0) (U_byte)
typedef U_byte GPIOR0_type;
// 0x3F - EECR (EEPROM Control Register)
typedef union {
	struct {
		uint8_t eere : 1;
		uint8_t eepe : 1;
		uint8_t eempe : 1;
		uint8_t eerie : 1;
		uint8_t eepm0 : 1;
		uint8_t eepm1 : 1;
		uint8_t       : 2;
	} par;
	uint8_t var;
} EECR_type;
// 0x40 - EEDR (EEPROM Data Register) (U_byte)
typedef U_byte EEDR_type;



// 0x41 - EEARL (EEPROM Address Register Low) (U_byte)
typedef U_byte EEARL_type;
// 0x42 - EEARH (EEPROM Address Register High) (U_byte)
typedef union {
	struct {
		uint8_t eearh : 4;
		uint8_t       : 4;
	} par;
	uint8_t var;
} EEARH_type;
// EEAR (EEPROM Address Register)
typedef union {
	struct {
		EEARL_type l;
		EEARH_type h;
	} par;
	uint16_t var;
} EEAR_type;



// 0x43 - GTCCR (General Timer/Counter Control Register)
typedef union {
	struct {
		uint8_t psrsync : 1;
		uint8_t psrasy : 1;
		uint8_t     : 5;
		uint8_t tsm : 1;
	} par;
	uint8_t var;
} GTCCR_type;
// 0x44 - TCCR0A (Timer/Counter0 Control Register A)
typedef union {
    struct {
        uint8_t wgm00 : 1;
        uint8_t wgm01 : 1;
		uint8_t       : 2;
        uint8_t com0b0 : 1;
        uint8_t com0b1 : 1;
        uint8_t com0a0 : 1;
        uint8_t com0a1 : 1;
    } par;
    uint8_t var;
} TCCR0A_type;
// 0x45 - TCCR0B (Timer/Counter0 Control Register B)
typedef union {
    struct {
        uint8_t cs0 : 3;
        uint8_t wgm02 : 1;
		uint8_t       : 2;
        uint8_t foc0b : 1;
        uint8_t foc0a : 1;
    } par;
    uint8_t var;
} TCCR0B_type;
// 0x46 - TCNT0 (Timer/Counter0) (U_byte)
typedef U_byte TCNT0_type;
// 0x47 - OCR0A (Output Compare Register 0 A) (U_byte)
typedef U_byte OCR0A_type;
// 0x48 - OCR0B (Output Compare Register 0 B) (U_byte)
typedef U_byte OCR0B_type;
// 0x49 - PLLCSR (PLL Control and Status Register)
typedef union {
	struct {
		uint8_t plock : 1;
		uint8_t plle  : 1;
		uint8_t       : 2;
		uint8_t pindiv : 1;
		uint8_t        : 3;
	} par;
	uint8_t var;
} PLLCSR_type;
// 0x4A - GPIOR1 (General Purpose I/O Register 1) (U_byte)
typedef U_byte GPIOR1_type;
// 0x4B - GPIOR2 (General Purpose I/O Register 2) (U_byte)
typedef U_byte GPIOR2_type;
// 0x4C - SPCR (SPI Control Register)
typedef union {
	struct {
		uint8_t spr0 : 1;
		uint8_t spr1 : 1;
		uint8_t cpha : 1;
		uint8_t cpol : 1;
		uint8_t mstr : 1;
		uint8_t dord : 1;
		uint8_t spe : 1;
		uint8_t spie : 1;
	} par;
	uint8_t var;
} SPCR_type;
// 0x4D - SPSR (SPI Status Register)
typedef union {
	struct {
		uint8_t spi2x : 1;
		uint8_t       : 5;
		uint8_t wcol : 1;
		uint8_t spif : 1;
	} par;
	uint8_t var;
} SPSR_type;
// 0x4E - SPDR (SPI Data Register) (U_byte)
typedef U_byte SPDR_type;
// 0x4F - Reserved
// 0x50 - ACSR (Analog Comparator Control and Status Register)
typedef union {
	struct {
		uint8_t acis0 : 1;
		uint8_t acis1 : 1;
		uint8_t acic : 1;
		uint8_t acie : 1;
		uint8_t aci : 1;
		uint8_t aco : 1;
		uint8_t acbg : 1;
		uint8_t acd : 1;
	} par;
	uint8_t var;
} ACSR_type;
// 0x51 - OCDR (On-chip Debug Register) (U_byte)
typedef union {
	struct {
		uint8_t ocdr0 : 1;
		uint8_t ocdr1 : 1;
		uint8_t ocdr2 : 1;
		uint8_t ocdr3 : 1;
		uint8_t ocdr4 : 1;
		uint8_t ocdr5 : 1;
		uint8_t ocdr6 : 1;
		uint8_t ocdr7 : 1;
	} par;
	uint8_t var;
} OCDR_type;
// 0x52 - PLLFRQ (PLL Frequency Control Register)
typedef union {
	struct {
		uint8_t pdiv0 : 4;
		uint8_t plltm : 2;
		uint8_t pllusb : 1;
		uint8_t pinmux : 1;
	} par;
	uint8_t var;
} PLLFRQ_type;
// 0x53 - SMCR (Sleep Mode Control Register)
typedef union {
	struct {
		uint8_t se : 1;
		uint8_t sm : 3;
		uint8_t    : 4;
	} par;
	uint8_t var;
} SMCR_type;
// 0x54 - MCUSR (MCU Status Register)
typedef union {
	struct {
		uint8_t porf : 1;
		uint8_t extrf : 1;
		uint8_t borf : 1;
		uint8_t wdrf : 1;
		uint8_t jtrf : 1;
		uint8_t usbrf : 1;
		uint8_t       : 2;
	} par;
	uint8_t var;
} MCUSR_type;
// 0x55 - MCUCR (MCU Control Register)
typedef union {
	struct {
		uint8_t ivce : 1;
		uint8_t ivsel : 1;
		uint8_t : 2;
		uint8_t pud : 1;
		uint8_t : 2;
		uint8_t jtd : 1;
	} par;
	uint8_t var;
} MCUCR_type;
// 0x56 - Reserved
// 0x57 - SPMCSR
typedef union {
	struct {
		uint8_t spmen : 1;
		uint8_t pgers : 1;
		uint8_t pgwrt : 1;
		uint8_t blbset : 1;
		uint8_t rwwsre : 1;
		uint8_t sigrd : 1;
		uint8_t rwwsb : 1;
		uint8_t spmie : 1;
	} par;
	uint8_t var;
} SPMCSR_type;
// 0x58 - Reserved
// 0x59 - Reserved
// 0x5A - Reserved
// 0x5B - RAMPZ
typedef union {
	struct {
		uint8_t rampz0 : 1;
		uint8_t rampz1 : 1;
		uint8_t        : 6;
	} par;
	uint8_t var;
} RAMPZ_type;
// 0x5C - Reserved



// 0x5D - SPL (Stack Pointer Low Byte) (U_byte)
typedef U_byte SPL_type;
// 0x5E - SPH (Stack Pointer High Byte) (U_byte)
typedef U_byte SPH_type;
// SP (Stack Pointer)
typedef U_word SP_type;



// 0x5F - SREG (Status Register)
typedef union {
	struct {
		uint8_t c : 1;
		uint8_t z : 1;
		uint8_t n : 1;
		uint8_t v : 1;
		uint8_t s : 1;
		uint8_t h : 1;
		uint8_t t : 1;
		uint8_t i : 1;
	} par;
	uint8_t var;
} SREG_type;
// 0x60 - WDTCSR
typedef union {
	struct {
		uint8_t wdp0 : 1;
		uint8_t wdp1 : 1;
		uint8_t wdp2 : 1;
		uint8_t wde : 1;
		uint8_t wdce : 1;
		uint8_t wdp3 : 1;
		uint8_t wdie : 1;
		uint8_t wdif : 1;
	} par;
	uint8_t var;
} WDTCSR_type;
// 0x61 - CLKPR
typedef union {
	struct {
		uint8_t clkps : 4;
		uint8_t       : 3;
		uint8_t clkpce : 1;
	} par;
	uint8_t var;
} CLKPR_type;
// 0x62 - Reserved
// 0x63 - Reserved
// 0x64 - PRR0
typedef union {
	struct {
		uint8_t pradc : 1;
		uint8_t       : 1;
		uint8_t prspi : 1;
		uint8_t prtim1 : 1;
		uint8_t        : 1;
		uint8_t prtim0 : 1;
		uint8_t        : 1;
		uint8_t prtwi : 1;
	} par;
	uint8_t var;
} PRR0_type;
// 0x65 - PRR1
typedef union {
	struct {
		uint8_t prusart1 : 1;
		uint8_t          : 2;
		uint8_t prtim3 : 1;
		uint8_t prtim4 : 1;
		uint8_t        : 2;
		uint8_t prusb : 1;
	} par;
	uint8_t var;
} PRR1_type;
// 0x66 - OSCAL (U_byte)
typedef U_byte OSCAL_type;
// 0x67 - RCCTRL
typedef union {
	struct {
		uint8_t rcfreq : 1;
		uint8_t        : 7;
	} par;
	uint8_t var;
} RCCTRL_type;
// 0x68 - PCICR
typedef union {
	struct {
		uint8_t pcie0 : 1;
		uint8_t       : 7;
	} par;
	uint8_t var;
} PCICR_type;
// 0x69 - EICRA
typedef union {
	struct {
		uint8_t isc0 : 2;
		uint8_t isc1 : 2;
		uint8_t isc2 : 2;
		uint8_t isc3 : 2;
	} par;
	uint8_t var;
} EICRA_type;
// 0x6A - EICRB
typedef union {
	struct {
		uint8_t      : 4;
		uint8_t isc6 : 2;
		uint8_t      : 2;
	} par;
	uint8_t var;
} EICRB_type;
// 0x6B - PCMSK0
typedef union {
	struct {
		uint8_t pcint0 : 1;
		uint8_t pcint1 : 1;
		uint8_t pcint2 : 1;
		uint8_t pcint3 : 1;
		uint8_t pcint4 : 1;
		uint8_t pcint5 : 1;
		uint8_t pcint6 : 1;
		uint8_t pcint7 : 1;
	} par;
	uint8_t var;
} PCMSK0_type;
// 0x6C - Reserved
// 0x6D - Reserved
// 0x6E - TIMSK0 (Timer/Counter0 Interrupt Mask Register)
typedef union {
	struct {
		uint8_t toie0 : 1;
		uint8_t ocie0a : 1;
		uint8_t ocie0b : 1;
		uint8_t        : 5;
	} par;
	uint8_t var;
} TIMSK0_type;
// 0x6F - TIMSK1 (Timer/Counter1 Interrupt Mask Register)
typedef union {
	struct {
		uint8_t toie1 : 1;
		uint8_t ocie1a : 1;
		uint8_t ocie1b : 1;
		uint8_t ocie1c : 1;
		uint8_t        : 1;
		uint8_t icie1 : 1;
		uint8_t       : 2;
	} par;
	uint8_t var;
} TIMSK1_type;
// 0x70 - Reserved
// 0x71 - TIMSK3 (Timer/Counter3 Interrupt Mask Register)
typedef union {
	struct {
		uint8_t toie3 : 1;
		uint8_t ocie3a : 1;
		uint8_t ocie3b : 1;
		uint8_t ocie3c : 1;
		uint8_t        : 1;
		uint8_t icie3 : 1;
		uint8_t       : 2;
	} par;
	uint8_t var;
} TIMSK3_type;
// 0x72 - TIMSK4 (Timer/Counter4 Interrupt Mask Register)
typedef union {
	struct {
		uint8_t       : 2;
		uint8_t toie4 : 1;
		uint8_t       : 2;
		uint8_t ocie4b : 1;
		uint8_t ocie4a : 1;
		uint8_t ocie4d : 1;
	} par;
	uint8_t var;
} TIMSK4_type;
// 0x73 - Reserved
// 0x74 - Reserved
// 0x75 - Reserved
// 0x76 - Reserved
// 0x77 - Reserved



// 0x78 - ADCL (ADC Data Register Low byte) (U_byte)
typedef U_byte ADCL_type;
// 0x79 - ADCH (ADC Data Register High byte) (U_byte)
typedef U_byte ADCH_type;
// ADC (ADC Data Register)
typedef U_word ADC_type;



// 0x7A - ADCSRA (ADC Control and Status Register A)
typedef union {
	struct {
		uint8_t adps : 3;
		uint8_t adie : 1;
		uint8_t adif : 1;
		uint8_t adate : 1;
		uint8_t adsc : 1;
		uint8_t aden : 1;
	} par;
	uint8_t var;
} ADCSRA_type;
// 0x7B - ADCSRB (ADC Control and Status Register B)
typedef union {
	struct {
		uint8_t adts : 4;
		uint8_t      : 1;
		uint8_t mux5 : 1;
		uint8_t acme : 1;
		uint8_t adhsm : 1;
	} par;
	uint8_t var;
} ADCSRB_type;
// 0x7C - ADMUX (ADC Multiplexer Selection Register)
typedef union {
	struct {
		uint8_t mux0_4 : 5;
		uint8_t adlar : 1;
		uint8_t refs : 2;
	} par;
	uint8_t var;
} ADMUX_type;
// 0x7D - DIDR2 (Digital Input Disable Register 2)
typedef union {
	struct {
		uint8_t adc8d : 1;
		uint8_t adc9d : 1;
		uint8_t adc10d : 1;
		uint8_t adc11d : 1;
		uint8_t adc12d : 1;
		uint8_t adc13d : 1;
		uint8_t        : 2;
	} par;
	uint8_t var;
} DIDR2_type;
// 0x7E - DIDR0 (Digital Input Disable Register 0)
typedef union {
	struct {
		uint8_t adc0d : 1;
		uint8_t adc1d : 1;
		uint8_t       : 2;
		uint8_t adc4d : 1;
		uint8_t adc5d : 1;
		uint8_t adc6d : 1;
		uint8_t adc7d : 1;
	} par;
	uint8_t var;
} DIDR0_type;
// 0x7F - DIDR1 (Digital Input Disable Register 1)
typedef union {
	struct {
		uint8_t ain0d : 1;
		uint8_t       : 7;
	} par;
	uint8_t var;
} DIDR1_type;
// 0x80 - TCCR1A (Timer/Counter1 Control Register A)
typedef union {
	struct {
		uint8_t wgm10 : 1;
		uint8_t wgm11 : 1;
		uint8_t com1c0 : 1;
		uint8_t com1c1 : 1;
		uint8_t com1b0 : 1;
		uint8_t com1b1 : 1;
		uint8_t com1a0 : 1;
		uint8_t com1a1 : 1;
	} par;
	uint8_t var;
} TCCR1A_type;
// 0x81 - TCCR1B (Timer/Counter1 Control Register B)
typedef union {
	struct {
		uint8_t cs1 : 3;
		uint8_t wgm12 : 1;
		uint8_t wgm13 : 1;
		uint8_t       : 1;
		uint8_t ices1 : 1;
		uint8_t icnc1 : 1;
	} par;
	uint8_t var;
} TCCR1B_type;
// 0x82 - TCCR1C (Timer/Counter1 Control Register C)
typedef union {
	struct {
		uint8_t       : 5;
		uint8_t foc1c : 1;
		uint8_t foc1b : 1;
		uint8_t foc1a : 1;
	} par;
	uint8_t var;
} TCCR1C_type;
// 0x83 - Reserved



// 0x84 - TCNT1L (Timer/Counter1 Low byte) (U_byte)
typedef U_byte TCNT1L_type;
// 0x85 - TCNT1H (Timer/Counter1 High byte) (U_byte)
typedef U_byte TCNT1H_type;
// TCNT1 (Timer/Counter1)
typedef U_word TCNT1_type;



// 0x86 - ICR1L (Input Capture Register 1 Low byte) (U_byte)
typedef U_byte ICR1L_type;
// 0x87 - ICR1H (Input Capture Register 1 High byte) (U_byte)
typedef U_byte ICR1H_type;
// ICR1 (Input Capture Register 1)
typedef U_word ICR1_type;



// 0x88 - OCR1AL (Output Compare Register 1 A Low byte) (U_byte)
typedef U_byte OCR1AL_type;
// 0x89 - OCR1AH (Output Compare Register 1 A High byte) (U_byte)
typedef U_byte OCR1AH_type;
// OCR1A (Output Compare Register 1 A)
typedef U_word OCR1A_type;



// 0x8A - OCR1BL (Output Compare Register 1 B Low byte) (U_byte)
typedef U_byte OCR1BL_type;
// 0x8B - OCR1BH (Output Compare Register 1 B High byte) (U_byte)
typedef U_byte OCR1BH_type;
// OCR1B (Output Compare Register 1 B)
typedef U_word OCR1B_type;



// 0x8C - OCR1CL (Output Compare Register 1 C Low byte) (U_byte)
typedef U_byte OCR1CL_type;
// 0x8D - OCR1CH (Output Compare Register 1 C High byte) (U_byte)
typedef U_byte OCR1CH_type;
// OCR1C (Output Compare Register 1 C)
typedef U_word OCR1C_type;



// 0x8E - Reserved
// 0x8F - Reserved
// 0x90 - TCCR3A (Timer/Counter3 Control Register A)
typedef union {
	struct {
		uint8_t wgm30 : 1;
		uint8_t wgm31 : 1;
		uint8_t com3c0 : 1;
		uint8_t com3c1 : 1;
		uint8_t com3b0 : 1;
		uint8_t com3b1 : 1;
		uint8_t com3a0 : 1;
		uint8_t com3a1 : 1;
	} par;
	uint8_t var;
} TCCR3A_type;
// 0x91 - TCCR3B (Timer/Counter3 Control Register B)
typedef union {
	struct {
		uint8_t cs3 : 3;
		uint8_t wgm32 : 1;
		uint8_t wgm33 : 1;
		uint8_t       : 1;
		uint8_t ices3 : 1;
		uint8_t icnc3 : 1;
	} par;
	uint8_t var;
} TCCR3B_type;
// 0x92 - TCCR3C (Timer/Counter3 Control Register C)
typedef union {
	struct {
		uint8_t foc3a : 1;
		uint8_t       : 7;
	} par;
	uint8_t var;
} TCCR3C_type;
// 0x93 - Reserved



// 0x94 - TCNT3L (Timer/Counter3 Low byte) (U_byte)
typedef U_byte TCNT3L_type;
// 0x95 - TCNT3H (Timer/Counter3 High byte) (U_byte)
typedef U_byte TCNT3H_type;
// TCNT3H (Timer/Counter3)
typedef U_word TCNT3_type;



// 0x96 - ICR3L (Input Capture Register 3 Low byte) (U_byte)
typedef U_byte ICR3L_type;
// 0x97 - ICR3H (Input Capture Register 3 High byte) (U_byte)
typedef U_byte ICR3H_type;
// ICR3 (Input Capture Register 3)
typedef U_word ICR3_type;



// 0x98 - OCR3AL (Output Compare Register 3 A Low byte) (U_byte)
typedef U_byte OCR3AL_type;
// 0x99 - OCR3AH (Output Compare Register 3 A High byte) (U_byte)
typedef U_byte OCR3AH_type;
// OCR3A (Output Compare Register 3 A)
typedef U_word OCR3A_type;



// 0x9A - OCR3BL (Output Compare Register 3 B Low byte) (U_byte)
typedef U_byte OCR3BL_type;
// 0x9B - OCR3BH (Output Compare Register 3 B High byte) (U_byte)
typedef U_byte OCR3BH_type;
// OCR3B (Output Compare Register 3 B)
typedef U_word OCR3B_type;



// 0x9C - OCR3CL (Output Compare Register 3 C Low byte) (U_byte)
typedef U_byte OCR3CL_type;
// 0x9D - OCR3CH (Output Compare Register 3 C High byte) (U_byte)
typedef U_byte OCR3CH_type;
// OCR3C (Output Compare Register 3 C)
typedef U_word OCR3C_type;



// 0x9E - Reserved
// 0x9F - Reserved
// 0xA0 - Reserved
// 0xA1 - Reserved
// 0xA2 - Reserved
// 0xA3 - Reserved
// 0xA4 - Reserved
// 0xA5 - Reserved
// 0xA6 - Reserved
// 0xA7 - Reserved
// 0xA8 - Reserved
// 0xA9 - Reserved
// 0xAA - Reserved
// 0xAB - Reserved
// 0xAC - Reserved
// 0xAD - Reserved
// 0xAE - Reserved
// 0xAF - Reserved
// 0xB0 - Reserved
// 0xB1 - Reserved
// 0xB2 - Reserved
// 0xB3 - Reserved
// 0xB4 - Reserved
// 0xB5 - Reserved
// 0xB6 - Reserved
// 0xB7 - Reserved
// 0xB8 - TWBR (Two-Wire Serial Interface Bit Rate Register) (U_byte)
typedef U_byte TWBR_type;
// 0xB9 - TWSR (Two-Wire Serial Interface Status Register)
typedef union {
	struct {
		uint8_t twps : 2;
		uint8_t      : 1;
		uint8_t tws3 : 1;
		uint8_t tws4 : 1;
		uint8_t tws5 : 1;
		uint8_t tws6 : 1;
		uint8_t tws7 : 1;
	} par;
	uint8_t var;
} TWSR_type;
// 0xBA - TWAR (Two-Wire Serial Interface Address Register)
typedef union {
	struct {
		uint8_t twgce : 1;
		uint8_t twa   : 7;
	} par;
	uint8_t var;
} TWAR_type;
// 0xBB - TWDR (Two-Wire Serial Interface Data Register) (U_byte)
typedef U_byte TWDR_type;
// 0xBC - TWCR (Two-Wire Serial Interface Control Register)
typedef union {
	struct {
		uint8_t twie : 1;
		uint8_t      : 1;
		uint8_t twen : 1;
		uint8_t twwc : 1;
		uint8_t twsto : 1;
		uint8_t twsta : 1;
		uint8_t twea  : 1;
		uint8_t twint : 1;
	} par;
	uint8_t var;
} TWCR_type;
// 0xBD - TWAMR (Two-Wire Serial Interface Address Mask Register)
typedef union {
	struct {
		uint8_t      : 1;
		uint8_t twam : 7;
	} par;
	uint8_t var;
} TWAMR_type;



// 0xBE - TCNT4L (Timer/Counter4) (U_byte)
typedef U_byte TCNT4L_type;
// 0xBF - TCNT4H (Timer/Counter4) (U_byte)
typedef union {
	struct {
		uint8_t tc4h : 3;
		uint8_t      : 5;	
	} par;
	uint8_t var;
} TCNT4H_type;
// TCNT4 (Timer/Counter4)
typedef union {
	struct {
		TCNT4L_type l;
		TCNT4H_type h;
	} par;
	uint16_t var;	
} TCNT4_type; 



// 0xC0 - TCCR4A (Timer/Counter4 Control Register A)
typedef union {
	struct {
		uint8_t pwm4b : 1;
		uint8_t pwm4a : 1;
		uint8_t foc4b : 1;
		uint8_t foc4a : 1;
		uint8_t com4b0 : 1;
		uint8_t com4b1 : 1;
		uint8_t com4c0 : 1;
		uint8_t com4a1 : 1;
	} par;
	uint8_t var;
} TCCR4A_type;
// 0xC1 - TCCR4B (Timer/Counter4 Control Register B)
typedef union {
	struct {
		uint8_t cs4 : 4;
		uint8_t dtps4 : 2;
		uint8_t psr4 : 1;
		uint8_t pwm4x : 1;
	} par;
	uint8_t var;
} TCCR4B_type;
// 0xC2 - TCCR4C (Timer/Counter4 Control Register C)
typedef union {
	struct {
		uint8_t pwm4d : 1;
		uint8_t foc4d : 1;
		uint8_t com4d0s : 1;
		uint8_t com4d1s : 1;
		uint8_t com4b0s : 1;
		uint8_t com4b1s : 1;
		uint8_t com4a0s : 1;
		uint8_t com4a1s : 1;
	} par;
	uint8_t var;
} TCCR4C_type;
// 0xC3 - TCCR4D (Timer/Counter4 Control Register D)
typedef union {
	struct {
		uint8_t wgm4 : 2;
		uint8_t fpf4 : 1;
		uint8_t fpac4 : 1;
		uint8_t fpes4 : 1;
		uint8_t fpnc4 : 1;
		uint8_t fpen4 : 1;
		uint8_t fpie4 : 1;
	} par;
	uint8_t var;
} TCCR4D_type;
// 0xC4 - TCCR4E (Timer/Counter4 Control Register #)
typedef union {
	struct {
		uint8_t oc4oe : 6;
		uint8_t enhc4 : 1;
		uint8_t tlock4 : 1;
	} par;
	uint8_t var;
} TCCR4E_type;
// 0xC5 - CLKSEL0
typedef union {
	struct {
		uint8_t clks : 1;
		uint8_t      : 1;
		uint8_t exte : 1;
		uint8_t rce : 1;
		uint8_t exsut : 2;
		uint8_t rcsut : 2;
	} par;
	uint8_t var;
} CLKSEL0_type;
// 0xC6 - CLKSEL1
typedef union {
	struct {
		uint8_t excksel : 4;
		uint8_t rccksel : 4;
	} par;
	uint8_t var;
} CLKSEL1_type;
// 0xC7 - CLKSTA
typedef union {
	struct {
		uint8_t exton : 1;
		uint8_t rcon : 1;
		uint8_t      : 6;
	} par;
	uint8_t var;
} CLKSTA_type;
// 0xC8 - UCSR1A (USART Control and Status Register A)
typedef union {
    struct {
        uint8_t mpcm1 : 1;
        uint8_t u2x1  : 1;
        uint8_t pe1   : 1;
        uint8_t dor1  : 1;
        uint8_t fe1   : 1;
        uint8_t udre1 : 1;
        uint8_t txc1 : 1;
        uint8_t rxc1 : 1;
    } par;
    uint8_t var;
} UCSR1A_type;
// 0xC9 - UCSR1B (USART Control and Status Register B)
typedef union {
    struct {
        uint8_t txb81 : 1;
        uint8_t rxb81 : 1;
        uint8_t ucsz12 : 1;
        uint8_t txen1 : 1;
        uint8_t rxen1 : 1;
        uint8_t udrie1 : 1;
        uint8_t txcie1 : 1;
        uint8_t rxcie1 : 1;
    } par;
    uint8_t var;
} UCSR1B_type;
// 0xCA - UCSR1C (USART Control and Status Register C)
typedef union {
    struct {
		uint8_t ucpol1 : 1;
		uint8_t ucsz10 : 1;
		uint8_t ucsz11 : 1;
		uint8_t usbs1 : 1;
		uint8_t upm10 : 1;
		uint8_t upm11 : 1;
        uint8_t umsel10 : 1;
        uint8_t umsel11 : 1;
    } par;
    uint8_t var;
} UCSR1C_type;
// 0xCB - UCSR1D (USART Control and Status Register D)
typedef union {
	struct {
		uint8_t rtsen : 1;
		uint8_t ctsen : 1;
		uint8_t       : 6;
	} par;
	uint8_t var;
} UCSR1D_type;



// 0xCC - UBRR1L (USART Baud Rate Register Low) (U_byte)
typedef U_byte UBRR1L_type;
// 0xCD - UBRR1H (USART Baud Rate Register High) (U_byte)
typedef union {
	struct {
		uint8_t brr1h : 4;
		uint8_t       : 4;	
	} par;
	uint8_t var;	
} UBRR1H_type;
// UBRR1 (USART Baud Rate Register)
typedef union {
	struct {
		UBRR1L_type l;
		UBRR1H_type h;
	} par;
	uint16_t var;	
} UBRR1_type;



// 0xCE - UDR1 (USART I/O Data Register) (U_byte)
typedef U_byte UDR1_type;
// 0xCF - OCR4A (Output Compare Register 4 A) (U_byte)
typedef U_byte OCR4A_type;
// 0xD0 - OCR4B (Output Compare Register 4 B) (U_byte)
typedef U_byte OCR4B_type;
// 0xD1 - OCR4C (Output Compare Register 4 C) (U_byte)
typedef U_byte OCR4C_type;
// 0xD2 - OCR4D (Output Compare Register 4 D) (U_byte)
typedef U_byte OCR4D_type;
// 0xD3 - Reserved
// 0xD4 - DT4
typedef union {
	struct {
		uint8_t l : 4;
		uint8_t h : 4;
	} par;
	uint8_t var;
} DT4_type;
// 0xD5 - Reserved
// 0xD6 - Reserved
// 0xD7 - UHWCON
typedef union {
	struct {
		uint8_t uvrege : 1;
		uint8_t        : 7;
	} par;
	uint8_t var;
} UHWCON_type;
// 0xD8 - USBCON
typedef union {
	struct {
		uint8_t vbuste : 1;
		uint8_t        : 3;
		uint8_t otgpade : 1;
		uint8_t frzclk : 1;
		uint8_t        : 1;
		uint8_t usbe : 1;
	} par;
	uint8_t var;
} USBCON_type;
// 0xD9 - USBSTA
typedef union {
	struct {
		uint8_t vbus : 1;
		uint8_t id : 1;
		uint8_t    : 6;
	} par;
	uint8_t var;
} USBSTA_type;
// 0xDA - USBINT
typedef union {
	struct {
		uint8_t vbusti : 1;
		uint8_t        : 7;
	} par;
	uint8_t var;
} USBINT_type;
// 0xDB - Reserved
// 0xDC - Reserved
// 0xDD - Reserved
// 0xDE - Reserved
// 0xDF - Reserved
// 0xE0 - UDCON
typedef union {
	struct {
		uint8_t detach : 1;
		uint8_t rmwkup : 1;
		uint8_t lsm : 1;
		uint8_t rstcpu : 1;
		uint8_t        : 4;
	} par;
	uint8_t var;
} UDCON_type;
// 0xE1 - UDINT
typedef union {
	struct {
		uint8_t suspi : 1;
		uint8_t msofi : 1;
		uint8_t sofi : 1;
		uint8_t eorsti : 1;
		uint8_t wakeupi : 1;
		uint8_t eorsmi : 1;
		uint8_t uprsmi : 1;
		uint8_t        : 1;
	} par;
	uint8_t var;
} UDINT_type;
// 0xE2 - UDIEN
typedef union {
	struct {
		uint8_t suspe : 1;
		uint8_t msofe : 1;
		uint8_t sofe : 1;
		uint8_t eorste : 1;
		uint8_t wakeupe : 1;
		uint8_t eorsme : 1;
		uint8_t uprsme : 1;
		uint8_t        : 1;
	} par;
	uint8_t var;
} UDIEN_type;
// 0xE3 - UDADDR
typedef union {
	struct {
		uint8_t uadd : 7;
		uint8_t adden : 1;
	} par;
	uint8_t var;
} UDADDR_type;



// 0xE4 - UDFNUML (U_byte)
typedef U_byte UDFNUML_type;
// 0xE5 - UDFNUMH
typedef union {
	struct {
		uint8_t fnum : 3;
		uint8_t      : 5;
	} par;
	uint8_t var;
} UDFNUMH_type;
// UDFNUM
typedef union {
	struct {
		UDFNUML_type l;
		UDFNUMH_type h;
	} par;
	uint16_t var;	
} UDFNUM_type;



// 0xE6 - UDMFN
typedef union {
	struct {
		uint8_t        : 4;
		uint8_t fncerr : 1;
		uint8_t        : 3;
	} par;
	uint8_t var;
} UDMFN_type;
// 0xE7 - Reserved
// 0xE8 - UEINTX
typedef union {
	struct {
		uint8_t txini : 1;
		uint8_t stalledi : 1;
		uint8_t rxouti : 1;
		uint8_t rxstpi : 1;
		uint8_t nakouti : 1;
		uint8_t rwal : 1;
		uint8_t nakini : 1;
		uint8_t fifocon : 1;
	} par;
	uint8_t var;
} UEINTX_type;
// 0xE9 - UENUM
typedef union {
	struct {
		uint8_t epnum : 3;
		uint8_t       : 5;
	} par;
	uint8_t var;
} UENUM_type;
// 0xEA - UERST
typedef union {
	struct {
		uint8_t eprst : 7;
		uint8_t       : 1;
	} par;
	uint8_t var;
} UERST_type;
// 0xEB - UECONX
typedef union {
	struct {
		uint8_t epen : 1;
		uint8_t      : 2;
		uint8_t rstdt : 1;
		uint8_t stallrqc : 1;
		uint8_t stallrq : 1;
		uint8_t         : 2;
	} par;
	uint8_t var;
} UECONX_type;
// 0xEC - UECFG0X
typedef union {
	struct {
		uint8_t epdir : 1;
		uint8_t       : 5;
		uint8_t eptype : 2;
	} par;
	uint8_t var;
} UECFG0X_type;
// 0xED - UECFG1X
typedef union {
	struct {
		uint8_t       : 1;
		uint8_t alloc : 1;
		uint8_t epbk : 2;
		uint8_t epsize : 4;
	} par;
	uint8_t var;
} UECFG1X_type;
// 0xEE - UESTA0X
typedef union {
	struct {
		uint8_t nbusybk : 2;
		uint8_t dtseq : 2;
		uint8_t       : 1;
		uint8_t underfi : 1;
		uint8_t overfi : 1;
		uint8_t cfgok : 1;
	} par;
	uint8_t var;
} UESTA0X_type;
// 0xEF - UESTA1X
typedef union {
	struct {
		uint8_t currbk : 2;
		uint8_t ctrldir : 1;
		uint8_t reserved : 5;
	} par;
	uint8_t var;
} UESTA1X_type;
// 0xF0 - UEIENX
typedef union {
	struct {
		uint8_t txine : 1;
		uint8_t stallede : 1;
		uint8_t rxoute : 1;
		uint8_t rxstpe : 1;
		uint8_t nakoute : 1;
		uint8_t         : 1;
		uint8_t nakine : 1;
		uint8_t flerre : 1;
	} par;
	uint8_t var;
} UEIENX_type;
// 0xF1 - UEDATX (U_byte)
typedef U_byte UEDATX_type;



// 0xF2 - UEBCLX (U_byte)
typedef U_byte UEBCLX_type;
// 0xF3 - UEBCHX
typedef union {
	struct {
		uint8_t byct : 3;
		uint8_t      : 5;
	} par;
	uint8_t var;
} UEBCHX_type;
// UEBC_X
typedef union {
	struct {
		UEBCLX_type l;
		UEBCHX_type h;
	} par;
	uint16_t var;	
} UEBC_X_type;



// 0xF4 - UEINT
typedef union {
	struct {
		uint8_t epint : 7;
		uint8_t       : 1;
	} par;
	uint8_t var;
} UEINT_type;
// 0xF5 - Reserved
// 0xF6 - Reserved
// 0xF7 - Reserved
// 0xF8 - Reserved
// 0xF9 - Reserved
// 0xFA - Reserved
// 0xFB - Reserved
// 0xFC - Reserved
// 0xFD - Reserved
// 0xFE - Reserved
// 0xFF - Reserved

#endif
/*** EOF ***/

