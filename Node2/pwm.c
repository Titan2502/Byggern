#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "F_CPU.h"
#include "util/delay.h"


void pwm_init(void){
  // Enabling mode 14 - Fast PWM
  TCCR3A &= ~(1<<WGM30);
  TCCR3A |= (1<<WGM31);
  TCCR3B |= (1<<WGM32) | (1<<WGM33);

  // Set OCnA on compare and set to noninverting mode
  TCCR3A &= ~(1<<COM3A0);
  TCCR3A |= (1<<COM3A1);

  // Set prescaler to clk/8
  TCCR3B |= (1<<CS31);
  TCCR3B &= ~((1<<CS30) | (1<<CS32));


  // Defining TOP to be 0x9C3F
  ICR3H = 0x9C;
  ICR3L = 0x3F;

  // Duty Cycle to 0xBB8
  OCR3AH = 0x0B;
  OCR3AL = 0xB8;

  //Pin E3,4,5 defined as output
  DDRE |= (1<<DDE3) | (1<<DDE4) | (1<<DDE5);
}


void pwm_set_duty_cycle(uint8_t xValue, uint8_t difficulty){
  uint16_t dutyCycle;
  if(difficulty == 2){
    dutyCycle = 1800 + xValue*((4200 -1800)/255); // Reverted mode - hard difficulty
  }else{
    dutyCycle = 4200 + xValue*((1800-4200)/255);
  }
  // Overflow check
  if( dutyCycle > 4200 ){
    dutyCycle = 4200;
  }else if( dutyCycle < 1800 ){
    dutyCycle = 1800;
  }
  // Set duty cycle for Higher and Lower 8 bits
  OCR3AH = (dutyCycle >> 8);
  OCR3AL = dutyCycle;
}
