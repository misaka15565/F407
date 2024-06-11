#include "GNSS.h"
#include "stm32f4xx_hal_uart.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>


GSVDATA gpgsv;
unsigned char gps_time[50] = "";
float latitude = 0.0;                                               //  纬度
float longitude = 0.0;                                              //  经度
char latitude_dir='N';
char longitude_dir='E';

unsigned char numMsg;	//  语句总数
unsigned char msgNo;	//  当前语句编号
unsigned char numSv;	//  可见卫星总数
unsigned int SVID;		//  卫星编号
unsigned char ele;		//  仰角
unsigned int az;		//  方位角
unsigned char cn0;		//  载噪比

static uint8_t GNSS_RxBuffer[256];
static uint16_t RxPos = 0;
void GNSS_Init() {
    HAL_UART_Receive_IT(&huart5, GNSS_RxBuffer + RxPos, 1);
}
void GNGGA_info(unsigned char *prdata) {
    unsigned char i = 0;
    unsigned char x = 0;
    unsigned char abc = 0;
    unsigned char de = 0;
    unsigned int fghi = 0;
    unsigned char str[20];

    char Disbuf[20] = "";
    unsigned char hour = 0;

    //-------------------------时间部分-----------------------------
    i = 0;
    while (prdata[i++] != ',')
        ; //  寻找时间

    x = 0;
    while (prdata[i] != ',') {
        str[x++] = prdata[i++];
    }
    if (x > 5) {
        hour = (str[0] - '0') * 10 + (str[1] - '0');
        hour += 8;
        Disbuf[0] = hour / 10 + '0';
        Disbuf[1] = hour % 10 + '0';
        Disbuf[2] = ':';
        Disbuf[3] = str[2];
        Disbuf[4] = str[3];
        Disbuf[5] = ':';
        Disbuf[6] = str[4];
        Disbuf[7] = str[5];

        memcpy(gps_time, Disbuf, 8);
    } else {
        Disbuf[0] = '0';
        Disbuf[1] = '0';
        Disbuf[2] = ':';
        Disbuf[3] = '0';
        Disbuf[4] = '0';
        Disbuf[5] = ':';
        Disbuf[6] = '0';
        Disbuf[7] = '0';

        memcpy(gps_time, Disbuf, 5);
    }
    //    printf("T:%s\r\n",time);

    //--------------------------纬度部分----------------------------
    i++;
    x = 0;
    while (prdata[i] != ',') {
        str[x++] = prdata[i++];
    }

    if (x > 5) {
        //  计算纬度
        abc = (str[0] - '0') * 10 + (str[1] - '0');
        de = (str[2] - '0') * 10 + (str[3] - '0');
        fghi = (str[5] - '0') * 1000 + (str[6] - '0') * 100 + (str[7] - '0') * 10 + (str[8] - '0');
        latitude = abc + (de / 60) + (fghi / 600000.0);
    } else {
        latitude = 0;
    }

    //--------------------------------------------------------------
    i++; //  显示纬度
    if (prdata[i] == 'N') {
        latitude_dir = 'N';
        //        printf("N:%.3f\r\n",latitude);
    }

    else {
        latitude_dir = 'S';
        //        printf("S:%.3f\r\n",latitude);
    }

    //--------------------------经度部分----------------------------
    x = 0;
    i = i + 2;
    while (prdata[i] != ',') {
        str[x++] = prdata[i++];
    }

    if (x > 5) {
        //  计算经度
        abc = (str[0] - '0') * 100 + (str[1] - '0') * 10 + (str[2] - '0');
        de = (str[3] - '0') * 10 + (str[4] - '0');
        fghi = (str[6] - '0') * 1000 + (str[7] - '0') * 100 + (str[8] - '0') * 10 + (str[9] - '0');
        longitude = abc + (de / 60) + (fghi / 600000.0);
    } else {
        longitude = 0;
    }

    //  显示经度
    i++;
    if (prdata[i] == 'E') {
        longitude_dir = 'E';
        //        printf("E:%.3f\r\n",longitude);
    } else {
        longitude_dir = 'W';
        //        printf("W:%.3f\r\n",longitude);
    }

    //--------------------------定位部分----------------------------
    i = i + 2; //  显示定位有效值：0/1
    if (prdata[i++] == '0') {
        //	     printf("No location\r\n");              //  未定位
    } else {
        //	     printf("Location\r\n");                 //  定位
    }

    //--------------------------卫星数目----------------------------
    x = 0;
    i = i + 1;
    while (prdata[i] != ',') {
        str[x++] = prdata[i++];
    }

    Disbuf[0] = (str[0] - '0') * 10 + str[1] - '0';

    //	printf("卫星数  %d\r\n", Disbuf[0]);
}

