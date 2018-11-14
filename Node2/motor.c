#include <avr/io.h>
#include <stdlib.h>
#include "F_CPU.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#include "TWI_Master.h"
#include "dac.h"
#include "motor.h"
#include "PID_controller.h"


void motor_init(void){
  // Setting pins as output
  // PH1 = DIR, PH3 = SEL, PH4 = EN, PH5 = -OE, PH6 = RST
  cli();
  DDRH |= (1<<PH1) | (1<<PH3) | (1<<PH4) | (1<<PH5) | (1<<PH6);
  PORTH |= (1<<PH4) | (1<<PH1);  // Setting Enable pin and direction pin
  motor_reset();
  //sei();
}

void motor_reset(void){
  PORTH &= ~(1<<PH6);
  _delay_us(20);
  PORTH |= (1<<PH6);
}

void motor_write(int16_t correction){
  //correction: [-255, 255], positiv verdi: venstre, negative verdi: høyre
  if (correction >= -255 && correction < 0){
    PORTH |= (1<<PH1);
    dac_write(abs(correction));
    // printf("Slider pos,to the right: %d\n", abs(correction));
  }
  else if (correction > 0 && correction <= 255){
    PORTH &= ~(1<<PH1);
    dac_write(correction);
    // printf("Slider pos,to the left: %d\n", correction);
  }
}


void motor_PID(uint8_t sliderpos, PID_parameters *pid_st){
  //printf("sliderpos in motor_PID: %d \n", sliderpos);
  sliderpos = (sliderpos-255)*-1;
  int16_t reference = (int16_t)(((int32_t)sliderpos)*9393L/255L);
  int16_t measurement = motor_readEncoder();
  int16_t correction = PID_controller(reference, measurement, pid_st);
  motor_write(correction);
  // printf("Reference: %d\n", reference);
  //printf("Correction: %d\n", correction);
}


int16_t motor_readEncoder(void){
  int16_t reading;

  PORTH &= ~(1<<PH5);   // Set !OE low to enable output of encoder
  PORTH &= ~(1<<PH3);   // Set SEL low to get high byte
  _delay_us(40);        // Wait about 20 microseconds
  reading = (PINK<<8);           // Read MSB
  PORTH |= (1<<PH3);    // Set SEL high to get low byte
  _delay_us(40);        // Wait about 20 microseconds
  reading |= PINK;           // Read LSB
  //motor_reset();        // Toggle !RST to reset encoder
  PORTH |= (1<<PH5);    // Set !OE high to disable output of encoder

  printf("\nEncoderValue:  %d\n", reading);
  return reading;
}

// DO0-7
