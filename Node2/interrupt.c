#include <avr/io.h>
#include <avr/interrupt.h>

void interrupt_init(void){
  DDRE &= ~(1<<PD2);
  cli();
  EIMSK &= ~(1<<INT2);  // Disable interrupt bit

  // Interrupt on falling edge
  EICRA &= ~(1<<ISC20);
  EICRA |= (1<<ISC21);

  EIFR |= (1<<INTF2); // Clear interrupt flag

  EIMSK |= (1<<INT2); // Enable interrupt bit
  sei();
}
