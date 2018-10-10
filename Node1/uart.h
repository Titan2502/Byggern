#ifndef UART_H
#define UART_H

#include <stdio.h>

void USART_Init();
int USART_Transmit( char data, FILE * );
int USART_Receive( FILE * );

#endif
