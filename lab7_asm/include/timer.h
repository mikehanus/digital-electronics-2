#ifndef TIMER_H
# define TIMER_H

/***********************************************************************
 * 
 * Timer library for AVR-GCC.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2019 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 *
 **********************************************************************/

/**
 * @file 
 * @defgroup fryza_timer Timer Library <timer.h>
 * @code #include <timer.h> @endcode
 *
 * @brief Timer library for AVR-GCC.
 *
 * The library contains macros for controlling the timer modules.
 *
 * @note Based on Microchip Atmel ATmega328P manual and no source file
 *       is needed for the library.
 * @author Tomas Fryza, Dept. of Radio Electronics, Brno University 
 *         of Technology, Czechia
 * @copyright (c) 2019 Tomas Fryza, This work is licensed under 
 *                the terms of the MIT license
 * @{
 */


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>

#define TCCRXB_MODIFY_CS(reg, val) reg = (reg & 0b111) | val

/* Defines -----------------------------------------------------------*/
/**
 * @name  Definitions for 16-bit Timer/Counter1
 * @note  t_OVF = 1/F_CPU * prescaler * 2^n where n = 16, F_CPU = 16 MHz
 */
/** @brief Stop timer, prescaler 000 --> STOP */
#define TIM0_STOP()       TCCRXB_MODIFY_CS(TCCR0B, 0)
/** @brief Set overflow 16us, prescaler 001 --> 1 */
#define TIM0_OVF_16US()   TCCRXB_MODIFY_CS(TCCR0B, 1)
/** @brief Set overflow ms, prescaler 010 --> 8 */
#define TIM0_OVF_128US()  TCCRXB_MODIFY_CS(TCCR0B, 2)
/** @brief Set overflow 1ms, prescaler 011 --> 64 */
#define TIM0_OVF_1MS()    TCCRXB_MODIFY_CS(TCCR0B, 3)
/** @brief Set overflow 4ms, 1024 prescaler 100 --> 256 */
#define TIM0_OVF_4MS()    TCCRXB_MODIFY_CS(TCCR0B, 3)
/** @brief Set overflow 16ms, prescaler // 101 --> 1024 */
#define TIM0_OVF_16MS()   TCCRXB_MODIFY_CS(TCCR0B, 5)


/** @brief Stop timer, prescaler 000 --> STOP */
#define TIM1_STOP()      TCCRXB_MODIFY_CS(TCCR1B, 0)
/** @brief Set overflow 4ms, prescaler 001 --> 1 */
#define TIM1_OVF_4MS()   TCCRXB_MODIFY_CS(TCCR1B, 1)
/** @brief Set overflow 33ms, prescaler 010 --> 8 */
#define TIM1_OVF_33MS()  TCCRXB_MODIFY_CS(TCCR1B, 2)
/** @brief Set overflow 262ms, prescaler 011 --> 64 */
#define TIM1_OVF_262MS() TCCRXB_MODIFY_CS(TCCR1B, 3)
/** @brief Set overflow 1s, prescaler 100 --> 256 */
#define TIM1_OVF_1SEC()  TCCRXB_MODIFY_CS(TCCR1B, 4)
/** @brief Set overflow 4s, prescaler // 101 --> 1024 */
#define TIM1_OVF_4SEC()  TCCRXB_MODIFY_CS(TCCR1B, 5)


/** @brief Stop timer, prescaler 000 --> STOP */
#define TIM2_STOP()       TCCRXB_MODIFY_CS(TCCR2B, 0)
/** @brief Set overflow 16us, prescaler 001 --> 1 */
#define TIM2_OVF_16US()   TCCRXB_MODIFY_CS(TCCR2B, 1)
/** @brief Set overflow 128us, prescaler 010 --> 8 */
#define TIM2_OVF_128US()  TCCRXB_MODIFY_CS(TCCR2B, 2)
/** @brief Set overflow 512, prescaler 011 --> 32 */
#define TIM2_OVF_512US()  TCCRXB_MODIFY_CS(TCCR2B, 3)
/** @brief Set overflow 1ms, 1024 prescaler 100 --> 64 */
#define TIM2_OVF_1MS()    TCCRXB_MODIFY_CS(TCCR2B, 4)
/** @brief Set overflow 2ms, prescaler // 101 --> 128 */
#define TIM2_OVF_2MS()    TCCRXB_MODIFY_CS(TCCR2B, 5)
/** @brief Set overflow 4ms, prescaler // 110 --> 256 */
#define TIM2_OVF_4MS()    TCCRXB_MODIFY_CS(TCCR2B, 6)
/** @brief Set overflow 16ms, prescaler // 111 --> 1024 */
#define TIM2_OVF_16MS()   TCCRXB_MODIFY_CS(TCCR2B, 7)


/** @brief Enable overflow interrupt, 1 --> enable */
#define TIM0_OVF_ENABLE()  TIMSK0 |= (1<<TOIE0)
/** @brief Disable overflow interrupt, 0 --> disable */
#define TIM0_OVF_DISABLE() TIMSK0 &= ~(1<<TOIE0)

/** @brief Enable overflow interrupt, 1 --> enable */
#define TIM1_OVF_ENABLE()  TIMSK1 |= (1<<TOIE1)
/** @brief Disable overflow interrupt, 0 --> disable */
#define TIM1_OVF_DISABLE() TIMSK1 &= ~(1<<TOIE1)

/** @brief Enable overflow interrupt, 1 --> enable */
#define TIM2_OVF_ENABLE()  TIMSK2 |= (1<<TOIE2)
/** @brief Disable overflow interrupt, 0 --> disable */
#define TIM2_OVF_DISABLE() TIMSK2 &= ~(1<<TOIE2)


/**
 * @name  Definitions for 8-bit Timer/Counter0
 * @note  t_OVF = 1/F_CPU * prescaler * 2^n where n = 8, F_CPU = 16 MHz
 */
// WRITE YOUR CODE HERE


/**
 * @name  Definitions for 8-bit Timer/Counter2
 * @note  t_OVF = 1/F_CPU * prescaler * 2^n where n = 8, F_CPU = 16 MHz
 */
// WRITE YOUR CODE HERE


/** @} */

#endif
