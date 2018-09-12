#ifndef JOYSTICK_H
#define JOYSTICK_H
#include <stdint.h>

typedef struct{
  uint8_t x,
  uint8_t y
} JOY_pos;

typedef struct{
  uint8_t left,
  uint8_t right
} SLIDER_pos;

typedef struct{
  uint8_t button_left,
  uint8_t button_right
} BUTTON_pos;

// Declare functions
JOY_pos
SLIDER_pos
BUTTON_pos

#endif
