/*************************************************************************
	MAIN
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: ATmega
Date:     03122023
*************************************************************************/
#include "atmega32U4.h"
#include "atmega32U4_timer1.h"

void toggle(void){
	dev()->portc->port.par.bit7 ^= 1;
}

int main(void) {
	dev()->portc->ddr.par.bit7 = 1;
	
	tc1_enable(0,1);
	tc1()->interrupt(2);
	
	tc1()->compareA(17654);
	
	tc1()->callback.compa_vect = toggle;
	tc1()->callback.ovf_vect = toggle;
	
	tc1()->start(64);

	while (1) {
		
	}

	return 0;
}

