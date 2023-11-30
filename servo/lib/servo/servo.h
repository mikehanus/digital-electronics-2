#ifndef SERVO_H
#define SERVO_H

#include <timer.h>
#include <gpio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

typedef struct
{
    volatile uint8_t *reg;
    uint8_t pin;
    uint8_t value;
} servo_t;

void servo_init(servo_t *servo, volatile uint8_t *reg, uint8_t pin);
void servo_set_value(servo_t *servo, uint8_t value);
void servo_tim0_interrupt_handler(servo_t *servo);

#endif