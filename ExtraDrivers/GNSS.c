#include "GNSS.h"
#include "stm32f4xx_hal_uart.h"
#include "usart.h"
#include <stdio.h>

static uint8_t GNSS_RxBuffer[256];
static uint16_t RxPos=0;
void GNSS_Init(){
    HAL_UART_Receive_IT(&huart5, GNSS_RxBuffer+RxPos, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    if(huart->Instance == huart5.Instance){
        if(RxPos==0){
            //以$开头
            if(GNSS_RxBuffer[RxPos] != '$'){
                HAL_UART_Receive_IT(&huart5, GNSS_RxBuffer+RxPos, 1);
                return;
            }
        }
        if(GNSS_RxBuffer[RxPos] == '\n'){
            GNSS_RxBuffer[RxPos] = '\0';
            RxPos = 0;
            //printf("%s\n", GNSS_RxBuffer);
            HAL_UART_Receive_IT(&huart5, GNSS_RxBuffer+RxPos, 1);
        }else{
            RxPos++;
            HAL_UART_Receive_IT(&huart5, GNSS_RxBuffer+RxPos, 1);
        }
    }
}
