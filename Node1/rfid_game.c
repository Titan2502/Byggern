#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "F_CPU.h"
#include "util/delay.h"

void rfid_init(void){
  DDRB &= ~(1<<PB1);
  PORTB &= ~(1<<PB1);
}

uint8_t rfid_getSignal(void){
  uint8_t rfid_signal = 0x02 & PINB;
  return rfid_signal;
}
