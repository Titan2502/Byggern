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

volatile uint8_t CAN_MESSAGE_PENDING = 0;

int main()
{
  USART_Init();
  interrupt_init(); // Enable interrupt
  can_init();
  pwm_init();
  adc_ir_init();
  game_init(3);   // 3 Lives
  dac_init();
  motor_init();
  // TWCR |= (1<<TWIE);    // enable interrupt



  //---------- CAN message send back to node 1 ----------------
  CAN_msg message;
  message.id = 321;
  message.length = 1;
  message.data[0] = (uint8_t)6;
  can_message_send(&message);
  _delay_ms(50);
  // --------------------------------------


  CAN_msg msg_controller;  // Message received

  while(1){
    if(CAN_MESSAGE_PENDING){
      CAN_MESSAGE_PENDING = 0;
      msg_controller = can_data_receive();
      pwm_set_duty_cycle(msg_controller.data[0]);
      dac_write(msg_controller.data[3]);
      printf("Encoder: 0x%x\r\n", motor_readEncoder());


      // printf("X position: %d, Y position: %d\n", msg_controller.data[0], msg_controller.data[1]);
      // printf("Slider Left position: %d, Slider right position: %d\n", msg_controller.data[2], msg_controller.data[3]);
    }

    game_get_lives();

  }
}

ISR(INT2_vect){
  CAN_MESSAGE_PENDING = 1;
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
