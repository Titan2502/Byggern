#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "F_CPU.h"
#include "util/delay.h"


void adc_ir_init(void){
  PRR0 &= ~(1<<PRADC);   // Power Reduction ADC bit disablet to enable the ADC

  // Setting the ADC Enable bit and ADC interrupt Enable
  // Setting prescaler to 128
  ADCSRA |= (1<<ADEN) | (1<<ADIE);
  ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
}


uint8_t adc_ir_read(void){
  // Selecting input channel: ADC0 10x gain. Rest set to 0
  ADMUX |= (1<<MUX0) | (1<<MUX1) | (1<<MUX2);



}

void adc_ir_read(){




  if result <= 8 bits:
    read ADCH
  else if result > 8 bits:
    read ADCL
    then read ADCH
}
