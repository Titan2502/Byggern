#ifndef OLED_H
#define OLED_H
#include <stdio.h>

void oled_init(void);
void oled_reset(void);
void oled_home(void);
void oled_goto_page(uint8_t  page);
void oled_goto_column(uint8_t  column);
void oled_clear_page(uint8_t  page);
void oled_pos(uint8_t  page, uint8_t  column);
void oled_clearScreen(void);
void oled_print_char(char c);
void oled_print(char *c);

#endif
