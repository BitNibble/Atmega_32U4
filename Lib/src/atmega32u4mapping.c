/********************************************************************
	ATMEGA 32U4 MAPPING
Author: <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega32U4
Date: 26092025
*********************************************************************/
/*** File Library ***/
#include "atmega32u4mapping.h"

/***File Header***/
uint16_t ATMEGA32U4_ReadHLByte(U_word reg);
uint16_t ATMEGA32U4_ReadLHByte(U_word reg);
U_word ATMEGA32U4_WriteHLByte(uint16_t val);
U_word ATMEGA32U4_WriteLHByte(uint16_t val);
uint16_t ATMEGA32U4_SwapByte(uint16_t num);
uint8_t Atmega32U4_ByteMask(uint8_t target, uint8_t mask);
void Atmega32U4_ByteSet(uint8_t* target, uint8_t set);
void Atmega32U4_ByteClear(uint8_t* target, uint8_t clear);
uint8_t Atmega32U4_ByteShiftright(uint8_t target, uint8_t shift);
uint8_t Atmega32U4_ByteShiftleft(uint8_t target, uint8_t shift);
/******/
void Atmega32U4ClockPrescalerSelect(volatile uint8_t prescaler);
void Atmega32U4MoveInterruptsToBoot(void);
void Atmega32U4MoveInterruptsToSram(void);

/***Internal State***/
static ATMEGA32U4 atmega32u4 = {
	// GPWR
	.gpiar = (Atmega32U4_GPIAR*) Atmega32U4_GPIAR_Address,
	// AC
	.ac = (Atmega32U4_AnalogComparator*) Atmega32U4_AnalogComparator_Address,	
	// ADC
	.adc = (Atmega32U4_AnalogToDigitalConverter*) Atmega32U4_AnalogToDigitalConverter_Address,
	#if defined(_ANALOG_MODULE_)
	.adc_enable = ANALOGenable,
	#endif	
	// BOOT_LOAD
	.boot_load = (Atmega32U4_Bootloader*) Atmega32U4_Bootloader_Address,	
	// CPU
	.cpu = (Atmega32U4_CPURegister*) Atmega32U4_CPURegister_Address,
	// EEPROM
	.eeprom = (Atmega32U4_Eeprom*) Atmega32U4_Eeprom_Address,
	#if defined(_EEPROM_MODULE_)
	.eeprom_enable = EEPROMenable,
	#endif	
	// EXINT
	.exint = (Atmega32U4_ExternalInterrupt*) Atmega32U4_ExternalInterrupt_Address,
	#if defined(_INTERRUPT_MODULE_)
	.exint_enable = INTERRUPTenable,
	#endif
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
	.jtag = (Atmega32U4_JtagInterface*) Atmega32U4_JtagInterface_Address,
	// PLL
	.pll = (Atmega32U4_PhaseLockedLoop*) Atmega32U4_PhaseLockedLoop_Address,
	// SPI
	.spi = (Atmega32U4_SerialPeripherialInterface*) Atmega32U4_SerialPeripherialInterface_Address,
	#if defined(_SPI_MODULE_)
	.spi_enable = SPIenable,
	#endif
	// TC4
	.tc4 = (Atmega32U4_TimerCounter4*) Atmega32U4_TimerCounter4_Address,
	#if defined(_TIMER_MODULE_)
	.tc4_enable = TIMER_COUNTER4enable,
	#endif
	// TC1
	.tc1 = (Atmega32U4_TimerCounter1*) Atmega32U4_TimerCounter1_Address,
	#if defined(_TIMER_MODULE_)
	.tc1_enable = TIMER_COUNTER1enable,
	#endif
	// TC3
	.tc3 = (Atmega32U4_TimerCounter3*) Atmega32U4_TimerCounter3_Address,
	#if defined(_TIMER_MODULE_)
	.tc3_enable = TIMER_COUNTER3enable,
	#endif
	// TC0
	.tc0 = (Atmega32U4_TimerCounter0*) Atmega32U4_TimerCounter0_Address,
	#if defined(_TIMER_MODULE_)
	.tc0_enable = TIMER_COUNTER0enable,
	#endif
	// TWI
	.twi = (Atmega32U4_TwoWireSerialInterface*) Atmega32U4_TwoWireSerialInterface_Address,
	#if defined(_TWI_MODULE_)
	.twi_enable = TWIenable,
	#endif
	// USART1
	.usart1 = (Atmega32U4_Usart1*) Atmega32U4_Usart1_Address,
	#if defined(_USART1_MODULE_)
	.usart1_enable = UARTenable,
	#endif
	// USB_DEVICE
	.usb_device = (Atmega32U4_UsbDeviceRegister*) Atmega32U4_UsbDeviceRegister_Address,
	// WDT
	.wdt = (Atmega32U4_WatchdogTimer*) Atmega32U4_WatchdogTimer_Address,
	// General Func
	.readhlbyte = ATMEGA32U4_ReadHLByte,
	.readlhbyte = ATMEGA32U4_ReadLHByte,
	.writehlbyte = ATMEGA32U4_WriteHLByte,
	.writelhbyte = ATMEGA32U4_WriteLHByte,
	.swapbyte = ATMEGA32U4_SwapByte,
	.byte_mask = Atmega32U4_ByteMask,
	.byte_set = Atmega32U4_ByteSet,
	.byte_clear = Atmega32U4_ByteClear,
	.byte_shiftright = Atmega32U4_ByteShiftright,
	.byte_shiftleft = Atmega32U4_ByteShiftleft,
	/******/
	.Clock_Prescaler_Select = Atmega32U4ClockPrescalerSelect,
	.Move_Interrupts_To_Boot = Atmega32U4MoveInterruptsToBoot,
	.Move_Interrupts_To_Sram = Atmega32U4MoveInterruptsToSram
};

