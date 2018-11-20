#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

// Include headerfiles

#include "F_CPU.h"
#include "util/delay.h"
#include "interrupt.h"
#include "uart.h"
#include "spi.h"
#include "MCP2515.h"
#include "can.h"
#include "pwm.h"
#include "adc_ir.h"
#include "game.h"
#include "TWI_Master.h"
#include "dac.h"
#include "motor.h"
#include "PID_controller.h"

#define TRUE 1
#define FALSE 0

volatile uint8_t FIRST_CAN_MESSAGE = FALSE;
volatile uint8_t CAN_MESSAGE_PENDING = FALSE;
volatile uint8_t PID_CHECK_CORRECTION = FALSE;
volatile uint8_t SCORE = 0;
volatile uint32_t COUNTER = 0;

int main()
{
  USART_Init();
  can_init();
  pwm_init();
  adc_ir_init();
  game_init(3);   // 3 Lives
  dac_init();
  motor_init();
  game_solonoid_init();

  //--------- CAN message for communication between node 1 and 2 ---------//
  CAN_msg message_transmit;          // Message send to Node 1
  message_transmit.id = 2;
  message_transmit.length = 2;

  CAN_msg msg_receive;   // Message received from Node 1
  // -------------------------------------------------------------------- //

  PID_parameters pid_struct;                // Struct for parameters for the regulator
  uint8_t best_score = 0;                   // Store best score for sending back to Node 1
  uint8_t game_status[2] = {FALSE, FALSE};  // Game_status = {GAME OVER, LOST LIFE}
  interrupt_init();                         // Enable interrupt


  while(1){
    if(CAN_MESSAGE_PENDING){
      CAN_MESSAGE_PENDING = FALSE;
      msg_receive = can_data_receive();

      // Need this so that PID control starts after first CAN message
      if(FIRST_CAN_MESSAGE == FALSE){
        FIRST_CAN_MESSAGE = TRUE;
        PORTL |= (1<<PL3);
        PID_init_to_winit(msg_receive.data[3], &pid_struct);
      }
      pwm_set_duty_cycle(msg_receive.data[0], msg_receive.data[3]);   // map X position to pwm for servo
      game_solonoid_check(msg_receive.data[2]);  // Check if button is pushed, if so activate
    }

    // Do PID control
    if(PID_CHECK_CORRECTION && FIRST_CAN_MESSAGE){
      PID_CHECK_CORRECTION = FALSE;
      uint8_t sliderposition = msg_receive.data[1];
      motor_PID(sliderposition, &pid_struct);
    }

    // Get info about lost life and game over
    game_get_lives(&game_status[0]);

    // If we lost a life, store the best score
    if(game_status[1]){
      if(SCORE > best_score){
        best_score = SCORE;
      }
      // Scores and counter is reset for next try
      SCORE = 0;
      COUNTER = 0;
    }

    // Do this if GAME OVER
    if(game_status[0]){
      message_transmit.data[0] = 0;
      message_transmit.data[1] = best_score;
      best_score = 0;                         // Reset best score for new game
      ADCSRA &= ~(1<<ADSC);                   // ADC Stop Conversion
      can_message_send(&message_transmit);
      _delay_ms(500);
      CAN_MESSAGE_PENDING = FALSE;
      FIRST_CAN_MESSAGE = FALSE;
      PORTL &= ~(1<<PL3);                     // Indikation for the Arduino for game reset
      game_init(3);                           // Setting lives equal to  3
      can_init();

      SCORE = 0;
      COUNTER = 0;
    }
  }
}

ISR(INT2_vect){
  CAN_MESSAGE_PENDING = TRUE;
}

ISR(TIMER1_OVF_vect){
  PID_CHECK_CORRECTION = TRUE;
  COUNTER += 1;
  if(PID_CHECK_CORRECTION && FIRST_CAN_MESSAGE && ((COUNTER % 31) == 0)){ // sync it up to around 1 sec
    SCORE += 1;
  }
}
