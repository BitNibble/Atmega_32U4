/**********************************************************************
    ATMEGA32U4_TIMER1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega32U4
Date:     26/10/2025
**********************************************************************/
#ifndef _ATMEGA32U4_TIMER1_H_
#define _ATMEGA32U4_TIMER1_H_

/*** Library ***/
#include "atmega32U4.h"

/*** Constant and Macro ***/
#if !defined(__AVR_ATmega32U4__)
	#error "Not ATmega32U4"
#endif

/*** Callback ***/
typedef struct {
    void (*capt_vect)(void);
    void (*compa_vect)(void);
    void (*compb_vect)(void);
    void (*compc_vect)(void);
    void (*ovf_vect)(void);
} TC1_Callback;

/*** Handler ***/
typedef struct {
    TC1_Callback callback;

    /*** V-Table ***/
    void (*wavegenmode)(unsigned char wavegenmode);
    void (*interrupt)(unsigned char interrupt);
    void    (*compoutmodeA)(uint8_t mode);
    void    (*compoutmodeB)(uint8_t mode);
    void    (*compoutmodeC)(uint8_t mode);
    void    (*compareA)(uint16_t value);
    void    (*compareB)(uint16_t value);
    void    (*compareC)(uint16_t value);
    uint8_t (*start)(uint16_t prescaler);
    uint8_t (*stop)(void);
} TC1_Handler;

void  tc1_enable(uint8_t wavegenmode, uint8_t interrupt);
TC1_Handler* tc1(void);

#endif
/*** EOF ***/

