// POLLING EXAMPLE(ATmega162)
// 8 buttons connected to PORTA, 8 leds to PORTB
#include <avr/io.h>
#include "util/delay.h"

int main()
{
  // Leds output (the whole port)
  DDRB = 0xFF;
  while(1){
    // Read A, set it out on B
    PORTB = 0xFF;
    //Do something else in X ms
    _delay_ms(500);
    PORTB = 0x00;
    _delay_ms(500);
  }
}
