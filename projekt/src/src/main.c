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

	//display_init();

	GPIO_mode_output(&DDRB, 0);
	servo_init(&water_servo, &PORTB, 0);
	servo_set_value(&water_servo, 0);

	storage_init(&storage);
	watering_init(&watering, &water_servo);
	watering_set_limit(&watering, 0, 255);
	sensors_init();

	TIM1_OVF_1SEC();
	TIM1_OVF_ENABLE();

	//set_zone(+1*ONE_HOUR);
	actual_data.time = 0; //1701344319 - AVRTIME_TO_UNIXTIME;

	uart_puts("Watering system terminal (pres ? for help):");
	
	while(1)
	{
		cmd_handler(&actual_data, &watering, &storage);
		_delay_ms(1000);
		watering_handler(&watering, &actual_data);
		sensors_update_dataset(&actual_data);
		//servo_set_value(&water_servo, actual_data.time%90);

		// Every save and display measurement
		if(last_measurement_time + 10 < actual_data.time)
		{
			last_measurement_time = actual_data.time;
			//display_show_data(&actual_data);
			storage_write(&storage, &actual_data);
		}
	}
	return 0;
}

// 50us overflow
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 158;
	servo_50us_interrupt_handler(&water_servo);
}

ISR(TIMER1_OVF_vect)
{
	actual_data.time++;
}

