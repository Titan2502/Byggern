#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "F_CPU.h"
#include <avr/sleep.h>
#include "util/delay.h"

// Include headerfiles

#include "uart.h"
#include "spi.h"
#include "MCP2515.h"
#include "can.h"
#include "interrupt.h"


int main()
{
  USART_Init();
  interrupt_init(); // Enable interrupt
  can_init();
  //---------- CAN message ----------------

  CAN_msg message;
  message.id = 321;
  message.length = 1;
  message.data[0] = (uint8_t)6;
  can_message_send(&message);
  _delay_ms(50);

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

  while(1){


    //----------- MCP write read Test ------------- //
    // printf("0x%x\r\n", mcp2515_read(MCP_CANSTAT));
    // _delay_ms(300);
    //----------------------------------------------//
    // printf("0x%x\r\n", SPI_MasterTransReceive(0x11));
    // _delay_ms(300);
    // USART_Transmit('B', NULL);
    // printf( "Veriy najs\n" );
    // _delay_ms(100);
    // printf("ADC test...\n\r");
    // volatile char *ext_ram = (char *) 0x1500;
    // for (uint16_t i = 0; i < 0x200; i++) {
    //   uint8_t some_value = rand();
    //   ext_ram[i] = some_value;
    //   uint8_t retreived_value = ext_ram[i];
    //   // if (!(i%100)){
    //   //   printf("Write phase: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
    //   // }
    // }


  }
}
