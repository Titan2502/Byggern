#ifndef JOYSTICK_H
#define JOYSTICK_H
#include <stdint.h>

typedef struct{
  uint8_t x;
  uint8_t y;
} JOY_pos;

typedef struct{
  uint8_t left;
  uint8_t right;
} SLIDER_pos;

// typedef struct{
//   uint8_t button_left;
//   uint8_t button_right;
// } BUTTON_pos;

typedef enum {
	NEUTRAL,
	UP,
	DOWN,
	RIGHT,
	LEFT,
	UP_RIGHT,
	UP_LEFT,
	DOWN_RIGHT,
	DOWN_LEFT
} JOY_dir_t;

// Declare functions
JOY_pos getJoystickAnalogPos(void);

SLIDER_pos getSliderAnalogPos(void);

JOY_dir_t getJoystickDirection(int deadzone);
//
// SLIDER_pos getSliderPos(float minVal, float maxVal, float scale);
//
// JOY_dir_t getJoystickDirection(int scale, int deadzone);
//
// void calibrateJoystick(void);

#endif
