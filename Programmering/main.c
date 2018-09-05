#include "F_CPU.h"
#include <avr/io.h>
#include "util/delay.h"
#include "uart.h"
#include "accessing_memory_test.h"

int main()
{
  USART_Init();
  MCUCR |= (1<<SRE);
  SRAM_test();

  while(1){
    // USART_Transmit('G', NULL);
    // printf( "HELLOOOOOOOOOOOOOO\n" );

  }
}
