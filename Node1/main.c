#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include <string.h>

// Include headerfiles
#include "F_CPU.h"
#include "util/delay.h"
#include "interrupt.h"
#include "accessing_memory_test.h"
#include "adc.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "uart.h"
#include "spi.h"
#include "MCP2515.h"
#include "can.h"

#define TRUE 1
#define FALSE 0

volatile uint8_t START_GAME = FALSE;

int main()
{
  USART_Init();
  SRAM_test();  // Reading and writing to the SRAM
  initMenu();
  interrupt_init();
  can_init();
  init_button();

  // Initializing the can messages
  CAN_msg msg_transmit;
  msg_transmit.id = 1;
  msg_transmit.length = 6;

  CAN_msg msg_receive;
  msg_receive.id = 2;



  while(1){
    if(START_GAME){
      // Do this after PLAY GAME have been chosen in menu
      JOY_pos pos_joy = getJoystickAnalogPos();
      SLIDER_pos pos_slider = getSliderAnalogPos();

      msg_transmit.data[0] = pos_joy.x;
      msg_transmit.data[1] = pos_joy.y;

      msg_transmit.data[2] = pos_slider.left;
      msg_transmit.data[3] = pos_slider.right;

      msg_transmit.data[4] = getButton();

      can_message_send(&msg_transmit);
      printf("X position: %d, Y position: %d\n", msg_transmit.data[0], msg_transmit.data[1]);
      printf("Slider Left position: %d, Slider right position: %d\n", msg_transmit.data[2], msg_transmit.data[3]);
      printf("BUTTON PRESS: %d\n", getButton());
    }
    else{
      _delay_ms(100);
      const char* menuReturned = checkJoystickDirection();
      if(menuReturned != NULL){
        if (strcmp(menuReturned, "Easy") == 0){
          msg_transmit.data[5] = 0;
        }else if (strcmp(menuReturned, "Medium") == 0){
          msg_transmit.data[5] = 1;
        }else if (strcmp(menuReturned, "Hard") == 0){
          msg_transmit.data[5] = 2;
        }
        START_GAME = TRUE;
        printf("%d", msg_transmit.data[5]);
      }




      // if(returnMenu !=)
    }

    //





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




// // Initializing the message containing the joystick position
// CAN_msg msg_joystick;
// msg_joystick.id = 1;
// msg_joystick.length = 2;
//
// // Initializing the message containing the slider position
// CAN_msg msg_slider;
// msg_slider.id = 2;
// msg_slider.length = 2;
//
//
//
// while(1){
//
//   _delay_ms(1000);
//   JOY_pos pos_joy = getJoystickAnalogPos();
//   SLIDER_pos pos_slider = getSliderAnalogPos();
//
//   msg_joystick.data[0] = pos_joy.x;
//   msg_joystick.data[1] = pos_joy.y;
//
//   msg_slider.data[0] = pos_slider.left;
//   msg_slider.data[1] = pos_slider.right;
//
//   can_message_send(&msg_joystick);
//   can_message_send(&msg_slider);
//   printf("X position: %d, Y position: %d\n", msg_joystick.data[0], msg_joystick.data[1]);
//   printf("Slider Left position: %d, Slider right position: %d\n", msg_slider.data[0], msg_slider.data[1]);
//   // checkJoystickDirection();
