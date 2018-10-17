#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "F_CPU.h"
#include <avr/sleep.h>
#include "util/delay.h"

// Include headerfiles

#include "uart.h"
#include "accessing_memory_test.h"
#include "adc.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "spi.h"
#include "MCP2515.h"
#include "can.h"

// Definitions


int main()
{
  USART_Init();
  MCUCR |= (1<<SRE);  // Init Sram??
  // SFIOR |= (1<<XMM2): // Release PC7-PC4 for normal Port Pin function.
  SRAM_test();  // Reading and writing to the SRAM
  initMenu();


  // -------- Enable interrupt ------------
  DDRE &= ~(1<<PD2);
  cli();
  EMCUCR |= (1<<ISC2);
  GICR |= (1<<INT0);
  sei();
  // --------------------------------------

  //---------- CAN message ----------------
  can_init();
  CAN_msg message;
  message.id = 321;
  message.length = 1;
  message.data[0] = (uint8_t)6;
  can_message_send(&message);
  // --------------------------------------
  // CAN_msg msg;
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

  while(1){
    checkJoystickDirection();

    //----------- MCP write read Test ------------- //
    // mcp2515_write(MCP_CANCTRL, 0xf1);
    // printf("0x%x\r\n", mcp2515_read(MCP_CANCTRL));
    // _delay_us(100);
    //----------------------------------------------//



    // -----------JOYSTICK/SLIDER READ AND PRINT DATA-----------
    // JOY_pos posJoy = getJoystickAnalogPos();
    // SLIDER_pos posSlider = getSliderAnalogPos();
    // printf("JOY_X: %d JOY_Y: %d\r" , posJoy.x, posJoy.y);
    // printf("SLIDER_L: %d SLIDER_R: %d\r" , posSlider.left, posSlider.right);
    // printf("JOYSTICK POSITION: ");
    // getJoystickDirection(10);
    // _delay_ms(1000);

    // printf("SLIDER_L: %d SLIDER_R: %d\r" , adc_read(SLIDER_L), adc_read(SLIDER_R));

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
