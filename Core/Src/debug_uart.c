/*
 * debug_uart.c
 *
 *  Created on: Sep 22, 2026
 *      Author: OS
 */
#include "debug_uart.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define LOG_BUFFER_SIZE    256

static UART_HandleTypeDef *log_huart = NULL;

static uint8_t log_tx_buffer[LOG_BUFFER_SIZE];

static volatile uint8_t log_busy = 0;


/*
 * Khởi tạo module LOG
 */
void LOG_Init(UART_HandleTypeDef *huart)
{
    log_huart = huart;
    log_busy = 0;
}


/*
 * Kiểm tra UART DMA đang bận hay không
 */
uint8_t LOG_IsBusy(void)
{
    return log_busy;
}


/*
 * Gửi chuỗi bằng UART DMA
 */
void LOG_Print(const char *str)
{
    if (log_huart == NULL)
        return;

    if (log_busy)
        return;

    uint16_t len = strlen(str);

    if (len == 0)
        return;

    if (len >= LOG_BUFFER_SIZE)
        len = LOG_BUFFER_SIZE - 1;

    memcpy(log_tx_buffer, str, len);

    log_busy = 1;

    HAL_UART_Transmit_DMA(
        log_huart,
        log_tx_buffer,
        len
    );
}


/*
 * Gửi chuỗi format giống printf
 *
 * Ví dụ:
 *
 * LOG_Printf("Angle = %.2f\r\n", angle);
 *
 * LOG_Printf("PWM = %d\r\n", pwm);
 */
void LOG_Printf(const char *format, ...)
{
    if (log_huart == NULL || log_busy)
        return;

    va_list args;
    va_start(args, format);

    int len = vsnprintf((char *)log_tx_buffer,
                        LOG_BUFFER_SIZE,
                        format,
                        args);

    va_end(args);

    if (len <= 0)
        return;

    if (len >= LOG_BUFFER_SIZE)
        len = LOG_BUFFER_SIZE - 1;

    log_busy = 1;
    HAL_UART_Transmit_DMA(log_huart, log_tx_buffer, len);
}
//void LOG_Printf(const char *format, ...)
//{
//    if (log_huart == NULL)
//        return;
//
//    if (log_busy)
//        return;
//
//    va_list args;
//
//    va_start(args, format);
//
//    int len = vsnprintf(
//        (char *)log_tx_buffer,
//        LOG_BUFFER_SIZE,
//        format,
//        args
//    );
//
//    va_end(args);
//
//    if (len <= 0)
//        return;
//
//    if (len >= LOG_BUFFER_SIZE)
//        len = LOG_BUFFER_SIZE - 1;
//
//    log_busy = 1;
//
//    HAL_UART_Transmit_DMA(
//        log_huart,
//        log_tx_buffer,
//        len
//    );
//}


/*
 * Callback được HAL gọi khi DMA truyền xong
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == log_huart)
    {
        log_busy = 0;
    }
}

void trans_uart(UART_HandleTypeDef *huart,float var_float)
{
	char buffer1[15];
	snprintf(buffer1,sizeof(buffer1),"gia tri =%.2f\r\n",var_float);
	HAL_UART_Transmit_DMA(huart, (uint8_t*)buffer1, strlen(buffer1));
}

void toggle_test(void)
{
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
}






