#ifndef SERVO_H
#define SERVO_H

#include "timer.h"

void servo_init(volatile uint8_t *reg, uint8_t pin);
void servo_set_value(uint8_t value);

#endif