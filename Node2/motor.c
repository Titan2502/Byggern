#include <avr/io.h>
#include "F_CPU.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#include "motor.h"
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

void motor_write(uint8_t sliderpos_in){
  // Slider pos [0, 255] => [-255/2 , 255/2]
  uint8_t center = (255/2)+1;
  signed char sliderpos = sliderpos_in; // Changing to signed 8 bit
  sliderpos -= center;
  if (sliderpos >= -center && sliderpos < 0){  // Direction negative
    PORTH &= ~(1<<PH1);
    sliderpos *= -1;
    dac_write(sliderpos);
    //printf("Slider pos, neg: %d\n", sliderpos);
  }

  else if (sliderpos >= 0 && sliderpos <= center){ // Direction positive
    PORTH |= (1<<PH1);
    dac_write(sliderpos);
    //printf("Slider pos, pos: %d\n", sliderpos);
  }
}

int16_t motor_readEncoder(void){
  int16_t reading;

  PORTH &= ~(1<<PH5);   // Set !OE low to enable output of encoder
  PORTH &= ~(1<<PH3);   // Set SEL low to get high byte
  _delay_us(20);        // Wait about 20 microseconds
  reading = (PINK<<8);           // Read MSB
  PORTH |= (1<<PH3);    // Set SEL high to get low byte
  _delay_us(20);        // Wait about 20 microseconds
  reading |= PINK;           // Read LSB
  //motor_reset();        // Toggle !RST to reset encoder
  PORTH |= (1<<PH5);    // Set !OE high to disable output of encoder

  return reading;
}

// DO0-7
