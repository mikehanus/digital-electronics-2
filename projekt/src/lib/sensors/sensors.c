    twi_start();
    if (twi_write((SENSOR_ADR<<1) | TWI_WRITE) == 0)
	{

        // Set internal memory location
        twi_write(SENSOR_TEMP_MEM);
        twi_stop();

        // Read data from internal memory
        twi_start();
        twi_write((SENSOR_ADR<<1) | TWI_READ);
        actual_data.temp_air = twi_read(TWI_ACK);
        actual_data.hum_air = twi_read(TWI_ACK);
        twi_stop();

        new_sensor_data = 1;
    }
    twi_stop();

