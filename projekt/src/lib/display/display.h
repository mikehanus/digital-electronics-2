#ifndef DISPLAY_H
#define DISPLAY_H

#include <twi.h>            // I2C/TWI library for AVR-GCC
#include <uart.h>           // Peter Fleury's UART library
#include <stdlib.h>         // C library. Needed for number conversions
#include <oled.h>           // OLED
#include <dataset.h>

typedef struct
{
    volatile uint8_t *reg;
    uint8_t pin;
    uint8_t value;
} display_t;

void display_init();
void display_show_data(dataset_t *data);

#endif

