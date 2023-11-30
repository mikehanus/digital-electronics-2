#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "timer.h"

/*typedef struct data_t
{
	uint32_t time;
	uint8_t hum_soil;
	uint8_t hum_air;
	uint8_t temp_air;
	uint8_t water;
};*/

int pos=0;

int main(void)
{
	//GPIO_mode_output(&DDRB, 5);
	DDRB |= (1 << 0); // set PB0 output
	PORTB &= !(1<<0);

	TIM0_OVF_128US();
	TIM0_OVF_ENABLE();

	sei();

	while(1)
	{//16-44
		pos=42;
		_delay_ms(1000);
		pos=43;
		_delay_ms(1000);
	}

	return 0;
}

// 50us overflow
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 156;
	static uint16_t tick = 0;
	if (tick == pos) PORTB &= ~(1 << 0);
	if (tick >= 387)
	{
		PORTB |= (1 << 0);
		tick=0;
	}
	else tick++;
}