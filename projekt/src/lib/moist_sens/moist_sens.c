#include <avr/io.h>
#include <avr/interrupt.h>
#include "moist_sens.h"




/**************************************
 * Function: moist_sens_init()
 * Purpose: Configuration of ADC
 * Input: None
 * Returns: None
***************************************/
void moist_sens_init(void){
    
    // Configure Analog-to-Digital Convertion unit
    // Select ADC voltage reference to "AVcc with external capacitor at AREF pin"
    ADMUX = ADMUX | (1<<REFS0);
    // Select input channel ADC0 (voltage divider pin)
    ADMUX = ADMUX & ~(1<<MUX3 | 1<<MUX2 | 1<<MUX1 | 1<<MUX0);
    // Enable ADC module
    ADCSRA = ADCSRA | (1<<ADEN);
    // Enable conversion complete interrupt
    ADCSRA = ADCSRA | (1<<ADIE);
    // Set clock prescaler to 128
    ADCSRA = ADCSRA | (1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0);
}


/****************************************************************************
 * Function: get_moist()
 * Purpose: Reads value from mositure sensor and converts it to percentage
 * Input: None
 * Returns: 16 bit unsigned integer which represents moisture percentage
*****************************************************************************/


uint16_t get_moist(void)
{
    // Start ADC conversion
    ADCSRA = ADCSRA | (1<<ADSC);

    uint16_t moisture;
    uint16_t zero_moist;
    uint16_t max_moist;
    uint16_t moist_constant;

    moisture = ADC;
    /* zero_moist = 300;
    max_moist = 600;
    moist_constant = (max_moist - zero_moist)/100;
    
    moisture = moisture - zero_moist;
    moisture = moisture/moist_constant; */
    moisture = moisture - 2;

    return moisture;
}