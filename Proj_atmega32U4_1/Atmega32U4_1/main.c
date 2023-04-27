/*
 * main.c
 *
 * Created: 11/29/2022 7:54:12 PM
 *  Author: sergi
 *	License: GNU General Public License
 */ 
/*** Working Frequency ***/
#define F_CPU 16000000UL

/*** Compiler ***/
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

/*
** library
*/
#include <xc.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "explode.h"
#include "keypad.h"

int main(void)
{
    while(1)
    {
        //TODO:: Please write your application code 
    }
}