#include "F_CPU.h"
#include <avr/io.h>
#include "util/delay.h"
#include "uart.h"
#include "accessing_memory_test.h"

#include <stdlib.h>

int main()
{
  USART_Init();
  MCUCR |= (1<<SRE);


  while(1){
    _delay_ms(2000);
    SRAM_test();
    _delay_ms(2000);
    // USART_Transmit('G', NULL);
    // printf( "HELLOOOOOOOOOOOOOO\n" );
    volatile char *ext_ram = (char *) 0x1500;
    for (uint16_t i = 0; i < 0x200; i++) {
      uint8_t some_value = rand();
      ext_ram[i] = some_value;
      uint8_t retreived_value = ext_ram[i];
      // if (!(i%100)){
      //   printf("Write phase: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
      // }
      }


  }
}
