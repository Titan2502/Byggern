#ifndef ACC_MEMORY_TEST
#define ACC_MEMORY_TEST

void SRAM_init(void);
void SRAM_test(void);
void SRAM_writeto(volatile uint8_t *highscores);
void SRAM_readfrom(volatile uint8_t *highscores);

#endif
