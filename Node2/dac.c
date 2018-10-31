#include "DAC.h"
#include "TWI_Master.h"

//Set i2c addresses
#define MAX520_TWI_ADDR_BASE 0b01010000

static uint8_t TWIaddress = 0x00;

void dac_init(){
  TWI_Master_Initialise();
}

void dac_write(){
  uint8_t msg[0] = (MAX520_TWI_ADDR_BASE |  ;

  TWI_Start_Transceiver_With_Data()
}
