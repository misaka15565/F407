#include "gt9147.h"
#include "ct_iic.h"
#include "lvgl.h"
#include "main.h"
#include "src/core/lv_group.h"
#include "src/indev/lv_indev.h"
#include "src/misc/lv_types.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "usart.h"
#include "string.h"
#include "lcd.h"
#include <stdbool.h>
// GT9147配置参数表
// 第一个字节为版本号(0X60),必须保证新的版本号大于等于GT9147内部
// flash原有版本号,才会更新配置.
const u8 GT9147_CFG_TBL[] =
    {
        0X60,
        0XE0,
        0X01,
        0X20,
        0X03,
        0X05,
        0X35,
        0X00,
        0X02,
        0X08,
        0X1E,
        0X08,
        0X50,
        0X3C,
        0X0F,
        0X05,
        0X00,
        0X00,
        0XFF,
        0X67,
        0X50,
        0X00,
        0X00,
        0X18,
        0X1A,
        0X1E,
        0X14,
        0X89,
        0X28,
        0X0A,
        0X30,
        0X2E,
        0XBB,
        0X0A,
        0X03,
        0X00,
        0X00,
        0X02,
        0X33,
        0X1D,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X32,
        0X00,
        0X00,
        0X2A,
        0X1C,
        0X5A,
        0X94,
        0XC5,
        0X02,
        0X07,
        0X00,
        0X00,
        0X00,
        0XB5,
        0X1F,
        0X00,
        0X90,
        0X28,
        0X00,
        0X77,
        0X32,
        0X00,
        0X62,
        0X3F,
        0X00,
        0X52,
        0X50,
        0X00,
        0X52,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X0F,
        0X0F,
        0X03,
        0X06,
        0X10,
        0X42,
        0XF8,
        0X0F,
        0X14,
        0X00,
        0X00,
        0X00,
        0X00,
        0X1A,
        0X18,
        0X16,
        0X14,
        0X12,
        0X10,
        0X0E,
        0X0C,
        0X0A,
        0X08,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X29,
        0X28,
        0X24,
        0X22,
        0X20,
        0X1F,
        0X1E,
        0X1D,
        0X0E,
        0X0C,
        0X0A,
        0X08,
        0X06,
        0X05,
        0X04,
        0X02,
        0X00,
        0XFF,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0X00,
        0XFF,
        0XFF,
        0XFF,
        0XFF,
        0XFF,
        0XFF,
        0XFF,
        0XFF,
        0XFF,
        0XFF,
        0XFF,
        0XFF,
        0XFF,
};
// 发送GT9147配置参数
// mode:0,参数不保存到flash
//      1,参数保存到flash

// 触摸屏初始化
// 返回值:0,没有进行校准
//        1,进行过校准
u8 TP_Init(void) {
    if (lcddev.id == 0X5510) // 电容触摸屏
    {
        if (GT9147_Init() == 0) // 是GT9147
        {
            tp_dev.scan = GT9147_Scan; // 扫描函数指向GT9147触摸屏扫描
        }

        tp_dev.touchtype |= 0X80;              // 电容屏
        tp_dev.touchtype |= lcddev.dir & 0X01; // 横屏还是竖屏
        return 0;
    }

    return 1;
}
_m_tp_dev tp_dev =
    {
        TP_Init,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
};

