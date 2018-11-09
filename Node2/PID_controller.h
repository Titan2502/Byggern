#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H
#include <stdio.h>
#include <stdint.h>

#define SCALING_FACTOR  128 //2^7

// MAx values needed to avoid sign/overflow problems
#define MAX_INT16       32767       // (2¹⁵-1)
#define MAX_INT32       INT32_MAX  // (2³¹-1)
#define MAX_I_TERM      (MAX_INT32 / 2)

typedef struct PID_parameters{
  int32_t Kp;
  int32_t Ki;
  int32_t Kd;
  int32_t lastMeasurement;
  int32_t sumError;
  int32_t maxError;
  int32_t maxSumError;
} PID_parameters;



void PID_init(float kp, float ki, float kd, PID_parameters *pid);
void PID_timer_enable(void);
int16_t PID_controller(int16_t reference, int16_t measurement, PID_parameters *pid_st);
void PID_reset_int(PID_parameters *pid_st);

#endif
