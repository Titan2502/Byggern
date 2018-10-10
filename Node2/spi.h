#ifndef SPI_H
#define SPI_H
#include <stdio.h>

void SPI_MasterInit(void);
uint8_t SPI_MasterTransReceive(uint8_t cData);

#endif
