#include "F_CPU.h"
#include <avr/io.h>
#include <stdlib.h>
#include "util/delay.h"
#include "adc.h"

#define ADC_ADDRESS 0x1400
#define CONVERSION_WAIT_TIME 60
#define STEADY_OUTPUT_WAIT_TIME 1

char adc_read(ADC_channel channel){
  _delay_us(STEADY_OUTPUT_WAIT_TIME);
  volatile char *adc = (char *) ADC_ADDRESS;
  *adc = channel;
   _delay_us(CONVERSION_WAIT_TIME);
  return *adc;
}
