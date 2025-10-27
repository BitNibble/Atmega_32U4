/*************************************************************************
	Atmega32u4Uart
Author:	Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega32u4 by ETT ET-BASE
Date: 03122023
Comment:
	stable
*************************************************************************/
/*** File Library ***/
#include "atmega32U4.h"
#include "atmega32U4_uart.h"
#include "buffer.h"
#include <util/delay.h>

/*** File Constant & Macro ***/
// test if the size of the circular buffers fits into SRAM
#if ( ( UART_RX_BUFFER_SIZE ) >= ( RAMEND - 0x60 ) )
	#error "size of UART_RX_BUFFER_SIZE + UART_TX_BUFFER_SIZE larger than size of SRAM"
#endif
#define BAUD_RATE_ASYNCHRONOUS_NORMAL_MODE(baudRate, xtalCpu) ((xtalCpu) / ((baudRate) * 16l) -1)
#define BAUD_RATE_ASYNCHRONOUS_DOUBLE_SPEED(baudRate, xtalCpu) (((xtalCpu) / ((baudRate) * 8l) -1) | 0x8000)
#define BAUD_RATE_SYNCHRONOUS_MASTER_MODE(baudRate, xtalCpu) (((xtalCpu) / ((baudRate) * 2l) -1)))
#define UART_FRAME_ERROR      0x0800	/* Framing Error by UART       */
#define UART_OVERRUN_ERROR    0x0400	/* Overrun condition by UART   */
#define UART_BUFFER_OVERFLOW  0x0200	/* receive ring buffer overflow */
#define UART_NO_DATA          0x0100	/* no receive data available   */
#if defined(__AVR_ATmega16U4__) || \
	defined(__AVR_ATmega32U4__)
	 // USART, RX Complete Handler
	 #define UART_RX_COMPLETE		USART_RX_vect
	 // USART, UDR Empty Handler
	 #define UART_UDR_EMPTY			USART_UDRE_vect
	 //USART, TX Complete Handler
	 #define UART_TX_COMPLETE		USART_TX_vect
#else
	#error "Not Atmega 32u4"
#endif

/*** File Variable ***/
//ATMEGA32U4 atmega32u4;
BUFF rxbuff;
UARTvar UART_Rx;
UARTvar UART_RxBuf[UART_RX_BUFFER_SIZE+1];
uint8_t UART_LastRxError;

/*** File Header ***/
UARTvar uart_read(void);
UARTvar uart_getch(void);
UARTvar* uart_gets(void);
void uart_rxflush(void);
void uart_write(UARTvar data);
void uart_putch(UARTvar c);
void uart_puts(UARTvar* s);

