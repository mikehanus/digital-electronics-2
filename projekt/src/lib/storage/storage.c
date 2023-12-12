#include "storage.h"

// see https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf

void EEPROM_write(uint32_t addr, uint8_t val)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE)) ;
	/* Set up address and Data Registers */
	EEAR = addr;
	EEDR = val;
	/* Write logical one to EEMPE */
	EECR |= (1<<EEMPE);
	/* Start eeprom write by setting EEPE */
	EECR |= (1<<EEPE);
}


uint8_t EEPROM_read(uint32_t addr)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));
	/* Set up address register */
	EEAR = addr;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	return EEDR;
}


void storage_read(storage_t *storage, dataset_t *data, uint32_t pos)
{
	uint8_t *iter = ((uint8_t *)data);
	for(uint32_t i = 0; i < sizeof(dataset_t); i++)
	{
		iter[i] = EEPROM_read(i + storage->buffer_start - pos*sizeof(dataset_t));
	}
}

void storage_write(storage_t *storage, dataset_t *data)
{
	uint8_t *iter = ((uint8_t *)data);
	for(uint32_t i = 0; i < sizeof(dataset_t); i++)
	{
		EEPROM_write(i + storage->buffer_start, iter[i]);
	}
	storage->buffer_start += sizeof(dataset_t);

	if(storage->buffer_start + sizeof(dataset_t) > 1000)
	{
		storage->buffer_start = 0;
	}
}

void storage_init(storage_t *storage)
{
	dataset_t data;
	time_t last_time = 0;
	storage->buffer_start = 0;
	storage_read(storage, &data, 0);
	last_time = data.time;

	while(data.time >= last_time)
	{
		storage->buffer_start += sizeof(dataset_t);
		storage_read(storage, &data, 0);

		if(storage->buffer_start + sizeof(dataset_t) > 1000)
		{
			storage->buffer_start = 0;
			break;
		}
	}
}

