#ifndef PWM_H
#define PWM_H
#include <stdio.h>

unsigned int TIM16_ReadTCNTn( void );
void TIM16_WriteTCNTn( unsigned int i );

#endif
