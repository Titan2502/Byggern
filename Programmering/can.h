#ifndef CAN_H
#define CAN_H
#include <stdio.h>

typedef struct{
  int ID;
  uint8_t dataLength;
  uint8_t data[8];
} CAN_msg;

void can_init(void);


#endif
