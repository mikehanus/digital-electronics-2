/***********************************************************************
 * 
 * The I2C (TWI) bus scanner tests all addresses and detects devices
 * that are connected to the SDA and SCL signals.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2023 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <twi.h>            // I2C/TWI library for AVR-GCC
#include <uart.h>           // Peter Fleury's UART library
#include <stdlib.h>         // C library. Needed for number conversions
#include <stdio.h>
#include <oled.h>

/* Global variables --------------------------------------------------*/


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Call function to test all I2C (TWI) combinations and send
 *           detected devices to UART.
 * Returns:  none
 * 
 * Some known devices:
 *     0x3c - OLED display
 *     0x57 - EEPROM
 *     0x5c - Temp+Humid
 *     0x68 - RTC
 *     0x68 - GY521
 *     0x76 - BME280
 *
 **********************************************************************/

/* Global variables --------------------------------------------------*/
// Declaration of "dht12" variable with structure "DHT_values_structure"
struct DHT_values_structure {
   uint8_t hum_int;
   uint8_t hum_dec;
   uint8_t temp_int;
   uint8_t temp_dec;
   uint8_t checksum;
} dht12;

// Flag for printing new data from sensor
volatile uint8_t new_sensor_data = 0;


// Slave and internal addresses of temperature/humidity sensor DHT12
#define DHT_ADR 0x5c
#define DHT_HUM_MEM 0
#define DHT_TEMP_MEM 2
#define DHT_CHECKSUM 4

/* Function definitions ----------------------------------------------*/
/**********************************************************************
* Function: Main function where the program execution begins
* Purpose:  Wait for new data from the sensor and sent them to UART.
* Returns:  none
**********************************************************************/
int main(void)
{
    char string[127];  // String for converting numbers by itoa()

    oled_init(OLED_DISP_ON);
    oled_clrscr();

    oled_charMode(DOUBLESIZE);
    oled_puts("OLED disp.");

    oled_charMode(NORMALSIZE);

    // oled_gotoxy(x, y)
    oled_gotoxy(0, 2);
    oled_puts("128x64, SHH1106");

    // oled_drawLine(x1, y1, x2, y2, color)
    oled_drawLine(0, 25, 120, 25, WHITE);

    oled_fillCircle(50, 25, 12, 1);

    oled_gotoxy(0, 4);
    oled_puts("BPC-DE2, Brno");

    // Copy buffer to display RAM
    oled_display();

    // TWI
    twi_init();

    // UART
    uart_init(UART_BAUD_SELECT(115200, F_CPU));

    sei();  // Needed for UART

    // Test if sensor is ready
    if (twi_test_address(DHT_ADR) == 0)
        uart_puts("I2C sensor detected\r\n");
    else {
        uart_puts("[ERROR] I2C device not detected\r\n");
        while (1);
    }

    // Timer1
    TIM1_OVF_1SEC();
    TIM1_OVF_ENABLE();

    sei();

    // Infinite loop
    while (1) {
        if (new_sensor_data == 1) {
            /*
            sprintf(string, "%i.%i °C  %i.%i %%", dht12.temp_int, dht12.temp_dec, dht12.hum_int, dht12.hum_dec);
            //uart_puts(string);
            oled_gotoxy(0, 5);
            oled_puts(string);

            //sprintf(string, "  chk: %i\n\r", dht12.checksum);
            //uart_puts(string);
            
            oled_display();*/
            
            /*itoa(dht12.temp_int, string, 10);
            uart_puts(string);
            uart_puts(".");
            itoa(dht12.temp_dec, string, 10);
            uart_puts(string);
            uart_puts(" °C  ");

            itoa(dht12.hum_int, string, 10);
            uart_puts(string);
            uart_puts(".");
            itoa(dht12.hum_dec, string, 10);
            uart_puts(string);

            uart_puts(" %\r\n");*/

            // Do not print it again and wait for the new data
            new_sensor_data = 0;
        }
    }

    // Will never reach this
    return 0;
}


/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
* Function: Timer/Counter1 overflow interrupt
* Purpose:  Read temperature and humidity from DHT12, SLA = 0x5c.
**********************************************************************/
ISR(TIMER1_OVF_vect)
{
    // Test ACK from sensor
    static int n = 0;
    char string[127];
    n++;
    if (n < 5) return;
    n = 0;

    twi_start();
    if (twi_write((DHT_ADR<<1) | TWI_WRITE) == 0) {
        // Set internal memory location
        twi_write(DHT_HUM_MEM);
        twi_stop();
        // Read data from internal memory
        twi_start();
        twi_write((DHT_ADR<<1) | TWI_READ);
        dht12.hum_int = twi_read(TWI_ACK);
        dht12.hum_dec = twi_read(TWI_ACK);
        dht12.temp_int = twi_read(TWI_ACK);
        dht12.temp_dec = twi_read(TWI_ACK);
        dht12.checksum = twi_read(TWI_NACK);
        twi_stop();

        sprintf(string, "%i.%i °C  %i.%i %%", dht12.temp_int, dht12.temp_dec, dht12.hum_int, dht12.hum_dec);
        //uart_puts(string);
        oled_gotoxy(0, 5);
        oled_puts(string);
        oled_display();

        new_sensor_data = 1;
    } else {
        twi_stop();
    }
}