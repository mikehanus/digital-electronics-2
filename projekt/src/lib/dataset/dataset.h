#ifndef DATASET_H
#define DATASET_H

typedef struct  {
   uint32_t time;
   uint8_t temp_air;
   uint8_t hum_air;
   uint8_t hum_soil;
} dataset_t;

#endif

