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
#include "rfid_game.h"
#include "oled.h"
#include "menu.h"
#include "uart.h"
#include "spi.h"
#include "MCP2515.h"
#include "can.h"

#define TRUE 1
#define FALSE 0

volatile uint8_t START_GAME = FALSE;
volatile uint8_t CAN_MESSAGE_PENDING = FALSE;
volatile uint8_t HIGHSCORES[3] = {0, 0, 0};     // Store the three best highscores
volatile uint8_t ACCESS_STATUS = FALSE;

int main()
{
  USART_Init();
  SRAM_init();
  SRAM_test();  // Reading and writing to the SRAM
  initMenu(HIGHSCORES);
  interrupt_init();
  can_init();
  init_button();
  rfid_init();

  // Initializing the can messages
  CAN_msg msg_transmit;
  msg_transmit.id = 1;
  msg_transmit.length = 4;

  CAN_msg msg_receive;
  msg_receive.id = 2;


  while(1){
    uint8_t temp_acces = rfid_getSignal();
    if(temp_acces){
      ACCESS_STATUS = TRUE;
    }
    if(ACCESS_STATUS){
      // Do this when difficulty is chosen in play game
      if(START_GAME){
        JOY_pos pos_joy = getJoystickAnalogPos();
        SLIDER_pos pos_slider = getSliderAnalogPos();

        msg_transmit.data[0] = pos_joy.x;
        msg_transmit.data[1] = pos_slider.right;
        msg_transmit.data[2] = getButton();
        // printf("Joyposx: %d\n", msg_transmit.data[0]);
        // printf("slider: %d\n", msg_transmit.data[1]);
        // printf("button: %d\n", msg_transmit.data[2]);

        can_message_send(&msg_transmit);

        if(CAN_MESSAGE_PENDING){
          CAN_MESSAGE_PENDING = FALSE;
          ACCESS_STATUS = FALSE;
          msg_receive = can_data_receive();
          if(msg_receive.data[0] == 0){
            START_GAME = FALSE;
            printf("CAN MESSAGE RECIEVED - GAME OVER!! VERDI %d\n");
            uint8_t current_highscore = msg_receive.data[1];
            if (current_highscore > HIGHSCORES[0]){
              HIGHSCORES[0] = current_highscore;
            }
            for( int i = 1; i < 3; i++ ){
              uint8_t temp_hs = HIGHSCORES[i];
              if (current_highscore > HIGHSCORES[i]){
                HIGHSCORES[i-1] = temp_hs;
                HIGHSCORES[i] = current_highscore;
              }
              initMenu(HIGHSCORES);

            }
          }
        }
      }

      else{
        const char* menuReturned = checkJoystickDirection();
        if(menuReturned != NULL){
          if (strcmp(menuReturned, "Easy") == 0){
            msg_transmit.data[3] = 0;
            START_GAME = TRUE;
          }else if (strcmp(menuReturned, "Medium") == 0){
            msg_transmit.data[3] = 1;
            START_GAME = TRUE;
          }else if (strcmp(menuReturned, "Hard") == 0){
            msg_transmit.data[3] = 2;
            START_GAME = TRUE;
          }
          printf("%d", msg_transmit.data[3]);
        }
      } // else
    } // if(ACCESS_STATUS)
  } // while
} // int main



ISR(INT0_vect){
  CAN_MESSAGE_PENDING = TRUE;
}
