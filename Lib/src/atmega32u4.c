/********************************************************************
	ATMEGA 32U4 MAPPING
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega32U4
Date:     26092025
*********************************************************************/
/*** File Library ***/
#include "atmega32U4.h"

/*** Internal State ***/
static ATMEGA32U4 atmega32u4_setup = {
	// GPWR
	.gpiar = (Atmega32U4_GPIAR*) Atmega32U4_GPIAR_Address,
	// AC
	.ac = (Atmega32U4_AnalogComparator*) Atmega32U4_AnalogComparator_Address,	
	// ADC
	.adc = (Atmega32U4_AnalogToDigitalConverter*) Atmega32U4_AnalogToDigitalConverter_Address,
	// BOOT_LOAD
	.boot_load = (Atmega32U4_Bootloader*) Atmega32U4_Bootloader_Address,	
	// CPU
	.cpu = (Atmega32U4_CPURegister*) Atmega32U4_CPURegister_Address,
	// EEPROM
	.eeprom = (Atmega32U4_Eeprom*) Atmega32U4_Eeprom_Address,
	// EXINT
	.exint = (Atmega32U4_ExternalInterrupt*) Atmega32U4_ExternalInterrupt_Address,
	// PORTB
	.portb = (Atmega32U4_PORTB*) Atmega32U4_PORTB_Address,
	// PORTC
	.portc = (Atmega32U4_PORTC*) Atmega32U4_PORTC_Address,
	// PORTD
	.portd = (Atmega32U4_PORTD*) Atmega32U4_PORTD_Address,
	// PORTE
	.porte = (Atmega32U4_PORTE*) Atmega32U4_PORTE_Address,
	// PORTF
	.portf = (Atmega32U4_PORTF*) Atmega32U4_PORTF_Address,
	// JTAG
	.jtag = (Atmega32U4_JtagInterface*) Atmega32U4_JtagInterface_Address,
	// PLL
	.pll = (Atmega32U4_PhaseLockedLoop*) Atmega32U4_PhaseLockedLoop_Address,
	// SPI
	.spi = (Atmega32U4_SerialPeripherialInterface*) Atmega32U4_SerialPeripherialInterface_Address,
	// TC4
	.tc4 = (Atmega32U4_TimerCounter4*) Atmega32U4_TimerCounter4_Address,
	// TC1
	.tc1 = (Atmega32U4_TimerCounter1*) Atmega32U4_TimerCounter1_Address,
	// TC3
	.tc3 = (Atmega32U4_TimerCounter3*) Atmega32U4_TimerCounter3_Address,
	// TC0
	.tc0 = (Atmega32U4_TimerCounter0*) Atmega32U4_TimerCounter0_Address,
	// TWI
	.twi = (Atmega32U4_TwoWireSerialInterface*) Atmega32U4_TwoWireSerialInterface_Address,
	// USART1
	.usart1 = (Atmega32U4_Usart1*) Atmega32U4_Usart1_Address,
	// USB_DEVICE
	.usb_device = (Atmega32U4_UsbDeviceRegister*) Atmega32U4_UsbDeviceRegister_Address,
	// WDT
	.wdt = (Atmega32U4_WatchdogTimer*) Atmega32U4_WatchdogTimer_Address,
};

ATMEGA32U4* dev(void) { return (ATMEGA32U4*) &atmega32u4_setup; }

// COMMON
uint16_t ReadHLByte(U_word reg)
{
	return (reg.par.h.var << 8) | reg.par.l.var;
}

uint16_t ReadLHByte(U_word reg)
{
	return (reg.par.l.var << 8) | reg.par.h.var;
}

U_word WriteHLByte(uint16_t val) // AVR normal little endian
{
	U_word reg; reg.par.h.var = (val >> 8); reg.par.l.var = val;
	return reg;
}

U_word WriteLHByte(uint16_t val)
{
	U_word reg; reg.par.l.var = (val >> 8); reg.par.h.var = val;
	return reg;
}

uint16_t SwapByte(uint16_t num)
{
	uint16_t tp;
	tp = (num << 8);
	return (num >> 8) | tp;
}

uint8_t ByteMask(uint8_t target, uint8_t mask)
{
	return target & mask;
}

void ByteSet(uint8_t* target, uint8_t set)
{
	*target |= set;
}

void ByteClear(uint8_t* target, uint8_t clear)
{
	*target &= ~clear;
}

uint8_t ByteShiftright(uint8_t target, uint8_t shift)
{
	return target >> shift;
}

uint8_t ByteShiftleft(uint8_t target, uint8_t shift)
{
	return target << shift;
}

/******/
void ClockPrescalerSelect(volatile uint8_t prescaler)
{
	volatile uint8_t sreg;
	prescaler &= 0x0F;
	sreg = atmega32u4_setup.cpu->sreg.var;
	atmega32u4_setup.cpu->sreg.var &= ~(1 << 7);
	
	atmega32u4_setup.cpu->clkpr.par.clkpce = 1; // (1 << CLKPCE);
	atmega32u4_setup.cpu->clkpr.var = prescaler;
	
	atmega32u4_setup.cpu->sreg.var = sreg;
}
void MoveInterruptsToBoot(void)
{
	volatile uint8_t sreg;
	sreg = atmega32u4_setup.cpu->sreg.var;
	atmega32u4_setup.cpu->sreg.var &= ~(1 << 7);
	
	/* Enable change of Interrupt Vectors */
	atmega32u4_setup.cpu->mcucr.par.ivce = 1;
	/* Move interrupts to Boot Flash section */
	atmega32u4_setup.cpu->mcucr.par.ivsel = 1;
	
	atmega32u4_setup.cpu->sreg.var = sreg;
}
void MoveInterruptsToSram(void)
{
	volatile uint8_t sreg;
	sreg = atmega32u4_setup.cpu->sreg.var;
	atmega32u4_setup.cpu->sreg.var &= ~(1 << 7);
	
	/* Enable change of Interrupt Vectors */
	atmega32u4_setup.cpu->mcucr.par.ivce = 1;
	/* Move interrupts to Boot Flash section */
	atmega32u4_setup.cpu->mcucr.par.ivsel = 0;
	
	atmega32u4_setup.cpu->sreg.var = sreg;
}

/*** File Interrupt ***/
// ISR(RESET_vect){}
// ISR(INT0_vect){}
// ISR(INT1_vect){}
// ISR(PCINT0_vect){}
// ISR(PCINT1_vect){}
// ISR(PCINT2_vect){}
// ISR(WDT_vect){}
// ISR(TIMER2_COMPA_vect){}
// ISR(TIMER2_COMPB_vect){}
// ISR(TIMER2_OVF_vect){}
// ISR(TIMER1_CAPT_vect){}
// ISR(TIMER1_COMPA_vect){}
// ISR(TIMER1_COMPB_vect){}
// ISR(TIMER1_OVF_vect){}
// ISR(TIMER0_COMPA_vect){}
// ISR(TIMER0_COMPB_vect){}
// ISR(TIMER0_OVF_vect){}
// ISR(SPI_STC_vect){}
// ISR(USART_RX_vect){}
// ISR(USART_UDRE_vect){}
// ISR(USART_TX_vect){}
// ISR(ADC_vect){}
// ISR(EE_READY_vect){}
// ISR(ANALOG_INTERRUPT)
// ISR(ANALOG_COMP_vect){}
// ISR(TWI_vect){}
// ISR(SPM_READY_vect){}

/***EOF***/

/******
1º Sequence
2º Scope
3º Pointer and Variable
4º Casting
******/