u8 GT9147_Send_Cfg(u8 mode) {
    u8 buf[2];
    u8 i = 0;
    buf[0] = 0;
    buf[1] = mode;                                                            // 是否写入到GT9147 FLASH?  即是否掉电保存
    for (i = 0; i < sizeof(GT9147_CFG_TBL); i++) buf[0] += GT9147_CFG_TBL[i]; // 计算校验和
    buf[0] = (~buf[0]) + 1;
    GT9147_WR_Reg(GT_CFGS_REG, (u8 *)GT9147_CFG_TBL, sizeof(GT9147_CFG_TBL)); // 发送寄存器配置
    GT9147_WR_Reg(GT_CHECK_REG, buf, 2);                                      // 写入校验和,和配置更新标记
    return 0;
}
// 向GT9147写入一次数据
// reg:起始寄存器地址
// buf:数据缓缓存区
// len:写数据长度
// 返回值:0,成功;1,失败.
u8 GT9147_WR_Reg(u16 reg, u8 *buf, u8 len) {
    u8 i;
    u8 ret = 0;
    CT_IIC_Start();
    CT_IIC_Send_Byte(GT_CMD_WR); // 发送写命令
    CT_IIC_Wait_Ack();
    CT_IIC_Send_Byte(reg >> 8); // 发送高8位地址
    CT_IIC_Wait_Ack();
    CT_IIC_Send_Byte(reg & 0XFF); // 发送低8位地址
    CT_IIC_Wait_Ack();
    for (i = 0; i < len; i++) {
        CT_IIC_Send_Byte(buf[i]); // 发数据
        ret = CT_IIC_Wait_Ack();
        if (ret) break;
    }
    CT_IIC_Stop(); // 产生一个停止条件
    return ret;
}
// 从GT9147读出一次数据
// reg:起始寄存器地址
// buf:数据缓缓存区
// len:读数据长度
void GT9147_RD_Reg(u16 reg, u8 *buf, u8 len) {
    u8 i;
    CT_IIC_Start();
    CT_IIC_Send_Byte(GT_CMD_WR); // 发送写命令
    CT_IIC_Wait_Ack();
    CT_IIC_Send_Byte(reg >> 8); // 发送高8位地址
    CT_IIC_Wait_Ack();
    CT_IIC_Send_Byte(reg & 0XFF); // 发送低8位地址
    CT_IIC_Wait_Ack();
    CT_IIC_Start();
    CT_IIC_Send_Byte(GT_CMD_RD); // 发送读命令
    CT_IIC_Wait_Ack();
    for (i = 0; i < len; i++) {
        buf[i] = CT_IIC_Read_Byte(i == (len - 1) ? 0 : 1); // 发数据
    }
    CT_IIC_Stop(); // 产生一个停止条件
}
// 初始化GT9147触摸屏
// 返回值:0,初始化成功;1,初始化失败
// GT_RST    PG15
// GT_INT    PG8
u8 GT9147_Init(void) {
    u8 temp[5];
    RCC->AHB1ENR |= 1 << 6; // 使能PORTG时钟

    GPIO_InitTypeDef GPIO_Initure;
    GPIO_Initure.Pin = GPIO_PIN_15;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOG, &GPIO_Initure); // PG15设置为推挽输出
    GPIO_Initure.Pin = GPIO_PIN_8;
    GPIO_Initure.Mode = GPIO_MODE_INPUT;
    GPIO_Initure.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOG, &GPIO_Initure); // PG8设置为上拉输入

    // GPIO_Set(GPIOG, PIN8,  GPIO_MODE_IN, 0, 0, GPIO_PUPD_PU);	//PG8设置为上拉输入
    // GPIO_Set(GPIOG, PIN15, GPIO_MODE_OUT, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU); //PG15设置为推挽输出

    CT_IIC_Init();                                                     // 初始化电容屏的I2C总线
    HAL_GPIO_WritePin(CTP_RST_GPIO_Port, CTP_RST_Pin, GPIO_PIN_RESET); // 复位
    // GT_RST = 0;				//复位
    HAL_Delay(10);
    HAL_GPIO_WritePin(CTP_RST_GPIO_Port, CTP_RST_Pin, GPIO_PIN_SET); // 释放复位
    // GT_RST = 1;				//释放复位
    HAL_Delay(10);
    GPIO_Initure.Pin = GPIO_PIN_8;
    GPIO_Initure.Mode = GPIO_MODE_INPUT;
    GPIO_Initure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOG, &GPIO_Initure); // PG8设置为浮空输入
    // GPIO_Set(GPIOG, PIN8, GPIO_MODE_IN, 0, 0, GPIO_PUPD_NONE);  //PG8设置为浮空输入
    HAL_Delay(100);
    GT9147_RD_Reg(GT_PID_REG, temp, 4); // 读取产品ID
    temp[4] = 0;
    //	printf("CTP ID:%s\r\n",temp);	//打印ID
    if (strcmp((char *)temp, "9147") == 0) // ID==9147
    {
        temp[0] = 0X02;
        GT9147_WR_Reg(GT_CTRL_REG, temp, 1); // 软复位GT9147
        GT9147_RD_Reg(GT_CFGS_REG, temp, 1); // 读取GT_CFGS_REG寄存器
        if (temp[0] < 0X60)                  // 默认版本比较低,需要更新flash配置
        {
            //			printf("Default Ver:%d\r\n",temp[0]);
            GT9147_Send_Cfg(1); // 更新并保存配置
        }
        HAL_Delay(10);
        temp[0] = 0X00;
        GT9147_WR_Reg(GT_CTRL_REG, temp, 1); // 结束复位
        return 0;
    }
    return 0;
}

