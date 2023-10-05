#include <avr/io.h>
//#include "gpio.h"
//#include <util/delay.h> // Functions for busy-wait delay loops

int main(void)
{
  /*
  GPIO_mode_output(&DDRB, 0);
  GPIO_mode_output(&DDRB, 5);
  while(1)
  {
    GPIO_write_high(&PORTB, 0);
    GPIO_write_high(&PORTB, 5);
    for(long i=0; i < 1000000; i++) asm("NOP");
    GPIO_write_low(&PORTB, 0);
    GPIO_write_low(&PORTB, 5);
    for(long i=0; i < 1000000; i++) asm("NOP");
  }*/
  
  DDRB |= (1 << 0) | (1 << 5);
  //PORTD |= (1 << 2);
  while(1)
  {
    //if(PIND & (1 << 2))
      PORTB ^= ((1 << 0) | (1 << 5));
    for(long i=0; i < 1000000; i++) asm("NOP");
  }
}