#ifndef GAME_H
#define GAME_H

typedef struct game_stats{
  uint8_t lives;
} game_stats;

void game_init(uint8_t lives);
uint8_t game_get_lives(void);
void game_solonoid_init(void);
void game_solonoid_check(uint8_t checkbutton);


#endif
