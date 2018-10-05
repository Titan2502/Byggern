#include <avr/io.h>
#include <stdio.h>

#include "F_CPU.h"
#include "util/delay.h"
#include "MCP2515.h"
#include "spi.h"

void mcp2515_invokeCommand(void){
  //PORTB |= (1<<PB4);
  //_delay_us(1);
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

  // uint8_t adress;
  // mcp2515_read(MCP_CANSTAT);
  // printf("0x%x\r\n",adress);
  // if( (adress & MODE_MASK) != MODE_NORMAL ){
  //     printf("ERROR");
  // }
  return 0;
}


void mcp2515_write(uint8_t address, uint8_t data){
  mcp2515_invokeCommand();
  SPI_MasterTransReceive(MCP_WRITE);
  SPI_MasterTransReceive(address);
  SPI_MasterTransReceive(data);
  mcp2515_deselectSS();
}


void mcp2515_requestToSend(uint8_t rts_port){
  mcp2515_invokeCommand();
  switch(rts_port){
    case 0: SPI_MasterTransReceive(MCP_RTS_TX0); break;
    case 1: SPI_MasterTransReceive(MCP_RTS_TX1); break;
    case 2: SPI_MasterTransReceive(MCP_RTS_TX2); break;
    // Include case for MCP_RTS_ALL ???
    default: break;
  mcp2515_deselectSS();
  }
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
