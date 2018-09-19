#include "F_CPU.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "joystick.h"
#include "adc.h"

volatile uint8_t deadzone = 10; // In percentage

JOY_pos getJoystickAnalogPos(void){
  JOY_pos pos = {.x = adc_read(JOY_X), .y = adc_read(JOY_Y)};
  return pos;
}

SLIDER_pos getSliderAnalogPos(void){
  SLIDER_pos pos = {.left = adc_read(SLIDER_L), .right = adc_read(SLIDER_R)};
  return pos;
}

JOY_dir_t getJoystickDirection(int deadzone){
	JOY_pos pos = getJoystickAnalogPos();
	int maxVal = 255;
	int minVal = 0;
	int centerPos = (maxVal - minVal)/2;
	int maxDeadzone = (centerPos + deadzone);
	int minDeadzone = (centerPos - deadzone);

	// Neutral, UP, DOWN, RIGH, LEFT
	if((pos.y > minDeadzone && pos.y < maxDeadzone) && (pos.x > minDeadzone && pos.x < maxDeadzone))
		{ printf("NEUTRAL\r"); return NEUTRAL; }
	if(pos.y > maxDeadzone && (pos.x > minDeadzone && pos.x < maxDeadzone))
		{ printf("UP\r"); return UP; }
	if(pos.y < minDeadzone && (pos.x > minDeadzone && pos.x < maxDeadzone))
		{ printf("DOWN\r"); return DOWN; }
	if(pos.x > maxDeadzone && (pos.y > minDeadzone && pos.y < maxDeadzone))
		{ printf("RIGHT\r"); return RIGHT; }
	if(pos.x < minDeadzone && (pos.y > minDeadzone && pos.y < maxDeadzone))
		{ printf("LEFT\r"); return LEFT; }

	// Skråposisjoner!
	if(pos.y > maxDeadzone && pos.x > maxDeadzone)
		{ printf("UP-RIGHT\r"); return UP_RIGHT; }
	if(pos.y > maxDeadzone && pos.x < minDeadzone)
		{ printf("UP-LEFT\r"); return UP_LEFT; }
	if(pos.y < minDeadzone && pos.x > maxDeadzone)
		{ printf("DOWN-RIGHT\r"); return DOWN_RIGHT; }
	if(pos.y < minDeadzone && pos.x < minDeadzone)
		{ printf("DOWN-LEFT\r"); return DOWN_LEFT; }
}


// // Calibrate the joystick with --> return the max min values.
// void calibrateJoystick(void){
// 	printf("\n\rStarting Calibration Process...\n\r");
// 	for(int i = 0; i<4; i++){
// 		switch(i){
// 			case 0: printf("\t<<-- Move joystick x-axis between max/min position -->>\n\r"); break;
// 			case 1: printf("\t<<-- Move joystick y-axis between max/min position -->>\n\r"); break;
// 			case 2: printf("\t<<-- Move slider A between max/min position -->>\n\r"); break;
// 			case 3: printf("\t<<-- Move slider B between max/min position -->>\n\r"); break;
// 		}
// 		_delay_ms(2000);
// 		//TO BE CONTINUED
// 	}
// }

// Get the analog position, scale values from 0-100, return result
// Min and max values are calculated from the calibration function
// JOY_pos_out getJoystickPos(float minVal, float maxVal, float scale){
// 	JOY_pos pos = {.x = adc_read(JOY_X), .y = adc_read(JOY_Y)};	// Get the current analog position of the Joystick
// 	printf("Original values: JOY_X: %d JOY_Y: %d\r" , pos.x, pos.y);
// 	// Mapping input from adc in scale
// 	int mappedValueX = mapInput(pos.x, minVal, maxVal, scale);
// 	int mappedValueY = mapInput(pos.y, minVal, maxVal, scale);
//
// 	JOY_pos_out posOut = {.x = mappedValueX - 104, .y = mappedValueY- 104};
//
// 	return posOut;
// }

// SLIDER_pos getSliderPos(float minVal, float maxVal, float scale){
// 	SLIDER_pos pos = {.left = adc_read(SLIDER_L), .right = adc_read(SLIDER_R)};	// Get the current analog position of the slider
//
// 	// Mapping input from adc in scale
// 	// Er det samme deal der som med joystick? left = [0,123], right = [-123,0] ???
// 	mappedValueX = mapInput(pos.x, minVal, maxVal, scale);
// 	mappedValueY = mapInput(pos.y, minVal, maxVal, scale);
//
// 	pos = {pos.x = mappedValueX, pos.y = mappedValueY};
//
// 	return pos;
// }
