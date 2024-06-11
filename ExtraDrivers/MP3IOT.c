#include "MP3IOT.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "usart.h"

void mp3_init() {
    mp3_stop();
    HAL_Delay(40);
    uint8_t device[5] = {0x7E, 0x03, 0x35, 0x04, 0xEF};
    uint8_t vol[5] = {0x7e, 0x03, 0x31, 0x01, 0xef};
    HAL_UART_Transmit(&huart6, device, sizeof(device), 1000);
    HAL_Delay(40);
    HAL_UART_Transmit(&huart6, vol, sizeof(vol), 1000);
    HAL_Delay(40);
}

void mp3_play() {
    uint8_t data1[] = {0x7e, 0x04, 0x4c, 0x00, 0x0f, 0xef};
    HAL_UART_Transmit(&huart6, data1, sizeof(data1), 1000);
}

void mp3_stop() {
    uint8_t stop_command[] = {0x7e, 0x02, 0x02, 0xef};
    HAL_UART_Transmit(&huart6, stop_command, sizeof(stop_command), 1000);
}

void mp3_changevol(uint8_t vol){
    uint8_t vol_command[5] = {0x7e, 0x03, 0x31, 0x01, 0xef};
    if(vol>30)vol=30;
    vol_command[3]=vol;
    HAL_UART_Transmit(&huart6, vol_command, sizeof(vol_command), 1000);
}