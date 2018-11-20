#ifndef SRAM_H
#define SRAM_H

#define HIGHSCORES_ADDRESS 0x1800

void SRAM_init(void);
void SRAM_test(void);
void SRAM_writeto(volatile uint8_t *highscores);
void SRAM_read_highscores(uint8_t *highscores);

#endif
