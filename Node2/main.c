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


volatile uint8_t CAN_MESSAGE_PENDING = FALSE;
volatile uint8_t PID_CHECK_CORRECTION = FALSE;

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
  // TWCR |= (1<<TWIE);    // enable interrupt

  //---------  Initializing the PID_controller ---------//
  float kp = 0.022;
  float ki = 0.005;
  float kd = 0.01;
  PID_parameters pid_struct;    // Parameters for the regulator
  PID_init(kp, ki, kd, &pid_struct);
  PID_timer_enable();
  // ------------------------------------------------- //



  //--------- CAN message for communication between node 1 and 2 ---------//
  CAN_msg message;          // Message send to Node 1
  message.id = 2;
  message.length = 1;

  CAN_msg msg_controller;   // Message received from Node 1
  // ------------------------------------------------ //
  interrupt_init(); // Enable interrupt

  while(1){
    // Recieve controller output from Node 1
    if(CAN_MESSAGE_PENDING){
      CAN_MESSAGE_PENDING = FALSE;
      msg_controller = can_data_receive();

      pwm_set_duty_cycle(msg_controller.data[0]);
      //motor_write(msg_controller.data[3]);
      game_solonoid_check(msg_controller.data[4]);




    }

    if(PID_CHECK_CORRECTION){
      PID_CHECK_CORRECTION = FALSE;
      uint8_t sliderposition = msg_controller.data[3];
      motor_PID(sliderposition, &pid_struct);
    }
    game_get_lives();
  }
}

ISR(INT2_vect){
  CAN_MESSAGE_PENDING = TRUE;
}

ISR(TIMER1_OVF_vect){
  PID_CHECK_CORRECTION = TRUE;
}

// CAN_msg msg;
// // --------------------------------------
// printf("BEFORE---------\r\n");
// printf("CANSTAT: 0x%x\r\n", mcp2515_read(MCP_CANSTAT));
// printf("CANINFE: 0x%x\r\n", mcp2515_read(MCP_CANINTF));
// can_message_send(&message);
//
// printf("CANSTAT: 0x%x\r\n", mcp2515_read(MCP_CANSTAT));
// printf("CANINFE: 0x%x\r\n", mcp2515_read(MCP_CANINTF));
// _delay_ms(1000);
// msg = can_data_receive();
// printf("%d\n", msg.id);
// printf("CANSTAT: 0x%x\r\n", mcp2515_read(MCP_CANSTAT));
// printf("CANINFE: 0x%x\r\n", mcp2515_read(MCP_CANINTF));
// _delay_ms(1000);

// printf( "Hello1\n" );
// printf("0x%x\r\n", SPI_MasterTransReceive(number));
// printf( "Hello2\n" );


// IN main
//----------- MCP write read Test ------------- //
// printf("0x%x\r\n", mcp2515_read(MCP_CANSTAT));
// _delay_ms(300);
//----------------------------------------------//
// printf("0x%x\r\n", SPI_MasterTransReceive(0x11));
// _delay_ms(300);
// USART_Transmit('B', NULL);
// printf( "Veriy najs\n" );
// _delay_ms(100);

//printf("Encoder: 0x%x\r\n", motor_readEncoder());
// printf("X position: %d, Y position: %d\n", msg_controller.data[0], msg_controller.data[1]);
// printf("Slider Left position: %d, Slider right position: %d\n", msg_controller.data[2], msg_controller.data[3]);
// printf("BUTTON PRESS: %d\n", msg_controller.data[4]);
