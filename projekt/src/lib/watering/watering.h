#ifndef WATERING_H
#define WATERING_H

#include <servo.h>
#include <dataset.h>

/** @struct watering_t
 *  ----
 *
 *  @var watering::servo
 *    ----
 *  @var watering::min
 *    ----
 *  @var watering::max
 *    ----
 */
typedef struct
{
    servo_t *servo;
    uint16_t min;
    uint16_t max;
} watering_t;

/***************************************************
 *  @brief  ---
 *  @param  watering ---
 *  @param  servo ---
 *  @return None
****************************************************/
void watering_init(watering_t *watering, servo_t *servo);

/***************************************************
 *  @brief  ---
 *  @param  watering ---
 *  @param  min ---
 *  @param  max ---
 *  @return None
****************************************************/
void watering_set_limit(watering_t *watering, uint16_t min, uint16_t max);

/***************************************************
 *  @brief  ---
 *  @param  watering ---
 *  @param  data --- Current measurements
 *  @return None
****************************************************/
void watering_handler(watering_t *watering, dataset_t *data);

#endif

