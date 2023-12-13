#ifndef STORAGE_H
#define STORAGE_H

#include <dataset.h>
#include <avr/io.h>
#include <time.h>

typedef struct {
	uint16_t buffer_start;
} storage_t;

/****************************************************
 *  @brief  Storage inicialization
 *  @param  storage Storage setup
 *  @return None
*****************************************************/
void storage_init(storage_t *storage);


/****************************************************
 *  @brief  Writes values into EEPROM
 *  @param  addr Address to where data are written
 *  @param  val Data that are going to be written

 *  @return None
*****************************************************/
void EEPROM_write(uint16_t addr, uint8_t val);


/****************************************************
 *  @brief  Reads values from EEPROM
 *  @param  addr Address from where dara are read
 *  @return Returns value from EEPROM
*****************************************************/
uint8_t EEPROM_read(uint16_t addr);


/****************************************************
 *  @brief  Writes data into EEPROM via 
 * 			EEPROM_write function
 *  @param  data Actual measured data
 *  @param  storage Storage setup
 *  @return None
*****************************************************/
void storage_write(storage_t *storage, dataset_t *data);


/****************************************************
 *  @brief  Reads data into EEPROM via 
 * 			EEPROM_read function
 *  @param  data Saved data
 *  @param  storage Storage setup
 *  @param  pos Position in EEPROM that says 
 * 			from where to start read
 *  @return None
*****************************************************/
void storage_read(storage_t *storage, dataset_t *data, uint8_t pos);

//size_t storage_read_multiple(storage_t *storage, dataset_t **data, uint32_t n); // needed?


#endif

