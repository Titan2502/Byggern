#include "F_CPU.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "joystick.h"
#include "adc.h"


JOY_pos getJoystickAnalogPos(void){
  JOY_pos pos = {.x = adc_read(JOY_X), .y = adc_read(JOY_Y)};
  return pos;
}

SLIDER_pos getSliderAnalogPos(void){
  SLIDER_pos pos = {.left = adc_read(SLIDER_L), .right = adc_read(SLIDER_R)};
  return pos;
}

void init_button(void){
  DDRB &= ~(1<<PB0);
  PORTB |= (1<<PB0);
}

uint8_t getButton(void){
  uint8_t joyButton = 0x01 & PINB;
  return joyButton;
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
		{return NEUTRAL; }
	if(pos.y > maxDeadzone && (pos.x > minDeadzone && pos.x < maxDeadzone))
		{ return UP; }
	if(pos.y < minDeadzone && (pos.x > minDeadzone && pos.x < maxDeadzone))
		{ return DOWN; }
	if(pos.x > maxDeadzone && (pos.y > minDeadzone && pos.y < maxDeadzone))
		{ return RIGHT; }
	if(pos.x < minDeadzone && (pos.y > minDeadzone && pos.y < maxDeadzone))
		{ return LEFT; }

	// Skråposisjoner!
	if(pos.y > maxDeadzone && pos.x > maxDeadzone)
		{ return UP_RIGHT; }
	if(pos.y > maxDeadzone && pos.x < minDeadzone)
		{ return UP_LEFT; }
	if(pos.y < minDeadzone && pos.x > maxDeadzone)
		{ return DOWN_RIGHT; }
	if(pos.y < minDeadzone && pos.x < minDeadzone)
		{ return DOWN_LEFT; }
}
