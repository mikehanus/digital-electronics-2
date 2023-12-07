#include "servo.h"

void servo_init(servo_t *servo, volatile uint8_t *reg, uint8_t pin)
{
    servo->reg = reg;
    servo->pin = pin;

	TIM0_OVF_128US();
	TIM0_OVF_ENABLE();
	sei();

    //GPIO_mode_output(servo->reg, servo->pin);
    GPIO_write_low(servo->reg, servo->pin);
}

void servo_set_value(servo_t *servo, uint8_t value)
{
    servo->value = value;
}

void servo_50us_interrupt_handler(servo_t *servo)
{
	static uint16_t tick = 0;
	if (tick == servo->value/3+14) GPIO_write_low(servo->reg, servo->pin);
	if (tick >= 387)
	{
		PORTB |= (1 << 0);
        GPIO_write_high(servo->reg, servo->pin);
		tick=0;
	}
	else tick++;
}

