#include "WIFI.h"
#include "LCD.h"
#include "main.h"
#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_uart.h"
#include "usart.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
uint8_t id=0;
static uint8_t wifi_buffer[16]={};
static uint16_t wifi_buffer_pos=0;
unsigned char mode;
unsigned char AT_ack;
void WIFI_Configuration() {
    HAL_UART_Receive_IT(&huart5, wifi_buffer+wifi_buffer_pos, 1);//要求串口中断接收一个字符
    unsigned char CWMODE[13] = "AT+CWMODE=2\r\n";
    unsigned char CWSAP[38] = "AT+CWSAP=\"PSE826\",\"0123456789\",11,0\r\n";
    unsigned char CIPMUX[13] = "AT+CIPMUX=1\r\n";
    unsigned char CIPSERVER[21] = "AT+CIPSERVER=1,5000\r\n";
    HAL_UART_Transmit(&huart5, CWMODE, sizeof(CWMODE), 0xffff);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart5, CWSAP, sizeof(CWSAP), 0xffff);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart5, CIPMUX, sizeof(CIPMUX), 0xffff);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart5, CIPSERVER, sizeof(CIPSERVER), 0xffff);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart5, "ATE1",4, 0xffff);
    HAL_Delay(1000);
    
}
static void UART5_Senddata(uint8_t* data,int len){
    HAL_UART_Transmit(&huart5, data, len, 0xffff);
}

#define SSID   "SudoerK50"                            //  WIFI名称
#define PASS   "1234567a"                       //  WIFI密码
//#define SSID   "RD_2.4G"                     //路由器SSID名称
//#define PASS   "17612290442"                 //路由器密码

#define SERVER_IP      "192.168.1.100"                  //  IP地址10.69.35.203
#define SERVER_PORT   5000                           //  端口号

void WIFI_Config2(){
    unsigned char CWMODE[13]    = "AT+CWMODE=1\r\n";                            //  选择 WIFI 应用模式 1:Station模式 2:AP模式 3:AP兼Station模式
    char CWJAP[50];     //  加入 AP
    unsigned char CIPSERVER[16] = "AT+CIPSERVER=0\r\n";                         //  关闭 server 模式
    unsigned char CIPMUX[13]    = "AT+CIPMUX=0\r\n";                            //  启动多连接 0:单路连接模式 1：多路连接模式
    char CIPSTART[50];   //  建立 TCP 连接或注册 UDP 端口号
    
    sprintf(CWJAP,"AT+CWJAP=\"%s\",\"%s\"\r\n",SSID,PASS);
    sprintf(CIPSTART, "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", SERVER_IP, SERVER_PORT);
    //  AT+CWMODE = 1，开启STA模式
    UART5_Senddata(CWMODE, sizeof(CWMODE));

  
    printf("正在连接wifi...\r\n");
    
    //  连接WIFI
	do {
        UART5_Senddata((void*)CWJAP, strlen(CWJAP));
        if (AT_ack == 0)
        {
            printf("连接WIFI成功\r\n");
        }
        else
        {
            printf("连接WIFI失败\r\n");
        }

    }
    while (AT_ack != 0);
    
    printf("连接WIFI成功\r\n");

    //	关闭 server 模式
	UART5_Senddata(CIPSERVER, sizeof(CIPSERVER));

    //	设置单连接
	UART5_Senddata(CIPMUX, sizeof(CIPMUX));

    
    //  建立TCP连接
    UART5_Senddata((void*)CIPSTART, strlen(CIPSTART));


    mode = 1;
    
}

void WIFI_Send(unsigned char *ptr, unsigned int length) {
    char CIPSEND[100] = "";
    sprintf(CIPSEND, "AT+CIPSEND=%d,%d\r\n", id, length);
    HAL_UART_Transmit(&huart5, CIPSEND, strlen(CIPSEND), 0xffff);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart5, ptr, length, 0xffff);
    HAL_Delay(100);
}

//倒数第几个字符
#define str(x) (wifi_buffer[(wifi_buffer_pos+sizeof(wifi_buffer)-x)%sizeof(wifi_buffer)])

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    return;
    if(huart!=&huart5)return;
    
    wifi_buffer_pos=(wifi_buffer_pos+1)%sizeof(wifi_buffer);//循环接收
    HAL_GPIO_TogglePin(GPIOF, LED1_Pin);
    LCD_ShowString(0,32,wifi_buffer,BLACK,WHITE);
    for(int i=0;i<sizeof(wifi_buffer);++i){
        if(str(-i)=='N'){
            HAL_GPIO_WritePin(GPIOF, (1 << 8) - 1, GPIO_PIN_RESET);
            break;
        }else if(str(-i)=='F'){
            HAL_GPIO_WritePin(GPIOF, (1 << 8) - 1, GPIO_PIN_RESET);
            break;
        }
    }
    HAL_UART_Receive_IT(&huart5, wifi_buffer+wifi_buffer_pos, 1);
}

