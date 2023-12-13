#ifndef DATASET_H
#define DATASET_H

#include <avr/io.h>

   /** @struct dataset_t
   *  Structure used for saving of measurements and reading them
   *
   *  @var dataset::time
   *    Actual time in UNIX timeformat
   *  @var dataset::temp
   *    Measured air temperature
   *  @var dataset::hum
   *    Measured air humidity
   *  @var dataset::moist
   *    Measured soil moisture
   */


typedef struct  {
   uint32_t time;
   uint8_t temp;
   uint8_t hum;
   uint8_t moist;
} dataset_t;

#endif

