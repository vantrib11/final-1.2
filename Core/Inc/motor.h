/*
 * motor.h
 *
 *  Created on: Sep 21, 2026
 *      Author: OS
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_
#include "main.h"
#define DEADZONE 160
void motor_init(TIM_HandleTypeDef *htimx);
int16_t motor_run(int16_t pwm);

#endif /* INC_MOTOR_H_ */
