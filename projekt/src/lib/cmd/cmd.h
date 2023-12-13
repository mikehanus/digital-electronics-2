#ifndef CMD_H
#define CMD_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <time.h>
#include <uart.h>
#include <moist_sens.h>
#include <dataset.h>
#include <watering.h>
#include <storage.h>

/****************************************************
 *  @brief  Enables communication
 *          between user and program via command line
 *  @param  data Actual measured data
 *  @param  watering Watering setup
 *  @param  storage Storage setup
 *  @return None
*****************************************************/

void cmd_handler(dataset_t *data, watering_t *watering, storage_t *storage);


#endif

