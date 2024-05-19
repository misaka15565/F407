#include "ct_iic.h"
#include "main.h"
#include "stm32f4xx_hal_gpio.h"
// 控制I2C速度的延时
/**
 * @brief 延时 nus
 * * @note 无论是否使用 OS, 都是用时钟摘取法来做 us 延时
 * @param nus: 要延时的 us 数
 * @note nus 取值范围: 0 ~ (2^32 / fac_us) (fac_us 一般等于系统主频, 自行套入计算)
 * @retval 无
 */
void delay_us(uint32_t nus) {
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD; /* LOAD 的值 */
    ticks = nus * 168;               // g_fac_us;          /* 需要的节拍数 */

    told = SysTick->VAL; /* 刚进入时的计数器值 */
    while (1) {
        tnow = SysTick->VAL;
        if (tnow != told) {
            if (tnow < told) {
                tcnt += told - tnow;
                /* 这里注意一下 SYSTICK 是一个递减的计数器就可以了 */
            } else {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks) {
                break; /* 时间超过/等于要延迟的时间,则退出 */
            }
        }
    }
}

void CT_Delay(void) {
    delay_us(2);
}
// 电容触摸芯片IIC接口初始化
void CT_IIC_Init(void) {
    // PB10设置为推挽输出
    // PB15设置为推挽输出
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    // GPIO_Set(GPIOB, PIN10, GPIO_MODE_OUT, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU); // PB10设置为推挽输出
    // GPIO_Set(GPIOB, PIN15, GPIO_MODE_OUT, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU); // PB15设置为推挽输出

    //	GPIO_Set(GPIOF,PIN11,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU); //PF11设置为推挽输出
}
// 产生IIC起始信号
void CT_IIC_Start(void) {
    CT_SDA_OUT();                                                    // sda线输出
    HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, GPIO_PIN_SET); // IIC_SDA = 1;
    HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_SET); // IIC_SCL = 1;
    delay_us(30);
    HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, GPIO_PIN_RESET); // IIC_SDA = 0;
                                                                       // START:when CLK is high,DATA change form high to low
    CT_Delay();
    HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET); // 钳住I2C总线，准备发送或接收数据
}
// 产生IIC停止信号
void CT_IIC_Stop(void) {
    CT_SDA_OUT();                                                    // sda线输出
    HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_SET); // IIC_SCL = 1;
    delay_us(30);
    HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, GPIO_PIN_RESET); // STOP:when CLK is high DATA change form low to high
    CT_Delay();
    HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, GPIO_PIN_SET); // 发送I2C总线结束信号
}
// 等待应答信号到来
// 返回值：1，接收应答失败
//         0，接收应答成功
u8 CT_IIC_Wait_Ack(void) {
    u8 ucErrTime = 0;
    CT_SDA_IN(); // SDA设置为输入
    HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_SET); // IIC_SCL = 1;
    CT_Delay();
    while (CT_READ_SDA) {
        ucErrTime++;
        if (ucErrTime > 250) {
            CT_IIC_Stop();
            return 1;
        }
        CT_Delay();
    }
    HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET); // 时钟输出0
    return 0;
}
// 产生ACK应答
void CT_IIC_Ack(void) {
    HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
    CT_SDA_OUT();
    CT_Delay();
    HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, GPIO_PIN_RESET);
    CT_Delay();
    HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_SET); // IIC_SCL = 1;
    CT_Delay();
    HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
}
// 不产生ACK应答
void CT_IIC_NAck(void) {
    HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
    CT_SDA_OUT();
    CT_Delay();
    HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, GPIO_PIN_SET);
    CT_Delay();
    HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_SET); // IIC_SCL = 1;
    CT_Delay();
    HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
}
// IIC发送一个字节
// 返回从机有无应答
// 1，有应答
// 0，无应答
void CT_IIC_Send_Byte(u8 txd) {
    u8 t;
    CT_SDA_OUT();
    HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET); // 拉低时钟开始数据传输
    CT_Delay();
    for (t = 0; t < 8; t++) {
        HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, (txd & 0x80) >> 7); // CT_IIC_SDA = (txd & 0x80) >> 7;
        txd <<= 1;
        HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_SET); // IIC_SCL = 1;
        CT_Delay();
        HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
        CT_Delay();
    }
}
// 读1个字节，ack=1时，发送ACK，ack=0，发送nACK
u8 CT_IIC_Read_Byte(unsigned char ack) {
    u8 i, receive = 0;
    CT_SDA_IN(); // SDA设置为输入
    delay_us(30);
    for (i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
        CT_Delay();
        HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_SET); // IIC_SCL = 1;
        receive <<= 1;
        if (CT_READ_SDA) receive++;
    }
    if (!ack)
        CT_IIC_NAck(); // 发送nACK
    else
        CT_IIC_Ack(); // 发送ACK
    return receive;
}