ATMEGA32U4 ATMEGA32U4enable(void) { return (ATMEGA32U4) atmega32u4; }

// COMMON
uint16_t ATMEGA32U4_ReadHLByte(U_word reg)
{
	return (reg.par.h.var << 8) | reg.par.l.var;
}

uint16_t ATMEGA32U4_ReadLHByte(U_word reg)
{
	return (reg.par.l.var << 8) | reg.par.h.var;
}

U_word ATMEGA32U4_WriteHLByte(uint16_t val) // AVR normal little endian
{
	U_word reg; reg.par.h.var = (val >> 8); reg.par.l.var = val;
	return reg;
}

U_word ATMEGA32U4_WriteLHByte(uint16_t val)
{
	U_word reg; reg.par.l.var = (val >> 8); reg.par.h.var = val;
	return reg;
}

uint16_t ATMEGA32U4_SwapByte(uint16_t num)
{
	uint16_t tp;
	tp = (num << 8);
	return (num >> 8) | tp;
}

uint8_t Atmega32U4_ByteMask(uint8_t target, uint8_t mask)
{
	return target & mask;
}

void Atmega32U4_ByteSet(uint8_t* target, uint8_t set)
{
	*target |= set;
}

void Atmega32U4_ByteClear(uint8_t* target, uint8_t clear)
{
	*target &= ~clear;
}

uint8_t Atmega32U4_ByteShiftright(uint8_t target, uint8_t shift)
{
	return target >> shift;
}

uint8_t Atmega32U4_ByteShiftleft(uint8_t target, uint8_t shift)
{
	return target << shift;
}

/******/
void Atmega32U4ClockPrescalerSelect(volatile uint8_t prescaler)
{
	volatile uint8_t sreg;
	prescaler &= 0x0F;
	sreg = atmega32u4.cpu->sreg.var;
	atmega32u4.cpu->sreg.var &= ~(1 << 7);
	
	CLKPR = (1 << CLKPCE);
	CLKPR = prescaler;
	
	atmega32u4.cpu->sreg.var = sreg;
}
void Atmega32U4MoveInterruptsToBoot(void)
{
	volatile uint8_t sreg;
	sreg = atmega32u4.cpu->sreg.var;
	atmega32u4.cpu->sreg.var &= ~(1 << 7);
	
	/* Enable change of Interrupt Vectors */
	MCUCR = (1<<IVCE);
	/* Move interrupts to Boot Flash section */
	MCUCR = (1<<IVSEL);
	
	atmega32u4.cpu->sreg.var = sreg;
}
void Atmega32U4MoveInterruptsToSram(void)
{
	volatile uint8_t sreg;
	sreg = atmega32u4.cpu->sreg.var;
	atmega32u4.cpu->sreg.var &= ~(1 << 7);
	
	/* Enable change of Interrupt Vectors */
	MCUCR = (1<<IVCE);
	/* Move interrupts to Boot Flash section */
	MCUCR = (0<<IVSEL);
	
	atmega32u4.cpu->sreg.var = sreg;
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

