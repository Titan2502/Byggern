#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>

#define FOSC 4915200//Clock speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int USART_Transmit( char data, FILE *stream ){
  /* Wait for empty transmit buffer */
  while ( !(UCSR0A & (1<<UDRE0)) );
  /* Put data into buffer, sends the data */
  UDR0 = data;
  return 0;
}

int USART_Receive( FILE *stream ){
  /* Wait for data to be recieved */
  while ( !(UCSR0A & (1<<RXC0)) );
  /* Get and return received data from buffer */
  return UDR0;
}

void USART_Init(){
  /* Set baud rate */
  unsigned int ubrr = MYUBRR;
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, Litt usikker, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
  fdevopen(USART_Transmit, USART_Receive);
}
