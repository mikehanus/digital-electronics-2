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


time_t last_measurement_time;

servo_t water_servo;
dataset_t actual_data;
watering_t watering;
storage_t storage;

int main(void)
{
	sei();
	uart_init(UART_BAUD_SELECT(9600, F_CPU));

	servo_init(&water_servo, &PORTB, 0);
	servo_set_value(&water_servo, 45);

	storage_init(&storage);
	watering_init(&watering, &water_servo);
	sensors_init();
	display_init();

	TIM1_OVF_1SEC();
	TIM1_OVF_ENABLE();

	set_zone(+1*ONE_HOUR);
	actual_data.time = 1701344319 - AVRTIME_TO_UNIXTIME;
	GPIO_mode_output(&DDRB, 0);

	uart_puts("Watering system terminal (pres ? for help):");

	for(uint8_t i = 0; i < 20; i++)
	{
		actual_data.time += 10;
		actual_data.temp = 12 + actual_data.time % 15;
		actual_data.hum = actual_data.time % 100;
		actual_data.moist = actual_data.time % 255;
		storage_write(&storage, &actual_data);
	}

	while(1)
	{
		cmd_handler(&actual_data, &watering, &storage);
		_delay_ms(1000);

		// Every 10 s make measurement
		if(last_measurement_time + 10 < actual_data.time)
		{
			last_measurement_time = actual_data.time;

			sensors_update_dataset(&actual_data);
			display_show_data(&actual_data);
			storage_write(&storage, &actual_data);
		}
	}
	return 0;
}

// 50us overflow
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 156;
	servo_50us_interrupt_handler(&water_servo);
}

ISR(TIMER1_OVF_vect)
{
	actual_data.time++;
}