/*** Procedure & Function ***/
UART UARTenable(unsigned int baudrate, unsigned int FDbits, unsigned int Stopbits, unsigned int Parity )
{
	uint8_t tSREG;
	tSREG = atmega32u4.cpu.reg->sreg;
	atmega32u4.cpu.reg->sreg &= ~(1 << GLOBAL_INTERRUPT_ENABLE);
	UART uart;
	atmega32u4 = ATMEGA32U4enable();
	rxbuff = BUFFenable(UART_RX_BUFFER_SIZE, UART_RxBuf);
	uart.par.ubrr = baudrate;
	// Vtable
	uart.read = uart_read;
	uart.getch = uart_getch;
	uart.gets = uart_gets;
	uart.rxflush = uart_rxflush;
	uart.write = uart_write;
	uart.putch = uart_putch;
	uart.puts = uart_puts;
	// Set baud rate
	if ( baudrate & 0x8000 )
	{
   		atmega32u4.usart1.reg->ucsr1a = (1 << U2X1);  //Enable 2x speed 
   		baudrate &= ~0x8000;
   	}
	atmega32u4.usart1.reg->ubrr1 = atmega32u4.writehlbyte(baudrate);
	// Enable USART receiver and transmitter and receive complete interrupt
	atmega32u4.usart1.reg->ucsr1b = _BV(RXCIE1) | (1 << RXEN1) | (1 << TXEN1);
	// Set frame format: asynchronous, 8data, no parity, 1stop bit
	#ifdef URSEL0
		atmega32u4.usart1.reg->ucsr1c = (1 << URSEL0) | (3 << UCSZ10);
		uart.par.FDbits = 8;
		uart.par.Stopbits = 1;
		uart.par.Parity = 0;
	#else
		switch(FDbits){
			case 9:
				atmega32u4.usart1.reg->ucsr1b |= (1 << UCSZ12);
				atmega32u4.usart1.reg->ucsr1c |= (3 << UCSZ10);
				uart.par.FDbits = 9;
			break;
			case 8:
				atmega32u4.usart1.reg->ucsr1b &= ~(1 << UCSZ12);
				atmega32u4.usart1.reg->ucsr1c |= (3 << UCSZ10);
				uart.par.FDbits=8;
			break;
			case 7:
				atmega32u4.usart1.reg->ucsr1b &= ~(1 << UCSZ12);
				atmega32u4.usart1.reg->ucsr1c |= (1 << UCSZ11);
				atmega32u4.usart1.reg->ucsr1c &= ~(1 << UCSZ10);
				uart.par.FDbits=7;
			break;
			case 6:	
				atmega32u4.usart1.reg->ucsr1b &= ~(1 << UCSZ12);
				atmega32u4.usart1.reg->ucsr1c &= ~(1 << UCSZ11);
				atmega32u4.usart1.reg->ucsr1c |= (1 << UCSZ10);
				uart.par.FDbits = 6;
			break;
			case 5:	
				atmega32u4.usart1.reg->ucsr1b &= ~(1 << UCSZ12);
				atmega32u4.usart1.reg->ucsr1c &= ~(3 << UCSZ10);
				uart.par.FDbits=5;
			break;
			default:
				atmega32u4.usart1.reg->ucsr1b &= ~(1 << UCSZ12);
				atmega32u4.usart1.reg->ucsr1c |= (3 << UCSZ10);
				uart.par.FDbits = 8;
			break;
		}
		switch(Stopbits){
			case 1:
				atmega32u4.usart1.reg->ucsr1c &= ~(1 << USBS1);
				uart.par.Stopbits = 1;
			break;
			case 2:
				atmega32u4.usart1.reg->ucsr1c |= (1 << USBS1);
				uart.par.Stopbits=2;
			break;	
			default:
				atmega32u4.usart1.reg->ucsr1c &= ~(1 << USBS1);
				uart.par.Stopbits=1;
			break;
		}
		switch(Parity){
			case 0:
				atmega32u4.usart1.reg->ucsr1c &= ~(3 << UPM10);
				uart.par.Parity=0;
			break;
			case 2:
				atmega32u4.usart1.reg->ucsr1c |= (1 << UPM11);
				atmega32u4.usart1.reg->ucsr1c &= ~(1 << UPM10);
				uart.par.Parity=2;
			break;
			case 3:
				atmega32u4.usart1.reg->ucsr1c |= (3 << UPM10);
				uart.par.Parity=3;
			break;
			default:
				atmega32u4.usart1.reg->ucsr1c &= ~(3 << UPM10);
				uart.par.Parity=0;
			break;
		}
	#endif
	atmega32u4.cpu.reg->sreg = tSREG;
	atmega32u4.cpu.reg->sreg |= (1 << GLOBAL_INTERRUPT_ENABLE);
	
#ifdef _USART1_MODULE_
	atmega32u4.usart1.run = uart;
#endif

	return uart;
}

UARTvar uart_read(void)
{
	UARTvar c;
	c = UART_Rx;
	UART_Rx = 0;
	_delay_ms(1);
	return c;
}
UARTvar uart_getch(void)
{
	return uart_read();
}
UARTvar* uart_gets(void)
{
	return rxbuff.raw(&rxbuff.par);
}
void uart_rxflush(void)
{
	rxbuff.flush(&rxbuff.par);
}
void uart_write(UARTvar data)
{
	atmega32u4.usart1.reg->udr1 = data;
	atmega32u4.usart1.reg->ucsr1b |= _BV(UDRIE1);
	_delay_ms(1);
}
void uart_putch(UARTvar c)
{
	uart_write(c);
}
void uart_puts(UARTvar* s)
{
	char tmp;
	while(*s){
		tmp = *(s++);
		uart_putch(tmp);
	}
}

/*** File Interrupt ***/
ISR(UART_RX_COMPLETE)
{ // USART, RX Complete Handler
	unsigned char bit9;
    unsigned char usr;
	
	usr  = atmega32u4.usart1.reg->ucsr1a;
    bit9 = atmega32u4.usart1.reg->ucsr1b;
    bit9 = 0x01 & (bit9 >> 1);
	
    UART_LastRxError = (usr & (_BV(FE1) | _BV(DOR1)));
	
	UART_Rx = atmega32u4.usart1.reg->udr1;
	rxbuff.push(&rxbuff.par, UART_Rx);
}

ISR(UART_UDR_EMPTY)
{ // USART, UDR Empty Handler
	atmega32u4.usart1.reg->ucsr1b &= ~_BV( UDRIE1 );
}

// ISR(USART1_TX_vect){}

/***EOF***/

