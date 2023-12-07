#undef F_CPU
#ifndef F_CPU
#define F_CPU 16000000 // CPU frequency in Hz required for UART_BAUD_SELECT
#endif


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"
#include <time.h>
#include <servo.h>
#include <uart.h>
#include <dataset.h>

servo_t water_servo;

#define AVRTIME_TO_UNIXTIME 946681200
time_t time_now;

int main(void)
{
	sei();
	uart_init(UART_BAUD_SELECT(9600, F_CPU));

	time_t t = 1701343534;
	set_zone(+1*ONE_HOUR);

	char str[100];

	t = 1701344319 - AVRTIME_TO_UNIXTIME;
	while(1)
	{
		//ptr = localtime(&t);
		uart_puts(ctime(&t));

		//strftime(str, 100, "Ted je %d.%m.%Y a %H:%M:%D den je %A", &localtime(t));
		//uart_putc(str);
		uart_puts("\n");
		//_delay_ms(1000);
		t++;
		for(long i=0; i < 0x2ffff0; i++) asm("NOP");
	}


	GPIO_mode_output(&DDRB, 0);
	servo_init(&water_servo, &PORTB, 0);

	while(1)
	{
		//GPIO_write(&PORTB, 5, 0);
		servo_set_value(&water_servo, 0);
		for(long i=0; i < 0x2ffff0; i++) asm("NOP");
		//GPIO_write(&PORTB, 5, 1);
		servo_set_value(&water_servo, 90);
		for(long i=0; i < 0x2ffff0; i++) asm("NOP");
	}

	return 0;
}

// 50us overflow
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 156;
	servo_tim0_interrupt_handler(&water_servo);
}

// 1s overflow
//		time_now++;

