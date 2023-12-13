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
#include <cmd.h>
#include <moist_sens.h>
#include <sensors.h>
#include <display.h>

servo_t water_servo;

#define AVRTIME_TO_UNIXTIME 946681200
time_t time_now;

dataset_t actual_data;
watering_t watering;
storage_t storage;

int main(void)
{
	sei();
	moist_sens_init();
	uart_init(UART_BAUD_SELECT(9600, F_CPU));

	storage_init(&storage);
	watering_init(&watering, &water_servo);

	sensors_init();

	time_t t = 1701343534;
	set_zone(+1*ONE_HOUR);

	char str[100];

	actual_data.time = 1701344319 - AVRTIME_TO_UNIXTIME;
	GPIO_mode_output(&DDRB, 0);
	servo_init(&water_servo, &PORTB, 0);
	servo_set_value(&water_servo, 45);
	uart_putc('a');

	while(1)
	{
		//ptr = localtime(&t);
		//uart_puts(ctime(&t));

		//strftime(str, 100, "Ted je %d.%m.%Y a %H:%M:%D den je %A", &localtime(t));
		//uart_putc(str);
		//uart_puts("\n");
		cmd_handler(&actual_data, &watering, &storage);
		_delay_ms(1000);
		actual_data.time++;/*
		actual_data.moist = get_moist() / 4;
		actual_data.hum = actual_data.time % 100;
		actual_data.temp = actual_data.time % 127;*/
		//for(long i=0; i < 0x2ffff0; i++) asm("NOP");
		sensors_update_dataset(&actual_data);
		//disp
	}



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
	servo_50us_interrupt_handler(&water_servo);
}

// 1s overflow
//		time_now++;

