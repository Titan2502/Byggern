#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "TWI_Master.h"
#include "dac.h"


void motor_init(void){
  // Setting pins as output
  // PH1 = DIR, PH3 = SEL, PH4 = EN, PH5 = -OE, PH6 = RST
  cli();
  DDRH |= (1<<PH1) | (1<<PH3) | (1<<PH4) | (1<<PH5) | (1<<PH6);
  PORTH |= (1<<PH4) | (1<<PH1);  // Setting Enable pin and direction pin
  motor_reset();
  sei();
}

void motor_reset(void){
  PORTH &= ~(1<<PH6);
  _delay_us(20);
  PORTH |= (1<<PH6);
}


uint16_t motor_readEncoder(void){
  uint8_t MSB;
  uint8_t LSB;

  PORTH &= ~(1<<PH5);   // Set !OE low to enable output of encoder
  PORTH &= ~(1<<PH3);   // Set SEL low to get high byte
  _delay_us(20);        // Wait about 20 microseconds
  MSB = PINK;           // Read MSB
  PORTH |= (1<<PH3);    // Set SEL high to get low byte
  _delay_us(20);        // Wait about 20 microseconds
  LSB = PINK;           // Read LSB
  motor_reset();        // Toggle !RST to reset encoder
  PORTH |= (1<<PH5);    // Set !OE high to disable output of encoder

  return ((MSB<<8) | LSB);
}

// DO0-7
