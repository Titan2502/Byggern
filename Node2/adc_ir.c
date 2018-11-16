#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "F_CPU.h"
#include "util/delay.h"
#include "adc_ir.h"

void adc_ir_init(void){
  ADCSRA |= (1<<ADEN);  // Setting the ADC Enable bit and ADC interrupt Enable  | (1<<ADIE)
  ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);  // Setting prescaler to 128
  ADMUX |= (1<<REFS0);  // AVCC with external capacitor at AREF pin
  ADMUX |= (1<<ADLAR);  // left adjust results
}


uint8_t adc_ir_read(void){
  // Selecting input channel: ADC7 - Single ended input
  ADMUX |= (1<<MUX0) | (1<<MUX1) | (1<<MUX2);
  ADCSRB &= ~(1<<MUX5);

  ADCSRA |= (1<<ADSC);   // ADC start Conversion

  while((ADCSRA & (1<<ADSC))){}  // Wait until convertion is complete
  //  printf("HELLOOO FROM ADCIR\n"); // INSIDE WHILE
  return ADCH;
}
