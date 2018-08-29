// POLLING EXAMPLE(ATmega162)
// 8 buttons connected to PORTA, 8 leds to PORTB
#include <avr/io.h>
int main()
{
  // Leds output (the whole port)
  DDRA = 0xFF;
  DDRB = 0xFF;
  while(1){
    // Read A, set it out on B
    PORTB = 0xFF;
    PORTA = 0xFF;
    //Do something else in X ms
  }
}
