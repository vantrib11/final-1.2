/*
 * debug_uart.h
 *
 *  Created on: Sep 22, 2026
 *      Author: OS
 */

#ifndef INC_DEBUG_UART_H_
#define INC_DEBUG_UART_H_
#include "main.h"
#include <stdint.h>

void LOG_Init(UART_HandleTypeDef *huart);

void LOG_Print(const char *str);

void LOG_Printf(const char *format, ...);

uint8_t LOG_IsBusy(void);
void trans_uart(UART_HandleTypeDef *huart,float var_float);
void toggle_test(void);
#endif /* INC_DEBUG_UART_H_ */
