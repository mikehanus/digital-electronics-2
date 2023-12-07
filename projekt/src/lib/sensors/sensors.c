#include "sensors.h"

void sensors_init(sensors_t *sensors, uint8_t dht22_addr, uint8_t hum_adc, volatile uint8_t *water_source_reg, uint8_t water_source_pin)
{
    sensors->dht22_addr = dht22_addr;
    sensors->hum_adc = hum_adc;
    sensors->water_source_reg = water_source_reg;
    sensors->water_source_pin = water_source_pin;
    twi_init();
    moist_sens_init();
}


void sensors_update_dataset(sensors_t *sensors, dataset_t *data)
{
    twi_start();
    if (twi_write((sensors->dht22_addr<<1) | TWI_WRITE) == 0)
	{
        // Set internal memory location
        twi_write(SENSOR_TEMP_MEM);
        twi_stop();

        // Read data from internal memory
        twi_start();
        twi_write((sensors->dht22_addr<<1) | TWI_READ);
        data->temp_air = twi_read(TWI_ACK);
        data->hum_air = twi_read(TWI_ACK);
    }
    twi_stop();

    data->hum_soil = get_moist();
}