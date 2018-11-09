#ifndef MOTOR_H
#define MOTOR_H
#include <stdio.h>
#include "PID_controller.h"

void motor_init(void);
void motor_reset(void);
void motor_write(int16_t correction);
void motor_PID(uint8_t sliderpos, PID_parameters *pid_st);
int16_t motor_readEncoder(void);

#endif
