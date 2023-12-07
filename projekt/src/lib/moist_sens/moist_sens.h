#ifndef MOIST_SENS_H
# define MOIST_SENS_H

/**********************************************************************************
 *  @brief Configures the ADC and input pin
 * 
 *  @param  None
 *  @return None
***********************************************************************************/
extern void moist_sens_init(void);

/**********************************************************************************
 *  @brief Starts the ADC conversion on pin PC0 (A0) and returns converted value
 * 
 *  @param  None
 *  @return None
***********************************************************************************/
extern unsigned short get_moist(void);



#endif