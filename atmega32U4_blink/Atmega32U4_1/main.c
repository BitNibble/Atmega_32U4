/*************************************************************************
	MAIN
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: ATmega
Date:     03122023
*************************************************************************/
#include "atmega32U4.h"
#include "atmega32U4_timer1.h"

#define CHANNELS 15
static volatile uint16_t ADC_CHANNEL[CHANNELS];

void toggle(void){
	dev()->portc->port.par.bit7 ^= 1;
}

uint8_t adc_is_conversion_complete(void){
	if( dev()->adc->adcsra.par.adsc ) return 0;
	else return 1;
}

uint8_t adc_is_conversion_in_progress(void){
	return dev()->adc->adcsra.par.adsc;
}

uint8_t adc_is_interrupt_flag_set(void){
	return dev()->adc->adcsra.par.adif;
}

void adc_start_single_conversion(void){
	dev()->adc->adcsra.par.adsc = 1;
}

void adc_start_first_conversion(void){
	dev()->adc->adcsra.par.adsc = 1;
}

void adc_enable(void){
	dev()->adc->adcsra.par.aden = 1;
}

void adc_disable(void){
	dev()->adc->adcsra.par.aden = 0;
}

uint16_t adc_read(void){
	uint16_t adc_value = dev()->adc->adc.par.l.var;
	adc_value |= (dev()->adc->adc.par.h.var << 8);
	return adc_value;
}

void adc_set_right_adjust(void){
	dev()->adc->admux.par.adlar = 0;
}

void adc_set_left_adjust(void){
	dev()->adc->admux.par.adlar = 1;
}

uint8_t adc_get_adjust(void){
	return dev()->adc->admux.par.adlar;
}

void adc_set_aref(uint8_t aref){
	switch(aref){
		// AREF, Internal VREF turned off
		case 0: dev()->adc->admux.par.refs = 0; break;
		// AVCC with external capacitor on AREF pin
		case 1: dev()->adc->admux.par.refs = 1; break;
		// Internal 2.56V Voltage Reference with external capacitor on AREF pin
		case 2: dev()->adc->admux.par.refs = 3; break;
		default: dev()->adc->admux.par.refs = 1; break;
	};
}

uint8_t adc_get_aref(void){
	return dev()->adc->admux.par.refs;
}

void adc_auto_trigger_enable(void){
	dev()->adc->adcsra.par.adate = 1;
}

void adc_auto_trigger_disable(void){
	dev()->adc->adcsra.par.adate = 0;
}

uint8_t adc_get_auto_trigger(void){
	return dev()->adc->adcsra.par.adate;
}

void adc_auto_trigger_source(uint8_t trigger){
	switch(trigger){
		// Free Running mode (ADC Interrupt Flag as trigger source)
		case 0: dev()->adc->adcsrb.par.adts = 0; break;
		// Analog Comparator
		case 1: dev()->adc->adcsrb.par.adts = 1; break;
		// External Interrupt Request 0
		case 2: dev()->adc->adcsrb.par.adts = 2; break;
		// Timer/Counter0 Compare Match A
		case 3: dev()->adc->adcsrb.par.adts = 3; break;
		// Timer/Counter0 Overflow
		case 4: dev()->adc->adcsrb.par.adts = 4; break;
		// Timer/Counter1 Compare Match B
		case 5: dev()->adc->adcsrb.par.adts = 5; break;
		// Timer/Counter1 Overflow
		case 6: dev()->adc->adcsrb.par.adts = 6; break;
		// Timer/Counter1 Capture Event
		case 7: dev()->adc->adcsrb.par.adts = 7; break;
		// Timer/Counter4 Overflow
		case 8: dev()->adc->adcsrb.par.adts = 8; break;
		// Timer/Counter4 Compare Match A
		case 9: dev()->adc->adcsrb.par.adts = 9; break;
		// Timer/Counter4 Compare Match B
		case 10: dev()->adc->adcsrb.par.adts = 10; break;
		// Timer/Counter4 Compare Match D
		case 11: dev()->adc->adcsrb.par.adts = 11; break;
		default: break;
	};
}

uint8_t adc_get_auto_trigger_source(void){
	return	dev()->adc->adcsrb.par.adts;
}

void adc_clear_interrupt_flag(void){
	dev()->adc->adcsra.par.adif = 1;
}

void adc_set_high_speed_mode(void){
	dev()->adc->adcsrb.par.adhsm = 1;
}

void adc_clear_high_speed_mode(void){
	dev()->adc->adcsrb.par.adhsm = 0;
}

uint8_t adc_get_high_speed_mode(void){
	return dev()->adc->adcsrb.par.adhsm;
}

