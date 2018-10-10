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


int main()
{
  USART_Init();

  //---------- CAN message ----------------
  can_init();
  // CAN_msg message;
  // message.id = 321;
  // message.length = 1;
  // message.data[0] = (uint8_t)6;
  // can_message_send(&message);
  // --------------------------------------

  while(1){
    //----------- MCP write read Test ------------- //
    // mcp2515_write(MCP_CANCTRL, 0xf1);
    // printf("0x%x\r\n", mcp2515_read(MCP_CANCTRL));
    // _delay_us(100);
    //----------------------------------------------//


    // // USART_Transmit('G', NULL);
    // // printf( "HELLOOOOOOOOOOOOOO\n" );
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
