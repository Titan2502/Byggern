#include <avr/io.h>
#include <stdlib.h>
#include "F_CPU.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#include "TWI_Master.h"
#include "dac.h"
#include "motor.h"
#include "PID_controller.h"

void PID_init_to_winit(uint8_t difficulty, PID_parameters *pid_struct){
  float kp, ki, kd;
  switch (difficulty) {
    case 0:
      kp = 0.022;
      ki = 0.001;
      kd = 0.01;
      break;
    case 1:
      kp = 0.022;
      ki = 0.0;
      kd = 0.0;
      break;
    case 2:
      kp = 0.022;
      ki = 0.001;
      kd = 0.01;
      break;
    default: break;
  }
  PID_init(kp, ki, kd, pid_struct);
  PID_timer_enable();
}


void PID_init(float kp, float ki, float kd, PID_parameters *pid){
    pid->Kp = (kp * SCALING_FACTOR);  // Scaling factor for increased accuracy
    pid->Ki = (ki * SCALING_FACTOR);
    pid->Kd = (kd * SCALING_FACTOR);
    pid->lastMeasurement = 0;
    pid->sumError = 0;                // For integral term
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
  // TCCR1B |= (1<<CS11) | (1<<CS10); // prescaling clk/64 too low samplings for PID
  TIMSK1 |= (1<<TOIE1);   // Overflow Interrupt enable
  TIFR1 &= ~(1<<TOV1);
  sei();
}


int16_t PID_controller(int16_t reference, int16_t measurement, PID_parameters *pid_st){
  int32_t error, p_term, d_term;
  int32_t i_term, temp, correction;

  error = reference - measurement;

  // Calculate P-term and limit error overflow, Pterm: Kp*e
  if (error > pid_st->maxError){
    p_term = MAX_INT32;
  }else if (error < -pid_st->maxError){
    p_term = -MAX_INT32;
  }else{
    p_term = pid_st->Kp * error;
  }

  // Calculate I-term and limit integral "runaway": Iterm: Ki*integral(error)
  temp = pid_st->sumError + error;
  if ( error > -5 && error < 5 ){  // && (temp < -INT32_MAX || temp > INT32_MAX)
    pid_st->sumError = 0;
    temp = 0;
  }

  if(temp > pid_st->maxSumError){
    i_term = MAX_I_TERM;
    pid_st->sumError = pid_st->maxSumError;
  }else if(temp < -pid_st->maxSumError){
    i_term = -MAX_I_TERM;
    pid_st->sumError = -pid_st->maxSumError;
  }else{
    pid_st->sumError = temp;
    i_term = pid_st->Ki * pid_st->sumError;
  }

  // Calculate D-term
  d_term = pid_st->Kd * (pid_st->lastMeasurement - measurement);

  // Collect the terms and divide by the SCALING FACTOR (added for accuracy)
  correction = (p_term + i_term + d_term) / SCALING_FACTOR;

  if(correction > MAX_INT16){
    correction = MAX_INT16;
  }else if(correction < -MAX_INT16){
    correction = -MAX_INT16;
  }
  pid_st->lastMeasurement = measurement;    // Store measurement for next iteration

  return((int16_t)correction);  // Convert it back to int16_t bit
}
