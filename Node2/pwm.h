#ifndef PWM_H
#define PWM_H
#include <stdio.h>

void pwm_init(void);
void pwm_set_duty_cycle(uint8_t xValue);
// unsigned int TIM16_ReadTCNTn( void );
// void TIM16_WriteTCNTn( unsigned int i );

#endif
