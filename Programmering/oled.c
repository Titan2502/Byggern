#include <avr/io.h>
#include <stdlib.h>
#include "util/delay.h"
#include "F_CPU.h"
#include "fonts.h"

#define OLED_COMMAND_ADDRESS 0x1000
#define OLED_DATA 0x1200
#define DISPLAY_WIDHT 128
#define DISPLAY_HEIGHT 64
#define FONT_WIDTH 8

volatile char *oled_command = (char *) OLED_COMMAND_ADDRESS;
volatile char *oled_data = (char *) OLED_DATA;
volatile uint8_t page, col;

// void oled_reset(void){
// }
// void oled_home(void){
// }
// void oled_goto_line(uint8_t  line){
// 	page = line;
// }
// // void oled_goto_column(uint8_t  column){
// // 	if(column <
// // }
// void oled_clear_line(uint8_t  line){
// }
// void oled_pos(uint8_t  row, uint8_t  column){
// 	oled_goto_line(row);
// 	oled_goto_column(column);
// }
void oled_print_char(char c){
	// Each character have 8*1 byte i fonten LARGE. '5' has the int value 53
	// If we write '0' -' ' it evaluates to 48-32, or the int 16
	for(int i = 0; i < FONT_WIDTH; i++){
		*oled_data = pgm_read_byte(&(font8[c-' '][i]));	// c - ' ' Fordi font begynner på ' ' (Dec = 32)
	}
}
// void oled_print(char *c){
// }

//Initialization routine for the OLED_
void oled_init(void)
{
	printf("Starting OLED Initializing...");
	//Display off
	*oled_command = 0xAE;
	//Segment remap
	*oled_command = 0xA1;
	//Common pads hardware: alternative
	*oled_command = 0xDA;
	*oled_command = 0x12;
	//Common output scan direction:com63~com0
	*oled_command = 0xC8;
	//Multiplex ration mode:63
	*oled_command = 0xA8;
	*oled_command = 0x3F;
	//Display divide ratio/osc. freq. mode
	*oled_command = 0xD5;
	*oled_command = 0x80;
	//Contrast control
	*oled_command = 0x81;
	*oled_command = 0x50;
	//Set pre-charge period
	*oled_command = 0xD9;
	*oled_command = 0x21;
	//Set Memory Addressing Mode
	*oled_command = 0x20;
	*oled_command = 0x02;
	//VCOM deselect level mode
	*oled_command = 0xDB;
	*oled_command = 0x30;
	//Master configuration
	*oled_command = 0xAD;
	*oled_command = 0x00;
	//Out follows RAM content
	*oled_command = 0xA4;
	//Set normal display
	*oled_command = 0xA6;
	//Display on
	*oled_command = 0xAF;
	/* //Set page start address
	*oled_command = 0xB0;
	//Set lower column start address
	*oled_command = 0x00;
	//Set higher column start address
	*oled_command = 0x10;

	//Goto start position
	OLED_ClearScreen();*/
	printf("OLED Initializing Complete!");
}
