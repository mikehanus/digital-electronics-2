#ifndef CMD_H
#define CMD_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <time.h>
#include <uart.h>
#include <moist_sens.h>
#include <dataset.h>

/****************************************************
 *  @brief  Enables communication 
 *          between user and program via command line
 *  @param  None
 *  @return None
*****************************************************/

void cmd_handler(dataset_t *data);


#endif