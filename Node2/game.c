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
  DDRL	|= (1 << DDL1);
  DDRL	|= (1 << DDL3);
}


void game_get_lives(uint8_t *game_status){
  game_status[0] = FALSE;
  game_status[1] = FALSE;
  uint8_t value = adc_ir_read();
  uint8_t trigger_value = 0x20; // For work station 18, trigger_value = 0x40
  if(value < trigger_value ){
    stats.lives--;
    PORTL |= (1<<PL1);
    printf("You lost a life! Current lives left: %d\n", stats.lives);
    if(stats.lives == 0){
      printf("Out of lives! ");
      printf("GAME OVER!\n");
      while(adc_ir_read() < trigger_value);
      PORTL &= ~(1<<PL1);
      game_status[0] = TRUE;  // GAME OVER
    }

    _delay_ms(2000);    // For bouncing! 2 sec settling time
    while(adc_ir_read() < trigger_value); // Continue until the ball is removed
    PORTL &= ~(1<<PL1);
    game_status[1] = TRUE;  // LOST LIFE
  }
}


void game_solonoid_init(void){
  DDRL	|= (1 << DDL0);
  PORTL |= (1 << PL0);
}


void game_solonoid_check(uint8_t checkbutton){
  if (checkbutton == 0){
    PORTL |= (1<<PL0);
  }
  if (checkbutton == 1){
    PORTL &= ~(1<<PL0);
    _delay_ms(20);
  }

}
