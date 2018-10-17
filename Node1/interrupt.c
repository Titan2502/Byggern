#include <avr/io.h>
#include <avr/interrupt.h>

void interrupt_init(void){
  DDRE &= ~(1<<PD2);
  cli();
  EMCUCR |= (1<<ISC2);
  GICR |= (1<<INT0);
  sei();
}
