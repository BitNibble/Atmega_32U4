/**********************************************************************
    ATMEGA32U4_TIMER0
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega32U4
Date:     27/10/2025
**********************************************************************/
#ifndef _ATMEGA32U4_TIMER0_H_
#define _ATMEGA32U4_TIMER0_H_

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
    void (*ovf_vect)(void);
} TC0_Callback;

/*** Handler ***/
typedef struct {
    TC0_Callback callback;

    /*** V-Table ***/
    void (*wavegenmode)(uint8_t wavegenmode);
	void (*clear_wavegenmode)(void);
    void (*interrupt)(uint8_t interrupt);
	void (*clear_interrupt)(void);
    void (*compoutmodeA)(uint8_t mode);
    void (*compoutmodeB)(uint8_t mode);
	void (*clear_compoutmode)(void);
    void (*compareA)(uint8_t value);
    void (*compareB)(uint8_t value);
    uint8_t (*start)(uint16_t prescaler);
    uint8_t (*stop)(void);
} TC0_Handler;

void  tc0_enable(uint8_t wavegenmode, uint8_t interrupt);
TC0_Handler* tc0(void);

#endif
/*** EOF ***/

