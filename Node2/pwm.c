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

  // Set OCnA on compare and set to inverting mode
  TCCR3A |= (1<<COM3A0) | (1<<COM3A1);

  // Set prescaler to clk/8
  TCCR3B |= (1<<CS31);
  TCCR3B &= ~((1<<CS30) | (1<<CS32));


  // Defining TOP to be 0x9C3F
  ICR3H = 0x9C;
  ICR3L = 0x3F;

  // Duty Cycle to 0xBB8
  OCR3AH = 0x0B;
  OCR3AL = 0xB8;

  DDRE |= (1<<DDE3) | (1<<DDE4) | (1<<DDE5); //Pin E3,4,5 defined as output
}


void pwm_set_duty_cycle(uint8_t xValue){
  uint16_t dutyCycle = 1800 + xValue*((4200-1800)/255);

  if( dutyCycle > 4200 ){
    dutyCycle = 4200;
  }
  else if( dutyCycle < 1800 ){
    dutyCycle = 1800;
  }

  // Set duty cycle for Higher and Lower 8 bits
  OCR3AH = (dutyCycle >> 8);
  OCR3AL = dutyCycle;
}

// ISR(INT3_vect){
//
// }






// unsigned int TIM16_ReadTCNTn( void ){
//   unsigned char sreg;
//   unsigned int i;
//   /* Save global interrupt flag */
//   sreg = SREG;
//   /* Disable interrupts */
//   __disable_interrupt();
//   /* Read TCNTn into i */
//   i = TCNTn;
//   /* Restore global interrupt flag */
//   SREG = sreg;
//   return i;
// }
//
// void TIM16_WriteTCNTn( unsigned int i ){
//   unsigned char sreg;
//   unsigned int i;
//   /* Save global interrupt flag */
//   sreg = SREG;
//   /* Disable interrupts */
//   __disable_interrupt();
//   /* Set TCNTn to i */
//   TCNTn = i;
//   /* Restore global interrupt flag */
//   SREG = sreg;
// }
