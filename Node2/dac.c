#include "dac.h"
#include "TWI_Master.h"

//Set i2c addresses
#define MAX520_TWI_ADDR_BASE 0b01010000
#define ENCODER_ADDRESS 0x07
#define MSG_SIZE 3


void dac_init(void){
  TWI_Master_Initialise();
}

void dac_write(uint8_t output_byte){
  uint8_t msg[3] = { MAX520_TWI_ADDR_BASE | (ENCODER_ADDRESS << 1), ENCODER_ADDRESS, output_byte};
  TWI_Start_Transceiver_With_Data(msg, MSG_SIZE);
}
