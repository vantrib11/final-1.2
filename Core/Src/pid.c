/*
 * pid.c
 *
 *  Created on: Sep 22, 2026
 *      Author: OS
 */

#include "../../../../will_SUCCESS/DADK_final1.1/Core/Inc/pid.h"


void PID_Init(pid_typedef *pid,
              float Kp,
              float Ki,
              float Kd,
              float dt,
              float output_min,
              float output_max)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;

    pid->dt = dt;

    pid->integral = 0.0f;
    pid->prev_error = 0.0f;

    pid->output_min = output_min;
    pid->output_max = output_max;
}
float PID_Calculate(pid_typedef *pid,
                    float angle,
                    float setpoint)
{
    float error;
    float derivative;
    float output;

    /* Sai số */
    error = setpoint - angle;

    /* Integral */
    pid->integral += error * pid->dt;

    /* Derivative */
    derivative = (error - pid->prev_error) / pid->dt;

    /* PID */
    output = (pid->Kp * error)
           + (pid->Ki * pid->integral)
           + (pid->Kd * derivative);

    /* Giới hạn output */
    if (output > pid->output_max)
    {
        output = pid->output_max;
    }

    if (output < pid->output_min)
    {
        output = pid->output_min;
    }

    pid->prev_error = error;

    return output;
}
