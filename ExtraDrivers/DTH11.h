#ifndef __DHT11_H
#define __DHT11_H
#include "stm32f4xx.h"

// DHT11_PIN         PE6
#define DHT11_L HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET)
#define DHT11_H HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET)

#define DHT11_READ() HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6)

void DTH11_OUT(void);
void DTH11_IN(void);
void DTH11_Delay(unsigned int j);
void Delay_10us(void);
unsigned char DTH11_ReadByte(void);
void DTH11_ReadData(unsigned char *temp, unsigned char *humi);

#endif
