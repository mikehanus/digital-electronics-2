#include "cmd.h"
// #include <air_temperature.h>
// #include <air_humidity.h>



void cmd_handler(dataset_t *data, watering_t *watering, storage_t *storage)
{
    // By typing different letters into command line this finction shows help menu or data form sensors
    uint8_t value, tmp;          // Selected letter is saved into this variable
    //uint16_t moisture = 50;      // Soil Moisture is saved here
    //uint8_t humidity = 60;       // Air humidity is saved here
    //uint8_t temperature = 25;    // Air temperature is saved here
    char string[8];  // String for converted numbers by itoa()

    struct tm* local;
    time_t t;

	int limit_tmp, data_n = 0;
	dataset_t mydata;

    // Get the localtime
	t = data->time;
    local = localtime(&t);


    value = uart_getc();
    if (value > 0) {  // Data available from UART

        switch (value) {
			case '?':    // By typing '?' into command line the Help menu is shown
				uart_puts("\nHelp: \n"
				          "? - Show help\n"
				          "a - Show every information\n"
				          "A N - Show every information for N last minutes\n"
				          "m - Show soil moisture\n"
				          "t - Show air temperature\n"
				          "h - Show air humidity\n"
				          "c - Show current time and date\n"
				          "C UNIT_TIME - Set current unix time\n"
						  "l - Show moisture limits"
				          "L MIN MAX - Set moister limits\n"
				);
				break;

			case 'm':   // By typing 'm' program will give you current soil moisture
				uart_puts("\nSoil moisture: ");
				//moisture = get_moist();
				itoa(data->moist, string, 10);
				uart_puts(string);
				uart_puts("%\n");
				break;

			case 't':   // By typing 't' program will give you current air temperature
				uart_puts("\nAir temperature: ");
				// temperature = get_temperature();
				itoa(data->temp, string, 10);
				uart_puts(string);
				uart_puts("°C\n");
				break;

			case 'h':   // By typing 'h' program will give you current air humidity
				uart_puts("\nAir humidity: ");
				// humidity = get_humidity();
				itoa(data->hum, string, 10);
				uart_puts(string);
				uart_puts("%\n");
				break;

			case 'L':
				limit_tmp = 0;
				while((tmp = uart_getc()) != '\n' && tmp != ' ') // TEST THIS
				{
					if(tmp == UART_NO_DATA || tmp < '0' || tmp > '9') continue;
					uart_putc(tmp);
					limit_tmp = (limit_tmp * 10) + tmp - '0';
				}
				watering->min = limit_tmp;
				limit_tmp = 0;
				while((tmp = uart_getc()) != '\n')
				{
					uart_putc(tmp);
					if(tmp == UART_NO_DATA || tmp < '0' || tmp > '9') continue;
					limit_tmp = (limit_tmp * 10) + tmp - '0';
				}
				watering->max = limit_tmp;

				uart_puts("Limits were set");

			case 'l':   // By typing 's' program will give you current moisture limis
				uart_puts("\nMoisture limits: from ");
				itoa(watering->min, string, 10);
				uart_puts(string);
				uart_puts("% to ");
				itoa(watering->max, string, 10);
				uart_puts(string);
				uart_puts("%\n");
				break;

			case 'C':
				t = 0;
				while((tmp = uart_getc()) != '\n')
				{
					if(tmp == UART_NO_DATA || tmp < '0' || tmp > '9') continue;
					uart_putc(tmp);
					t = (t * 10) + tmp - '0';
				}
				data->time = t - AVRTIME_TO_UNIXTIME;
				uart_puts("Time was set");

			case 'c':    // By typing 'c' program will give you current time
				uart_puts("\nCurrent time and date: ");
				uart_puts(asctime(local));
				uart_puts("\n");
				break;

			case 'A':
				data_n = 0;
				while((tmp = uart_getc()) != '\n')
				{
					if(tmp == UART_NO_DATA || tmp < '0' || tmp > '9') continue;
					uart_putc(tmp);
					data_n = (data_n * 10) + tmp - '0';
				}

			case 'a':    // By typing 'a' program will give every current information
				uart_puts("\nDate\tTemp [˚C]\tHum [%]\tMoist\n");
				while(1)
				{
					// Time
					uart_puts(asctime(local));
					uart_puts("\t");

					// Temperature
					itoa(data->temp, string, 10);
					uart_puts(string);
					uart_puts("\t");

					// Humidity
					itoa(data->hum, string, 10);
					uart_puts(string);
					uart_puts("\t");

					// Moisture
					itoa(data->moist, string, 10);
					uart_puts(string);
					uart_puts("\n");

					if(data_n > 0)
					{
						data = &mydata;

						data_n--;
						storage_read(storage, data, data_n);
						t = data->time;
						local = localtime(&t);
					}
					else break;

				}
				break;


			default:    // When you type different letter the program will try to help you
				uart_puts("\nWrong letter was typed. Type \x27?\x27 for help\n");
				break;
        }

        // uart_putc('\n');
    }

}

