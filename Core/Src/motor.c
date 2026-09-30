/*
 * motor.c
 *
 *  Created on: Sep 21, 2026
 *      Author: OS
 */
#include "motor.h"
void motor_init(TIM_HandleTypeDef *htimx)
{
	HAL_TIM_PWM_Start(htimx, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(htimx, TIM_CHANNEL_2);
}
int16_t motor_run(int16_t pwm)
{
	if(pwm > 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 1);
		pwm = pwm + DEADZONE;
		if(pwm >=2000)pwm =2000;
		if(pwm <=0   )pwm = 0  ;
		TIM2->CCR1 = pwm;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		TIM2->CCR2 = pwm;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
	}
	if(pwm < 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 0);
		pwm = -pwm;
		pwm = pwm + DEADZONE;
		if(pwm >=2000)pwm =2000;
		if(pwm <=0   )pwm = 0  ;
		TIM2->CCR1 = pwm;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		TIM2->CCR2 = pwm;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
	}
	return TIM2->CCR1;
}
