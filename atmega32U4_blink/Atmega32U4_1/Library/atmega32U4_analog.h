/************************************************************************
	ANALOG
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega32u4
Date:     03122023
************************************************************************/
#ifndef _ATMEGA32U4_ANALOG_H_
	#define _ATMEGA32U4_ANALOG_H_

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/
#define ADC_NUMBER_SAMPLE 2 // ADC_NUMBER_SAMPLE^2 gives number of samples, note values can only range from 0 to 4.

/*** Global Variable ***/
typedef struct {
	uint8_t VREFF;
	uint8_t DIVISION_FACTOR;
}analogparameter;

struct analog {
	analogparameter par;
	int (*read)(int selection);
};
typedef struct analog ANALOG;

/***Global Header***/
ANALOG ANALOGenable( uint8_t Vreff, uint8_t Divfactor, int n_channel, ... );

#endif

/***EOF***/

