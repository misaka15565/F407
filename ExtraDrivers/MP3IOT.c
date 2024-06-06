#include "MP3IOT.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "usart.h"

void mp3_init() {
    uint8_t device[5] = {0x7E, 0x03, 0x35, 0x04, 0xEF};
    uint8_t vol[5] = {0x7e, 0x03, 0x31, 0x1e, 0xef};
    HAL_UART_Transmit(&huart6, device, sizeof(device), 1000);
    HAL_Delay(40);
    HAL_UART_Transmit(&huart6, vol, sizeof(vol), 1000);
    HAL_Delay(40);
}

void mp3_play() {
    uint8_t data1[] = {0x7e, 0x03, 0x07, 0x01, 0xef};
    HAL_UART_Transmit(&huart6, data1, sizeof(data1), 1000);
}

void mp3_stop() {
    uint8_t stop_command[] = {0x7e, 0x03, 0x07, 0x00, 0xef};
    HAL_UART_Transmit(&huart6, stop_command, sizeof(stop_command), 1000);
}