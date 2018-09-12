#include "F_CPU.h"
#include <avr/io.h>
#include <stdlib.h>
#include "joystick.h"
#include "adc.h"

JOY_Y = 4,
JOY_X = 5,
SLIDER_L = 6,
SLIDER_R = 7


JOY_pos joystick_pos(void){
  JOY_pos pos = {.x = adc_read(JOY_X), .y = adc_read(JOY_Y)};
  return pos;
}

SLIDER_pos slider_pos(void){
  SLIDER_pos pos = {.left = adc_read(SLIDER_L), .right = adc_read(SLIDER_R)};
  return pos;
}

BUTTON_pos
