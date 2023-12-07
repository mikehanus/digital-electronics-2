#ifndef SENSORS_H
#define SENSORS_H

#include <twi.h>
#include <gpio.h>
#include <dataset.h>
#include <moist_sens.h>

#define SENSOR_HUM_MEM 0
#define SENSOR_TEMP_MEM 2
#define SENSOR_CHECKSUM 4

typedef struct
{
    uint8_t dht22_addr;
    uint8_t hum_adc;
    volatile uint8_t *water_source_reg;
    uint8_t water_source_pin;
} sensors_t;

void sensors_init(sensors_t *sensors, uint8_t dht22_addr, uint8_t hum_adc, volatile uint8_t *water_source_reg, uint8_t water_source_pin);
void sensors_update_dataset(sensors_t *sensors, dataset_t *data);

#endif

