#ifndef SOFTIIC_H
#define SOFTIIC_H
#include "main.h"
#define SDA_SET_HIGH HAL_GPIO_WritePin(SOFTIIC_SDA_GPIO_Port, SOFTIIC_SDA_Pin, GPIO_PIN_SET)
#define SDA_SET_LOW HAL_GPIO_WritePin(SOFTIIC_SDA_GPIO_Port, SOFTIIC_SDA_Pin, GPIO_PIN_RESET)
#define SCL_SET_HIGH HAL_GPIO_WritePin(SOFTIIC_SCL_GPIO_Port, SOFTIIC_SCL_Pin, GPIO_PIN_SET)
#define SCL_SET_LOW HAL_GPIO_WritePin(SOFTIIC_SCL_GPIO_Port, SOFTIIC_SCL_Pin, GPIO_PIN_RESET)
#define SDA_READ() HAL_GPIO_ReadPin(SOFTIIC_SDA_GPIO_Port, SOFTIIC_SDA_Pin)
void SDA_reInit_Input(void);
void SDA_reInit_Output(void);
void softiic_Start(void);
void softiic_Stop(void);
void softiic_sendACK(unsigned char ack);
void softiic_receiveACK(void);
void softiic_sendByte(unsigned char data);
unsigned char softiic_receiveByte(void);
#endif
