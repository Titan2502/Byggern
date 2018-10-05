#include <avr/io.h>
#include <stdio.h>

#include "F_CPU.h"
#include "util/delay.h"
#include "MCP2515.h"
#include "spi.h"
#include "can.h"

void can_init(void){
  mcp2515_init();
  bitModify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);  // Switching to loop-back mode
  // bitModify(MCP_RXB0CTRL, 0x60, filteroff??);
  // bitModify(MCP_RXB0CTRL, 0x04, rolloveroff??);
  // bitModify(MCP_CANINTE, 0xff, MCP_NO_INT);
}


void can_sendMessage(CAN_msg dataStruct){
  send_message();
  // SEE p. 15+!
  // full opp registere for sending --> TX registere : ID Datalenght, og data

  // RTS
}


//receive
