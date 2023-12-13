#ifndef DISPLAY_H
#define DISPLAY_H

#include <twi.h>            // I2C/TWI library for AVR-GCC
#include <uart.h>           // Peter Fleury's UART library
#include <stdlib.h>         // C library. Needed for number conversions
#include <oled.h>           // OLED
#include <dataset.h>


/****************************************************
 *  @brief  Inicialization of diplay 
 *  @return None
*****************************************************/

void display_init();


/****************************************************
 *  @brief  It dispalys measured data
 *  @param  data Actual measured data
 *  @return None
*****************************************************/

void display_show_data(dataset_t *data);

#endif

