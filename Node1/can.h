#ifndef CAN_H
#define CAN_H
#include <stdio.h>

typedef struct{
  uint16_t id;
  uint8_t length;
  uint8_t data[8];
} CAN_msg;

void can_init(void);
void can_message_send(CAN_msg* msg);
CAN_msg can_data_receive(void);

#endif
