#include "display.h"

void display_init()
{
    oled_init(OLED_DISP_ON);
    oled_clrscr();

    oled_charMode(DOUBLESIZE);
    // oled_puts("OLED disp.");

    oled_charMode(NORMALSIZE);

    oled_gotoxy(0, 1);
    oled_puts("Podminky v kvetinaci");

    oled_gotoxy(0, 2);
    // oled_drawLine(x1, y1, x2, y2, color)
    oled_drawLine(0, 25, 120, 25, WHITE);

    // Copy buffer to display RAM
    oled_display();
}

void display_show_data(dataset_t *data)
{
	char tmp_str[100];

	itoa(data->temp, tmp_str, 10);
	oled_gotoxy(0, 4);
	oled_puts("Teplota vzduchu\t");
	oled_puts(tmp_str);
	oled_puts(" °C");
	oled_display();

	itoa(data->hum, tmp_str, 10);

	oled_gotoxy(0, 5);
	oled_puts("Vlhkost vzduchu\t");
	oled_puts(tmp_str);
	oled_puts(" %");

	for(long i=0; i < 5000; i++) asm("NOP"); // around 1ms delay

	oled_display();
}

