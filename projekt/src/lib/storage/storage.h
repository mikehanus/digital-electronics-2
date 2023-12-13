#ifndef STORAGE_H
#define STORAGE_H

#include <dataset.h>
#include <avr/io.h>
#include <time.h>

typedef struct {
	uint16_t buffer_start;
} storage_t;

void storage_init(storage_t *storage);

void EEPROM_write(uint16_t addr, uint8_t val);
uint8_t EEPROM_read(uint16_t addr);

void storage_write(storage_t *storage, dataset_t *data);
void storage_read(storage_t *storage, dataset_t *data, uint8_t pos);

//size_t storage_read_multiple(storage_t *storage, dataset_t **data, uint32_t n); // needed?


#endif