void adc_select_single_ended_input(uint8_t channel){
	switch(channel){
		// ADC0
		case 0:
			dev()->adc->admux.par.mux0_4 = 0;
			dev()->adc->adcsrb.par.mux5 = 0;
			break;
		// ADC1
		case 1:
			dev()->adc->admux.par.mux0_4 = 1;
			dev()->adc->adcsrb.par.mux5 = 0;
			break;
		// ADC4
		case 4:
			dev()->adc->admux.par.mux0_4 = 4;
			dev()->adc->adcsrb.par.mux5 = 0;
			break;
		// ADC5
		case 5:
			dev()->adc->admux.par.mux0_4 = 5;
			dev()->adc->adcsrb.par.mux5 = 0;
			break;
		// ADC6
		case 6:
			dev()->adc->admux.par.mux0_4 = 6;
			dev()->adc->adcsrb.par.mux5 = 0;
			break;
		// ADC7
		case 7:
			dev()->adc->admux.par.mux0_4 = 7;
			dev()->adc->adcsrb.par.mux5 = 0;
			break;
		// 1.1V (VBand Gap)
		case 30:
			dev()->adc->admux.par.mux0_4 = 30;
			dev()->adc->adcsrb.par.mux5 = 0;
			break;
		// 0V (GND)
		case 31:
			dev()->adc->admux.par.mux0_4 = 31;
			dev()->adc->adcsrb.par.mux5 = 0;
			break;
		// ADC8
		case 32:
			dev()->adc->admux.par.mux0_4 = 0;
			dev()->adc->adcsrb.par.mux5 = 1;
			break;
		// ADC9
		case 33:
			dev()->adc->admux.par.mux0_4 = 1;
			dev()->adc->adcsrb.par.mux5 = 1;
			break;
		// ADC10
		case 34:
			dev()->adc->admux.par.mux0_4 = 2;
			dev()->adc->adcsrb.par.mux5 = 1;
			break;
		// ADC11
		case 35:
			dev()->adc->admux.par.mux0_4 = 3;
			dev()->adc->adcsrb.par.mux5 = 1;
			break;
		// ADC12
		case 36:
			dev()->adc->admux.par.mux0_4 = 4;
			dev()->adc->adcsrb.par.mux5 = 1;
			break;
		// ADC13
		case 37:
			dev()->adc->admux.par.mux0_4 = 5;
			dev()->adc->adcsrb.par.mux5 = 1;
			break;
		// Temperature Sensor
		case 39:
			dev()->adc->admux.par.mux0_4 = 7;
			dev()->adc->adcsrb.par.mux5 = 1;
			break;
		default: break;
	};
}

void adc_select_prescaler(uint8_t div){
	switch(div){
		// Division Factor 2
		case 2: dev()->adc->adcsra.par.adps = 0; break;
		// Division Factor 4
		case 4: dev()->adc->adcsra.par.adps = 2; break;
		// Division Factor 8
		case 8: dev()->adc->adcsra.par.adps = 3; break;
		// Division Factor 16
		case 16: dev()->adc->adcsra.par.adps = 4; break;
		// Division Factor 32
		case 32: dev()->adc->adcsra.par.adps = 5; break;
		// Division Factor 64
		case 64: dev()->adc->adcsra.par.adps = 6; break;
		// Division Factor 128
		case 128: dev()->adc->adcsra.par.adps = 7; break;
		default: break;
	};
}

uint8_t adc_get_prescaler(void){
	uint8_t div_factor = 0;
	switch(dev()->adc->adcsra.par.adps){
		// Division Factor 2
		case 0: div_factor = 2;
		// Division Factor 2
		case 1: div_factor = 2; break;
		// Division Factor 4
		case 2: div_factor = 4; break;
		// Division Factor 8
		case 3: div_factor = 8; break;
		// Division Factor 16
		case 4: div_factor = 16; break;
		// Division Factor 32
		case 5: div_factor = 32; break;
		// Division Factor 64
		case 6: div_factor = 64; break;
		// Division Factor 128
		case 7: div_factor = 128; break;
		default: break;
	};
	return div_factor;
}

void adc_enable_disable_digital_input(uint16_t hbit_disable){
	dev()->adc->didr0.var = WriteHLByte(hbit_disable).par.l.var;
	dev()->adc->didr2.var = WriteHLByte(hbit_disable).par.h.var;
}

void adc_interrupt_enable(void){
	dev()->adc->adcsra.par.adie = 1;
}

void adc_interrupt_disable(void){
	dev()->adc->adcsra.par.adie = 0;
}

uint16_t adc_get_if_conversion(void){
	static volatile uint16_t adc_value = 0;
	if(adc_is_interrupt_flag_set()){ 
		adc_value = adc_read();
		adc_clear_interrupt_flag();
	}
	return adc_value;
}

uint16_t adc_get_adsc_conversion(void){
	static volatile uint16_t adc_value = 0;
	if(adc_is_conversion_complete()){
		adc_value = adc_read();
		adc_start_single_conversion();
	}
	return adc_value;
}

int main(void) {
	dev()->portc->ddr.par.bit7 = 1;
	dev()->portf->ddr.var = 0;
	dev()->portf->port.var = 255;
	
	adc_set_aref(1);
	adc_select_single_ended_input(0);
	adc_select_prescaler(8);
	adc_auto_trigger_enable();
	adc_auto_trigger_source(0);
	adc_enable();
	adc_start_first_conversion();
	
	tc1()->callback.compa_vect = toggle;
	tc1_enable(4,2);
	tc1()->start(128);

	while (1) {
		
		tc1()->compareA(adc_get_if_conversion());

	}

	return 0;
}

