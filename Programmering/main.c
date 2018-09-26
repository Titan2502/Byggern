#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "F_CPU.h"
#include <avr/sleep.h>
#include "util/delay.h"

// Include headerfiles
#include "uart.h"
#include "accessing_memory_test.h"
#include "adc.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"

// Definitions


int main()
{
  USART_Init();
  MCUCR |= (1<<SRE);
  // SFIOR |= (1<<XMM2): // Release PC7-PC4 for normal Port Pin function.
  SRAM_test();  // Reading and writing to the SRAM
  char c = 'p';
  char str[] = "ab";
  char *pointer = &str[0];
  oled_init();
  oled_clearScreen();


  initMenu();


  while(1){
    _delay_ms(500);
    oled_print(pointer);


    //-----------JOYSTICK/SLIDER READ AND PRINT DATA-----------
    // JOY_pos posJoy = getJoystickAnalogPos();
    // SLIDER_pos posSlider = getSliderAnalogPos();
    // printf("JOY_X: %d JOY_Y: %d\r" , posJoy.x, posJoy.y);
    // printf("SLIDER_L: %d SLIDER_R: %d\r" , posSlider.left, posSlider.right);
    // printf("JOYSTICK POSITION: ");
    // getJoystickDirection(10);


    // printf("SLIDER_L: %d SLIDER_R: %d\r" , adc_read(SLIDER_L), adc_read(SLIDER_R));

    // // USART_Transmit('G', NULL);
    // // printf( "HELLOOOOOOOOOOOOOO\n" );
    // printf("ADC test...\n\r");
    // volatile char *ext_ram = (char *) 0x1500;
    // for (uint16_t i = 0; i < 0x200; i++) {
    //   uint8_t some_value = rand();
    //   ext_ram[i] = some_value;
    //   uint8_t retreived_value = ext_ram[i];
    //   // if (!(i%100)){
    //   //   printf("Write phase: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
    //   // }
    // }


  }
}
