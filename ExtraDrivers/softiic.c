#include "softiic.h"
#include "cmsis_gcc.h"
#include "stm32f4xx_hal_gpio.h"
#include <sys/_types.h>

void SDA_reInit_Input() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = SOFTIIC_SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SOFTIIC_SDA_GPIO_Port, &GPIO_InitStruct);
}

void SDA_reInit_Output() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = SOFTIIC_SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SOFTIIC_SDA_GPIO_Port, &GPIO_InitStruct);
}

static void softI2C_Delay() {
    for (int i = 0; i < 80; i++) {
        __NOP();
    }
}

void softiic_Start() {
    SDA_SET_HIGH;
    SCL_SET_HIGH;
    softI2C_Delay();
    SDA_SET_LOW;
    softI2C_Delay();
    SCL_SET_LOW;
    softI2C_Delay();
}
void softiic_Stop() {
    SCL_SET_HIGH;
    SDA_SET_LOW;
    softI2C_Delay();
    SDA_SET_HIGH;
    softI2C_Delay();
}
void softiic_sendACK(unsigned char ack){
    if(ack==1){
        SDA_SET_HIGH;
    }else{
        SDA_SET_LOW;
    }
    SCL_SET_HIGH;
    softI2C_Delay();
    SCL_SET_LOW;
    softI2C_Delay();
}

void softiic_receiveACK(){
    unsigned char errcnt=20;
    SDA_reInit_Input();
    softI2C_Delay();
    SCL_SET_HIGH;
    softI2C_Delay();
    while(SDA_READ()){
        errcnt--;
        if(errcnt==0){
            softiic_Stop();
        }
    }
    SCL_SET_LOW;
    SDA_reInit_Output();
    softI2C_Delay();
}
void softiic_sendByte(unsigned char data){
    for(int i=0;i<8;++i){
        if(data&0x80){
            SDA_SET_HIGH;
        }else{
            SDA_SET_LOW;
        }
        data<<=1;
        SCL_SET_HIGH;
        softI2C_Delay();
        SCL_SET_LOW;
        softI2C_Delay();
    }
    softiic_receiveACK();
}

unsigned char softiic_receiveByte(){
    unsigned char data=0;
    SDA_reInit_Input();
    for(int i=0;i<8;++i){
        data<<=1;
        SCL_SET_HIGH;
        softI2C_Delay();
        if(SDA_READ()){
            data|=0x01;
        }
        SCL_SET_LOW;
        softI2C_Delay();
    }
    SDA_reInit_Output();
    return data;
}