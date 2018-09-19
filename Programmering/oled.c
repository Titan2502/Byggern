#include <avr/io.h>
#include <stdlib.h>
#include "util/delay.h"
#include "F_CPU.h"
#include "fonts.h"
#include "oled.h"

#define OLED_COMMAND_ADDRESS 0x1000
#define OLED_DATA 0x1200
#define DISPLAY_WIDHT 128
#define DISPLAY_HEIGHT 64
#define FONT_WIDTH 8

volatile char *oled_command = (char *) OLED_COMMAND_ADDRESS;
volatile char *oled_data = (char *) OLED_DATA;
uint8_t page, col;

void oled_write_command(char addr){
	*oled_command = addr;
}

void oled_write_data(char addr){
	*oled_data = addr;
}

// void oled_reset(void){
// }
void oled_home(void){
	oled_write_command(0x21);
	oled_write_command(0x00);
	oled_write_command(0x7f);
	oled_write_command(0x22);
	oled_write_command(0x00);
	oled_write_command(0x07);

	// page
	oled_write_command(0x00);
	oled_write_command(0x10);
	oled_write_command(0xB0);

}
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
		oled_write_data(0xff);	// c - ' ' Fordi font begynner på ' ' (Dec = 32) pgm_read_byte(&(font8[c-' '][i]))
	}
}

void oled_ClearScreen(void){
	for(int page = 0; page < 8; page++){
		oled_write_command(0xB0 + page);
		for(int i = 0; i < 128; ++i){
			oled_write_command(0x00);
		}
	}
}

// void oled_print(char *c){
// }

//Initialization routine for the OLED_
void oled_init(void)
{
	printf("Starting OLED Initializing...\n\r");
	//Display off
	oled_write_command(0xAE);
	//Segment remap
	oled_write_command(0xA1);
	//Common pads hardware: alternative
	oled_write_command(0xDA);
	oled_write_command(0x12);
	//Common output scan direction:com63~com0
	oled_write_command(0xC8);
	//Multiplex ration mode:63
	oled_write_command(0xA8);
	oled_write_command(0x3F);
	//Display divide ratio/osc. freq. mode
	oled_write_command(0xD5);
	oled_write_command(0x80);
	//Contrast control
	oled_write_command(0x81);
	oled_write_command(0x50);
	//Set pre-charge period
	oled_write_command(0xD9);
	oled_write_command(0x21);
	//Set Memory Addressing Mode
	oled_write_command(0x20);
	oled_write_command(0x02);
	//VCOM deselect level mode
	oled_write_command(0xDB);
	oled_write_command(0x30);
	//Master configuration
	oled_write_command(0xAD);
	oled_write_command(0x00);
	//Out follows RAM content
	oled_write_command(0xA4);
	//Set normal display
	oled_write_command(0xA6);
	//Display on
	oled_write_command(0xAF);
	//Set page start address
	// oled_write_command(0xB0);
	// //Set lower column start address
	//  oled_write_command(0x00);
	// //Set higher column start address
	//  oled_write_command(0x10);

	// //Goto start position
	oled_ClearScreen();
	printf("...OLED Initializing Complete!\n\r");
}
