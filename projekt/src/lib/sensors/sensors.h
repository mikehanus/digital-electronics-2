#ifndef SENSORS_H
#define SENSORS_H

#include <twi.h>
#include <gpio.h>
#include <dataset.h>
#include <moist_sens.h>

#define DHT22_ADDR 0x5c
#define SENSOR_HUM_MEM 0
#define SENSOR_TEMP_MEM 2
#define SENSOR_CHECKSUM 4

typedef struct
{
} sensors_t;

void sensors_init();
void sensors_update_dataset(dataset_t *data);

#endif

