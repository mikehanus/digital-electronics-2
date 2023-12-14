#include "watering.h"

void watering_init(watering_t *watering, servo_t *servo)
{
    watering->servo = servo;
    servo_set_value(watering->servo, 0);
}

void watering_set_limit(watering_t *watering, uint16_t min, uint16_t max)
{
    watering->min = min;
    watering->max = max;
}

void watering_handler(watering_t *watering, dataset_t *data)
{
    if(watering->servo->value != 160 && watering->servo->value != 20)
        servo_set_value(watering->servo, 20);

    if(watering->servo->value == 20 && data->moist < watering->min)
        servo_set_value(watering->servo, 160);
    if(watering->servo->value != 20 && data->moist > watering->max)
        servo_set_value(watering->servo, 20);
}