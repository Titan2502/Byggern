#include <avr/io.h>
#include <stdio.h>

#include "F_CPU.h"
#include "util/delay.h"
#include "MCP2515.h"
#include "spi.h"

void mcp2515_invokeCommand(void){
  PORTB &= ~(1<<PB4);
}


void mcp2515_deselectSS(void){
  PORTB |= (1<<PB4);
}


void mcp2515_reset(void){
  mcp2515_invokeCommand();
  SPI_MasterTransReceive(MCP_RESET);
  mcp2515_deselectSS();
}


uint8_t mcp2515_read(uint8_t address){
  uint8_t result;
  mcp2515_invokeCommand();
  SPI_MasterTransReceive(MCP_READ);
  SPI_MasterTransReceive(address);
  result = SPI_MasterTransReceive(address);
  mcp2515_deselectSS(); // Terminating the read operation
  return result;
}


uint8_t mcp2515_init(void){
  SPI_MasterInit();
  mcp2515_reset();
  _delay_ms(10);
  return 0;
}


void mcp2515_write(uint8_t address, uint8_t data){
  mcp2515_invokeCommand();
  SPI_MasterTransReceive(MCP_WRITE);
  SPI_MasterTransReceive(address);
  SPI_MasterTransReceive(data);
  mcp2515_deselectSS();
}


void mcp2515_requestToSend(uint8_t TXbuffer){
  mcp2515_invokeCommand();
  SPI_MasterTransReceive(TXbuffer);
  mcp2515_deselectSS();
}


uint8_t mcp2515_readStatus(void){
  uint8_t status;
  mcp2515_invokeCommand();
  SPI_MasterTransReceive(MCP_READ_STATUS);
  status = SPI_MasterTransReceive(0x00);
  mcp2515_deselectSS();
  return status;
}


void mcp2515_bitModify(uint8_t address, uint8_t mask, uint8_t data){
  mcp2515_invokeCommand();
  SPI_MasterTransReceive(MCP_BITMOD);
  SPI_MasterTransReceive(address);
  SPI_MasterTransReceive(mask);
  SPI_MasterTransReceive(data);
  mcp2515_deselectSS();
}
