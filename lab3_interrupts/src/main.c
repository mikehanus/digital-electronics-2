#include <avr/io.h>
#include <avr/interrupt.h>
#include <gpio.h>
#include "timer.h"

int main(void)
{
  //GPIO_mode_output(&DDRB, 5);
  DDRB |= (1 << 5) | (1 << 0) | (1 << 1);
  PORTB |= 1;

  TIM1_OVF_262MS();
  TIM1_OVF_ENABLE();

  TIM0_OVF_16MS();
  TIM0_OVF_ENABLE();

  sei();

  while(1) ;

  //for(long i=0; i < 1000000; i++) asm("NOP");
  return 0;
}

ISR(TIMER1_OVF_vect)
{
  PORTB ^= (1 << 5);
}

ISR(TIMER0_OVF_vect)
{
  TCNT0 = 27;
  static uint8_t n_overflows = 0;
  n_overflows++;
  if(n_overflows >= 30) // 500ms
  {
    PORTB ^= ((1 << 0) | (1 << 1));
    n_overflows = 0;
  }
}