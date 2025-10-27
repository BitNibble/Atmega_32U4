/**********************************************************************
    ATMEGA32U4_TIMER4
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega32U4
Date:     27/10/2025
**********************************************************************/
#ifndef _ATMEGA32U4_TIMER4_H_
#define _ATMEGA32U4_TIMER4_H_

/*** Library ***/
#include "atmega32U4.h"

/*** Constant and Macro ***/
#if !defined(__AVR_ATmega32U4__)
	#error "Not ATmega32U4"
#endif

/*** Callback ***/
typedef struct {
    void (*compa_vect)(void);
    void (*compb_vect)(void);
    void (*compc_vect)(void);
    void (*compd_vect)(void);
    void (*ovf_vect)(void);
} TC4_Callback;

/*** Handler ***/
typedef struct {
    TC4_Callback callback;

    /*** V-Table ***/
    void (*wavegenmode)(unsigned char mode);
	void (*clear_wavegenmode)(void);
    void (*interrupt)(unsigned char interrupt);
	void (*clear_interrupt)(void);
    void (*compoutmodeA)(unsigned char mode);
    void (*compoutmodeB)(unsigned char mode);
    void (*compoutmodeD)(unsigned char mode);
	void (*clear_compoutmode)(void);
    void (*compareA)(uint16_t value);
    void (*compareB)(uint16_t value);
    void (*compareD)(uint16_t value);
    uint8_t (*start)(uint16_t prescaler);
    uint8_t (*stop)(void);
} TC4_Handler;

void tc4_enable(uint8_t wavegenmode, uint8_t interrupt);
TC4_Handler* tc4(void);

#endif
/*** EOF ***/

