#include "F_CPU.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "joystick.h"
#include "adc.h"

volatile uint8_t deadzone = 10; // In percentage
volatile uint8_t maxVal = 255;
volatile uint8_t minVal = 0;

/* JOY_pos getJoystickAnalogPos(void){
  JOY_pos pos = {.x = adc_read(JOY_X), .y = adc_read(JOY_Y)};
  return pos;
}

SLIDER_pos getSliderAnalogPos(void){
  SLIDER_pos pos = {.left = adc_read(SLIDER_L), .right = adc_read(SLIDER_R)};
  return pos;
} */

// Function to map the input from 0-100.
int mapInput(float analogInput, float minVal, float maxVal, float scale){
	// Range of the input
	float range = maxVal - minVal;
	scaledValue = analogInput* (2*scale)/(maxVal-minVal);
	
	// Hvis scaledValue = 0.. ka skjer då????
	
	// Vi vil ha en verdi ut som er mellom [-100, 100]. 
	// Negative scaledValue er positiv X/Y retning: Scale - scaledValue
	if(scaledValue < 0):
		scaledValue = scale + scaledValue;
		
	// Positiv scaledValue er negativ X/Y retning: scaledValue - Scale
	if(scaledValue > 0):
		scaledValue = scaledValue - scale;

	return scaledValue;
}

// Get the analog position, scale values from 0-100, return result
// Min and max values are calculated from the calibration function
JOY_pos getJoystickPos(float minVal, float maxVal, float scale){
	JOY_pos pos = {.x = adc_read(JOY_X), .y = adc_read(JOY_Y)};	// Get the current analog position of the Joystick
	
	// Mapping input from adc in scale
	mappedValueX = mapInput(pos.x, minVal, maxVal, scale);
	mappedValueY = mapInput(pos.y, minVal, maxVal, scale);
	
	pos = {pos.x = mappedValueX, pos.y = mappedValueY};

	return pos
}

SLIDER_pos getSliderPos(float minVal, float maxVal, float scale){
	SLIDER_pos pos = {.left = adc_read(SLIDER_L), .right = adc_read(SLIDER_R)};	// Get the current analog position of the slider
	
	// Mapping input from adc in scale
	// Er det samme deal der som med joystick? left = [0,123], right = [-123,0] ???
	mappedValueX = mapInput(pos.x, minVal, maxVal, scale);
	mappedValueY = mapInput(pos.y, minVal, maxVal, scale);
	
	pos = {pos.x = mappedValueX, pos.y = mappedValueY};

	return pos
}

JOY_dir_t getJoystickDirection(int scale, int deadzone){
	JOY_pos pos = getJoystickPos(minVal, maxVal, scale);
	
	// Neutral, UP, DOWN, RIGH, LEFT
	if((pos.y > -deadzone && pos.y < deadzone) && (pos.x > -deadzone && pos.x < deadzone))
		{ printf("NEUTRAL\r"); return NEUTRAL }
	if(pos.y > deadzone && (pos.x > -deadzone && pos.x < deadzone))
		{ printf("UP\r"); return UP }
	if(pos.y < -deadzone && (pos.x > -deadzone && pos.x < deadzone))
		{ printf("DOWN\r"); return DOWN }	
	if(pos.x > deadzone && (pos.y > -deadzone && pos.y < deadzone))
		{ printf("RIGHT\r"); return RIGHT }	
	if(pos.x < -deadzone && (pos.y > -deadzone && pos.y < deadzone))
		{ printf("LEFT\r"); return LEFT }		
	
	// Skråposisjoner!
	if(pos.y > deadzone && pos.x > deadzone)
		{ printf("UP-RIGHT\r"); return UP_RIGHT }	
	if(pos.y > deadzone && pos.x < -deadzone)
		{ printf("UP-LEFT\r"); return UP_LEFT }
	if(pos.y < -deadzone && pos.x > deadzone)
		{ printf("DOWN-RIGHT\r"); return DOWN_RIGHT }	
	if(pos.y < -deadzone && pos.x < -deadzone)
		{ printf("DOWN-LEFT\r"); return DOWN_LEFT }		
}



// Calibrate the joystick with --> return the max min values.
void calibrateJoystick(void){
	printf("\n\rStarting Calibration Process...\n\r");
	for(int i = 0; i<4; i++){
		switch(i){
			case 0: printf("\t<<-- Move joystick x-axis between max/min position -->>\n\r"); break;
			case 1: printf("\t<<-- Move joystick y-axis between max/min position -->>\n\r"); break;
			case 2: printf("\t<<-- Move slider A between max/min position -->>\n\r"); break;
			case 3: printf("\t<<-- Move slider B between max/min position -->>\n\r"); break;
		}
		_delay_ms(2000);
		//TO BE CONTINUED
	}
}

