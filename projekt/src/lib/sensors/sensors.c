#include "sensors.h"

void sensors_init()
{
    twi_init();
    moist_sens_init();
}


void sensors_update_dataset(dataset_t *data)
{
    twi_start();
    if (twi_write((DHT22_ADDR<<1) | TWI_WRITE) == 0)
	{
        // Set internal memory location
        twi_write(SENSOR_HUM_MEM);
        twi_stop();

        // Read data from internal memory
        twi_start();
        twi_write((DHT22_ADDR<<1) | TWI_READ);
        data->hum = twi_read(TWI_ACK);
        twi_read(TWI_ACK); // skip hum decimal
        data->temp = twi_read(TWI_ACK);
        twi_read(TWI_ACK); // skip temp decimal
    }
    twi_stop();

    data->moist = get_moist();
}