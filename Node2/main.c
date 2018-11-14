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
volatile uint8_t GAME_OVER = FALSE;
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
  // ------------------------------------------------ //

  PID_parameters pid_struct;    // Parameters for the regulator
  interrupt_init(); // Enable interrupt

  // char str[10];
  // sprintf(str,"%d",19);
  // printf("%s\n", str);


  while(1){
    printf("SCORE: %d\n",  SCORE);
    if(CAN_MESSAGE_PENDING){
      CAN_MESSAGE_PENDING = FALSE;
      msg_receive = can_data_receive();
      printf("HELLOOO\n");

      // Need this so that PID control starts after first CAN message
      if(FIRST_CAN_MESSAGE == FALSE){
        FIRST_CAN_MESSAGE = TRUE;
        printf("HELLOOO1\n");
        PID_init_to_winit(msg_receive.data[3], &pid_struct);
      }

      pwm_set_duty_cycle(msg_receive.data[0]);   // map X position to pwm for servo
      game_solonoid_check(msg_receive.data[2]);  // Check if button is pushed, if so activate
    }

    // Do PID control
    if(PID_CHECK_CORRECTION && FIRST_CAN_MESSAGE){
      printf("HELLOOO2\n");
      PID_CHECK_CORRECTION = FALSE;
      uint8_t sliderposition = msg_receive.data[1];
      motor_PID(sliderposition, &pid_struct);
    }

    GAME_OVER = game_get_lives();
    if(GAME_OVER){
      message_transmit.data[0] = 0;
      message_transmit.data[1] = SCORE;
      ADCSRA &= ~(1<<ADSC);
      can_message_send(&message_transmit);
      _delay_ms(500);
      CAN_MESSAGE_PENDING = FALSE;
      FIRST_CAN_MESSAGE = FALSE;
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
  if(PID_CHECK_CORRECTION && FIRST_CAN_MESSAGE && ((COUNTER % 20) == 0)){
    SCORE += 1;
  }
}
