#ifndef WATERING_H
#define WATERING_H

#include <servo.h>
#include <dataset.h>

typedef struct
{
    servo_t *servo;
    uint16_t min;
    uint16_t max;
    int8_t direction;
} watering_t;

void watering_init(watering_t *watering, servo_t *servo);
void watering_set_limit(watering_t *watering, uint16_t min, uint16_t max);
void watering_handler(watering_t *watering, dataset_t *data);

#endif