/*********************************************************************************************************
函数名称: void GPGSV_info(unsigned char *prdata)
函数说明：显示信息
输入参数: 接收缓冲区
输出参数:
*********************************************************************************************************/
void GSV_info(unsigned char *prdata) {
    unsigned char i, j, x;
    unsigned char str[20];

    //-------------------------语句总数-----------------------------
    i = 0;
    while (prdata[i++] != ',')
        ;

    x = 0;
    while (prdata[i] != ',') {
        str[x++] = prdata[i++];
    }
    if (x == 1) {
        gpgsv.numMsg = str[0] - '0';
    } else {
        gpgsv.numMsg = 0;
    }

    //--------------------------当前语句编号----------------------------
    i++;
    x = 0;
    while (prdata[i] != ',') {
        str[x++] = prdata[i++];
    }

    if (x == 1) {
        gpgsv.msgNo = str[0] - '0';
    } else {
        gpgsv.msgNo = 0;
    }

    //------------------------可见卫星总数--------------------------------------
    i++; //  显示纬度
    x = 0;
    while (prdata[i] != ',') {
        str[x++] = prdata[i++];
    }

    if (x > 0) {
        gpgsv.numSv = 0;

        for (j = 0; j < x; j++) {
            gpgsv.numSv = gpgsv.numSv * 10 + (str[j] - '0');
        }

        if (gpgsv.numSv == 0) {
            return;
        }
    } else {
        gpgsv.numSv = 0;
    }

    //----------------------------------------------------------------
    //  卫星编号SVID
    //  仰角ele 		0-90  度
    //  方位角az 		0-359 度
    //  载噪比cn0 		0-99  dB-Hz

    //  卫星编号
    i++;
    x = 0;
    while (prdata[i] != ',') {
        str[x++] = prdata[i++];
    }

    if (x > 0) {
        gpgsv.SVID = 0;

        for (j = 0; j < x; j++) {
            gpgsv.SVID = gpgsv.SVID * 10 + (str[j] - '0');
        }
    } else {
        gpgsv.SVID = 0;
    }

    //  仰角ele
    i++;
    x = 0;
    while (prdata[i] != ',') {
        str[x++] = prdata[i++];
    }

    if (x > 0) {
        gpgsv.ele = 0;

        for (j = 0; j < x; j++) {
            gpgsv.ele = gpgsv.ele * 10 + (str[j] - '0');
        }
    } else {
        gpgsv.ele = 0;
    }

    //  方位角az
    i++;
    x = 0;
    while (prdata[i] != ',') {
        str[x++] = prdata[i++];
    }

    if (x > 0) {
        gpgsv.az = 0;

        for (j = 0; j < x; j++) {
            gpgsv.az = gpgsv.az * 10 + (str[j] - '0');
        }
    } else {
        gpgsv.az = 0;
    }

    //  载噪比cn0
    i++;
    x = 0;
    while (prdata[i] != ',') {
        str[x++] = prdata[i++];
    }

    if (x > 0) {
        gpgsv.cn0 = 0;

        for (j = 0; j < x; j++) {
            gpgsv.cn0 = gpgsv.cn0 * 10 + (str[j] - '0');
        }
    } else {
        gpgsv.cn0 = 0;
    }

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == huart5.Instance) {
        if (RxPos == 0) {
            // 以$开头
            if (GNSS_RxBuffer[RxPos] != '$') {
                HAL_UART_Receive_IT(&huart5, GNSS_RxBuffer + RxPos, 1);
                return;
            }
        }
        if (GNSS_RxBuffer[RxPos] == '\n') {
            GNSS_RxBuffer[RxPos] = '\0';
            RxPos = 0;
            // printf("%s\n", GNSS_RxBuffer);
            if(memcmp(GNSS_RxBuffer, "$GNGGA", 6) == 0) {
                GNGGA_info(GNSS_RxBuffer);
            } else if(memcmp(GNSS_RxBuffer, "$GPGSV", 6) == 0) {
                GSV_info(GNSS_RxBuffer);
            }
            HAL_UART_Receive_IT(&huart5, GNSS_RxBuffer + RxPos, 1);
        } else {
            RxPos++;
            HAL_UART_Receive_IT(&huart5, GNSS_RxBuffer + RxPos, 1);
        }
    }
}
