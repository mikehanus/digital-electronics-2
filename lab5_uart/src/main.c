/***********************************************************************
 *
 * Use USART unit and transmit data between ATmega328P and computer.
 *
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2018 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 *
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#undef F_CPU
#ifndef F_CPU
#define F_CPU 16000000 // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

//#define UART_TX_BUFFER_SIZE 256
//#define UART_RX_BUFFER_SIZE 256

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>				// AVR device-specific IO definitions
#include <avr/interrupt.h> // Interrupts standard C library for AVR-GCC
#include "timer.h"				 // Timer library for AVR-GCC
#include <uart.h>					// Peter Fleury's UART library
#include <stdlib.h>				// C library. Needed for number conversions

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:	Use Timer/Counter1 and transmit UART data four times
 *					 per second.
 * Returns:	none
 **********************************************************************/
int main(void)
{
	// Initialize USART to asynchronous, 8N1, 9600
	uart_init(UART_BAUD_SELECT(9600, F_CPU));

	// Configure 16-bit Timer/Counter1 to transmit UART data
	// Set prescaler to 262 ms and enable overflow interrupt

	// Enables interrupts by setting the global interrupt mask
	sei();

	TIM1_OVF_ENABLE();
	TIM1_OVF_262MS();

	// Put strings to ringbuffer for transmitting via UART
	uart_puts("Print one line... ");
	uart_puts("done\r\n");

	// Infinite loop
	while (1)
	{
		/* Empty loop. All subsequent operations are performed exclusively
		 * inside interrupt service routines ISRs */
	}

	// Will never reach this
	return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:	Transmit UART data four times per second.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
	// Transmit UART string(s)
	static char *s="      ", val = 0;
	static uint8_t i = 0;

	if((val = uart_getc()))
	{
		//i = ++i % 10;
		//s[4] = '0' + i;
		uart_putc(val);
		uart_puts("\e[31m");
		uart_puts("  \t0");
		itoa(val, s, 8);
		uart_puts(s);

		uart_puts("  \t");
		uart_puts("\e[33m");
		itoa(val, s, 10);
		uart_puts(s);

		uart_puts("  \t0x");
		uart_puts("\e[34m");
		itoa(val, s, 16);
		uart_puts(s);
		uart_puts("\e[0");
		uart_puts("\n\r");
	}
	//uart_puts(s);
}
