#ifndef ADC_H
#define ADC_H
#include <stdio.h>

typedef enum{
  JOY_Y = 4,
  JOY_X = 5,
  SLIDER_L = 6,
  SLIDER_R = 7
} ADC_channel;

char adc_read(ADC_channel channel);

#endif
