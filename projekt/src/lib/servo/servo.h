#ifndef SERVO_H
#define SERVO_H

#include <timer.h>
#include <gpio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/** @struct servo_t
 *  ----
 *
 *  @var servo::reg
 *    ----
 *  @var servo::pin
 *    ----
 *  @var servo::value
 *    ----
 */
typedef struct
{
    volatile uint8_t *reg;
    uint8_t pin;
    uint8_t value;
} servo_t;


/***************************************************
 *  @brief  Servo inicialization
 *  @param  servo ---
 *  @param  reg ---
 *  @param  pin ---
 *  @return None
****************************************************/
void servo_init(servo_t *servo, volatile uint8_t *reg, uint8_t pin);

/***************************************************
 *  @brief  ---
 *  @param  servo ---
 *  @param  value ---
 *  @return None
****************************************************/
void servo_set_value(servo_t *servo, uint8_t value);

/***************************************************
 *  @brief  ---
 *  @param  servo ---
 *  @return None
****************************************************/
void servo_50us_interrupt_handler(servo_t *servo);

#endif

