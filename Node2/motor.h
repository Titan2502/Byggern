#ifndef MOTOR_H
#define MOTOR_H
#include <stdio.h>

void motor_init(void);
void motor_reset(void);
void motor_write(uint8_t sliderpos);
uint16_t motor_readEncoder(void);

#endif
