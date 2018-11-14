#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "F_CPU.h"
#include "util/delay.h"
#include "adc_ir.h"
#include "game.h"

#define TRUE 1
#define FALSE 0

game_stats stats;

void game_init(uint8_t lives){
  stats.lives = lives;
}


uint8_t game_get_lives(void){
  uint8_t value = adc_ir_read();
  // printf("Value 0x%x\r\n", value);
  // Max 0x8b = 162, Min 0x4 = 4,
  uint8_t trigger_value = 0x40;
  if(value < trigger_value ){
    stats.lives--;
    printf("You lost a life!\n\rCurrent lives left: %d\n\r", stats.lives);
    if(stats.lives == 0){
      printf("Out of lives\n\r");
      printf("GAME OVER!\n");
      return TRUE;
      // CALL SOME KIND OF TERMINATION!!!
    }

    _delay_ms(1000);    // For bouncing! 1 sec settling time
    // Continue until the ball is removed
    while(adc_ir_read() < trigger_value);
  }
  return FALSE;
}

void game_solonoid_init(void){
  DDRL	|= (1 << DDL0);
  PORTL |= (1 << PL0);
}

void game_solonoid_check(uint8_t checkbutton){
  if (checkbutton == 0){
    PORTL |= (1<<PL0);
    //_delay_ms(20);
  }
  if (checkbutton == 1){
    PORTL &= ~(1<<PL0);
    _delay_ms(20);
  }

}
