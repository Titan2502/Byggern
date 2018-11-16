#include <avr/io.h>
#include <avr/interrupt.h>

void interrupt_init(void){
  DDRE &= ~(1<<PD2);    // Button defined as input (by default)
  cli();
  EMCUCR |= (1<<ISC2);  // Interrupt on rising edge PE0
  GICR |= (1<<INT0);    // Enable interrupt on PE0
  sei();
}
