/*
 * pid.h
 *
 *  Created on: Sep 22, 2026
 *      Author: OS
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#include "main.h"
typedef struct
{
    float Kp;
    float Ki;
    float Kd;

    float integral;
    float prev_error;

    float output_min;
    float output_max;

    float dt;

} pid_typedef;
void PID_Init(pid_typedef *pid,
              float Kp,
              float Ki,
              float Kd,
              float dt,
              float output_min,
              float output_max);
float PID_Calculate(pid_typedef *pid,
                    float angle,
                    float setpoint);

#endif /* INC_PID_H_ */
