#include "cmd.h"
// #include <air_temperature.h>
// #include <air_humidity.h>




/*****************************************************
 * Function: cmd_comm()
 * Purpose: Communication between user and program
 * Input: None
 * Returns: None
******************************************************/

void cmd_handler(dataset_t *data)
{
    // By typing different letters into command line this finction shows help menu or data form sensors
    uint8_t value;          // Selected letter is saved into this variable
    //uint16_t moisture = 50;      // Soil Moisture is saved here
    //uint8_t humidity = 60;       // Air humidity is saved here
    //uint8_t temperature = 25;    // Air temperature is saved here
    char string[8];  // String for converted numbers by itoa()

    struct tm* local; 
    time_t t = data->time; 
  
    // Get the localtime 
    local = localtime(&t); 


    value = uart_getc();
    if (value > 0) {  // Data available from UART

        switch (value) {
        case 63:    // By typing '?' into command line the Help menu is shown
            uart_puts("\nHelp: \n");
            uart_puts("? - Show help\n");
            uart_puts("a - Show every information\n");
            uart_puts("m - Show soil moisture\n");
            uart_puts("t - Show air temperature\n");
            uart_puts("h - Show air humidity\n");
            // uart_puts("c - Show current time and date\n");
            break;

        case 109:   // By typing 'm' program will give you current soil moisture
            uart_puts("\nSoil moisture: ");
            //moisture = get_moist();
            itoa(data->hum_soil, string, 10);
            uart_puts(string);
            uart_puts("%\n");
            break;

        case 116:   // By typing 't' program will give you current air temperature
            uart_puts("\nAir temperature: ");
            // temperature = get_temperature();
            itoa(data->temp_air, string, 10);
            uart_puts(string);
            uart_puts("°C\n");
            break;

        case 104:   // By typing 'h' program will give you current air humidity
            uart_puts("\nAir humidity: ");
            // humidity = get_humidity();
            itoa(data->hum_air, string, 10);
            uart_puts(string);
            uart_puts("%\n");
            break;

        case 99:    // By typing 'c' program will give you current time
            uart_puts("\nCurrent time and date: ");
            uart_puts(asctime(local));
            uart_puts("\n");
            break;

        case 97:    // By typing 'a' program will give every current information
            // Time
            uart_puts("\nCurrent time and date: ");
            uart_puts(asctime(local));
            uart_puts("\n");
            
            // Temperature
            uart_puts("Air temperature: ");
            // temperature = get_temperature();
            itoa(data->temp_air, string, 10);
            uart_puts(string);
            uart_puts("°C\n");

            // Humidity
            uart_puts("Air humidity: ");
            // humidity = get_humidity();
            itoa(data->hum_air, string, 10);
            uart_puts(string);
            uart_puts("%\n");
            
            // Moisture
            uart_puts("Soil moisture: ");
            // moisture = get_moist();
            itoa(data->hum_soil, string, 10);
            uart_puts(string);
            uart_puts("%\n");
            break;

        default:    // When you type different letter the program will try to help you
            uart_puts("\nWrong letter was typed. Type \x27?\x27 for help\n");
            break;
        }

        // uart_putc('\n');
    }

}