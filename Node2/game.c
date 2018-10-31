#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "F_CPU.h"
#include "util/delay.h"
#include "adc_ir.h"
#include "game.h"

game_stats stats;

void game_init(uint8_t lives){
  stats.lives = lives;
}

void game_get_lives(void){
  uint8_t value = adc_ir_read();
  // printf("Value 0x%x\r\n", value);
  // Max 0x8b = 162, Min 0x4 = 4,
  uint8_t trigger_value = 0x40;
  if(value < trigger_value ){
    stats.lives--;
    printf("You lost a life! \n\rCurrent lives left: %d", stats.lives);
    if(stats.lives == 0){
      printf("Out of lives\n\r");
      printf("GAME OVER!");
      // CALL SOME KIND OF TERMINATION!!!
    }

    // Continue until the ball is removed
    while(adc_ir_read() < trigger_value);
    _delay_ms(1000);
  }
}
