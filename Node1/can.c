#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "F_CPU.h"
#include "util/delay.h"
#include "MCP2515.h"
#include "spi.h"
#include "can.h"


void can_init(void){
  mcp2515_init();
  mcp2515_bitModify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);  // Switching to loop-back mode
  mcp2515_bitModify(MCP_CANINTE, 0x03, MCP_RX_INT);
  // bitModify(MCP_RXB0CTRL, 0x60, filteroff??);
  // bitModify(MCP_RXB0CTRL, 0x04, rolloveroff??);
}


void can_message_send(CAN_msg* msg){
  mcp2515_bitModify(MCP_TXB0SIDH, 0xFF, (msg->id >> 3));   // Fill the ID register TXBnSIDH
  mcp2515_bitModify(MCP_TXB0SIDL, 0xFF, msg->id << 5);
  mcp2515_bitModify(MCP_TXB0DLC, 0x0F, msg->length);   // Fill the Data Length register TXBnDLC
  for(uint8_t i=0; i < msg->length; i++){
    mcp2515_bitModify(MCP_TXB0D0+i, 0xFF, msg->data[i]);
  }
  mcp2515_requestToSend(MCP_RTS_TX0);
}


CAN_msg can_data_receive(void){
  CAN_msg msg;
  uint8_t status;
  status = mcp2515_read(MCP_CANINTF);

  // Buffer register 0
  if( (status & MCP_RX0IF) ){
    msg.id = (mcp2515_read(MCP_RXB0SIDH) << 3) | (mcp2515_read(MCP_RXB0SIDL) >>5);
    msg.length = (mcp2515_read(MCP_RXB0DLC) & 0x0F);
    for(uint8_t i=0; i < msg.length; i++){
      msg.data[i] = mcp2515_read(MCP_RXB0D0 + i);
    }
    mcp2515_bitModify(MCP_CANINTF, MCP_RX0IF, MCP_NO_INT);
  }


  // Buffer register 1
  else if( (status & MCP_RX1IF) ){
    msg.id = (mcp2515_read(MCP_RXB1SIDH) << 3) | (mcp2515_read(MCP_RXB1SIDL) >>5);
    msg.length = (mcp2515_read(MCP_RXB1DLC) & 0x0F);
    for(uint8_t i=0; i < msg.length; i++){
      msg.data[i] = mcp2515_read(MCP_RXB1D0 + i);
    }
    mcp2515_bitModify(MCP_CANINTF, MCP_RX1IF, MCP_NO_INT);
  }


  return msg;
}



ISR(INT0_vect){
  CAN_msg msg;
  msg = can_data_receive();
  printf("%d\n", msg.id);
}
