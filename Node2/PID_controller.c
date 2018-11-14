#include <avr/io.h>
#include <stdlib.h>
#include "F_CPU.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#include "TWI_Master.h"
#include "dac.h"
#include "motor.h"
#include "PID_controller.h"


void PID_init(float kp, float ki, float kd, PID_parameters *pid){
    pid->Kp = (kp * SCALING_FACTOR);      // Scaling factor for increased accuracy
    pid->Ki = (ki * SCALING_FACTOR);
    pid->Kd = (kd * SCALING_FACTOR);
    pid->lastMeasurement = 0;
    pid->sumError = 0;           // For integral term
    //! Maximum allowed error, avoid overflow
    pid->maxError = MAX_INT32 / (pid->Kp + 1);
    //! Maximum allowed sumerror, avoid overflow
    pid->maxSumError = MAX_I_TERM / (pid->Ki + 1);
}

void PID_timer_enable(void){
  // Normal port opperation (everything is zero)
  cli();
  TCCR1A = 0x00;      // Normal count mode
  TCCR1B |= (1<<CS11);    // prescaling clk/8
  // TCCR1B |= (1<<CS10) | (1<<CS12);    // prescaling clk/1024
  TIMSK1 |= (1<<TOIE1);   // Overflow Interrupt enable
  TIFR1 &= ~(1<<TOV1);
}


int16_t PID_controller(int16_t reference, int16_t measurement, PID_parameters *pid_st){
  int32_t error, p_term, d_term;
  int32_t i_term, temp, correction;

  error = reference - measurement;
  // printf("measurement inside PID: %d\n", measurement);
  // printf("reference inside PID: %d\n", reference);
  // printf("error inside: %d\n", error);

  // Calculate Pterm and limit error overflow, Pterm: Kp*e
  if (error > pid_st->maxError){
    p_term = MAX_INT32;
  }
  else if (error < -pid_st->maxError){
    p_term = -MAX_INT32;
  }
  else{

  }
  p_term = pid_st->Kp * error;

  // Calculate Iterm and limit integral "runaway": Iterm: Ki*integral(error)
  // printf("pid_st->sumError BEFORE PID: %ld\n", pid_st->sumError);
  temp = pid_st->sumError + error;
  // printf("temp inside PID: %ld\n", temp);
  // printf("error inside PID: %ld\n", error);
  // printf("pid_st->sumError inside PID: %ld\n", pid_st->sumError);


  if ( error > -5 && error < 5 ){  // && (temp < -INT32_MAX || temp > INT32_MAX)
    pid_st->sumError = 0;
    temp = 0;
  }

  if(temp > pid_st->maxSumError){
    i_term = MAX_I_TERM;
    pid_st->sumError = pid_st->maxSumError;
  }
  else if(temp < -pid_st->maxSumError){
    i_term = -MAX_I_TERM;
    pid_st->sumError = -pid_st->maxSumError;
  }
  else{
    pid_st->sumError = temp;
    i_term = pid_st->Ki * pid_st->sumError;
  }
  // printf("pid_st->sumError inside PID: %ld\n", pid_st->sumError);
  // printf("i_term inside PID: %ld\n", i_term);
  // Calculate Dterm: Kd*\dot(error)
  d_term = pid_st->Kd * (pid_st->lastMeasurement - measurement);

  // Collect the terms and divide by the SCALING FACTOR (added for accuracy)
  correction = (p_term + i_term + d_term) / SCALING_FACTOR;

  if(correction > MAX_INT16){
    correction = MAX_INT16;
  }
  else if(correction < -MAX_INT16){
    correction = -MAX_INT16;
  }

  pid_st->lastMeasurement = measurement;    // Store measurement for next iteration

  // printf("p_term inside PID: %ld\n", p_term);
  // printf("i_term inside PID: %ld\n", i_term);
  // printf("d_term inside PID: %ld\n", d_term);
  // printf("correction inside PID: %ld\n\n", correction);

  return((int16_t)correction);  // Convert it back to int16_t bit
}


void PID_reset_int(PID_parameters *pid_st){
  pid_st->sumError = 0;
}