const u16 GT9147_TPX_TBL[5] = {GT_TP1_REG, GT_TP2_REG, GT_TP3_REG, GT_TP4_REG, GT_TP5_REG};
// 扫描触摸屏(采用查询方式)
// mode:0,正常扫描.
// 返回值:当前触屏状态.
// 0,触屏无触摸;1,触屏有触摸
u8 GT9147_Scan(u8 mode) {
    u8 buf[4];
    u8 i = 0;
    u8 res = 0;
    u8 temp;
    u8 tempsta;
    GT9147_RD_Reg(GT_GSTID_REG, &mode, 1); // 读取触摸点的状态
    temp = 0;
    GT9147_WR_Reg(GT_GSTID_REG, &temp, 1); // 清标志
    if ((mode & 0XF) && ((mode & 0XF) < 6)) {
        temp = 0XFF << (mode & 0XF); // 将点的个数转换为1的位数,匹配tp_dev.sta定义
        tempsta = tp_dev.sta;        // 保存当前的tp_dev.sta值
        tp_dev.sta = (~temp) | TP_PRES_DOWN | TP_CATH_PRES;
        tp_dev.x[4] = tp_dev.x[0]; // 保存触点0的数据
        tp_dev.y[4] = tp_dev.y[0];
        for (i = 0; i < 5; i++) {
            if (tp_dev.sta & (1 << i)) // 触摸有效?
            {
                GT9147_RD_Reg(GT9147_TPX_TBL[i], buf, 4); // 读取XY坐标值

                if (tp_dev.touchtype & 0X01) // 横屏
                {
                    tp_dev.y[i] = ((u16)buf[1] << 8) + buf[0];
                    tp_dev.x[i] = 800 - (((u16)buf[3] << 8) + buf[2]);
                }

                else {
                    //                        tp_dev.x[i] = ((u16)buf[1] << 8) + buf[0];
                    //                        tp_dev.y[i] = ((u16)buf[3] << 8) + buf[2];

                    tp_dev.x[i] = lcddev.width - (((u16)buf[1] << 8) + buf[0]);
                    tp_dev.y[i] = lcddev.height - (((u16)buf[3] << 8) + buf[2]);
                }
                // printf("x[%d]:%d,y[%d]:%d\r\n",i,tp_dev.x[i],i,tp_dev.y[i]);
            }
        }
        res = 1;
        if (tp_dev.x[0] > lcddev.width || tp_dev.y[0] > lcddev.height) // 非法数据(坐标超出了)
        {
            if ((mode & 0XF) > 1) // 有其他点有数据,则复第二个触点的数据到第一个触点.
            {
                tp_dev.x[0] = tp_dev.x[1];
                tp_dev.y[0] = tp_dev.y[1];

            } else // 非法数据,则忽略此次数据(还原原来的)
            {
                tp_dev.x[0] = tp_dev.x[4];
                tp_dev.y[0] = tp_dev.y[4];
                mode = 0X80;
                tp_dev.sta = tempsta; // 恢复tp_dev.sta
            }
        }
    }

    if ((mode & 0X8F) == 0X80) // 无触摸点按下
    {
        if (tp_dev.sta & TP_PRES_DOWN) // 之前是被按下的
        {
            tp_dev.sta &= ~(1 << 7); // 标记按键松开
        } // 之前就没有被按下
        tp_dev.x[0] = 0xffff;
        tp_dev.y[0] = 0xffff;
        tp_dev.sta &= 0XE0; // 清除点有效标记
    }

    return res;
}

volatile static int32_t touch_last_x;
volatile static int32_t touch_last_y;
volatile static bool data_readed; // 标志本次触摸数据是否已经被lvgl读走
void lvgl_input_torch(lv_indev_t *indev, lv_indev_data_t *data) {
    data->point.x = touch_last_x;
    data->point.y = touch_last_y;
    if (data_readed) {
        // 如果触摸点已经被读过，说明上次读到这次读中间没有发生新的触摸
        data->state = LV_INDEV_STATE_RELEASED;
    } else {
        data->state = LV_INDEV_STATE_PRESSED;
        data_readed = true;
    }
}
static bool key1_pressed = false;
static bool key2_pressed = false;
static bool key3_pressed = false;
static bool key_readed = true;
void lvgl_input_key_cb(lv_indev_t *indev, lv_indev_data_t *data) {
    if (!key_readed) {
        key_readed = true;
        data->state = LV_INDEV_STATE_PRESSED;
        if (key1_pressed) {
            data->enc_diff = -1;
        } else if (key3_pressed) {
            data->enc_diff = 1;
        }

        if(key2_pressed){
            data->state = LV_INDEV_STATE_PRESSED;
        }else{
            data->state = LV_INDEV_STATE_RELEASED;
        }

        key1_pressed = false;
        key2_pressed = false;
        key3_pressed = false;
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance != TIM3)
        return;
    static uint16_t count = 0;
    ++count;
    GT9147_Scan(0);
    // 处理触摸屏事件，如果有触摸，将触摸点给到touch_last_x和touch_last_y，设置readed
    if (tp_dev.sta & TP_PRES_DOWN) {
        touch_last_x = 800 - tp_dev.x[0];
        touch_last_y = 480 - tp_dev.y[0];
        data_readed = false;
    }
    if (count == 10) {
        HAL_GPIO_TogglePin(LED8_GPIO_Port, LED8_Pin);
        count = 0;
    }
    // 检查key123是否按下
    if (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET) {
        if (!key1_pressed) {
            key1_pressed = true;
            key_readed = false;
        }
    } else {
        key1_pressed = false;
    }
    if (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_RESET) {
        if (!key2_pressed) {
            key2_pressed = true;
            key_readed = false;
        }
    } else {
        key2_pressed = false;
    }
    if (HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == GPIO_PIN_RESET) {
        if (!key3_pressed) {
            key3_pressed = true;
            key_readed = false;
        }
    } else {
        key3_pressed = false;
    }
}