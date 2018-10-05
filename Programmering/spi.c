#include <avr/io.h>

void SPI_MasterInit(void){
  /* Set MOSI and SCK output, all others input */
  DDRB = (1<<PB5)|(1<<PB6);
  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


char SPI_MasterTransReceive(char cData){
  /* Start transmission */
  SPDR = cData;
  /* Wait for transmission/receive complete */
  while(!(SPSR & (1<<SPIF)))
    ;
  /* Return data register */
  return SPDR;
}
