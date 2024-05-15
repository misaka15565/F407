#ifndef SUDOER_KEY_H
#define SUDOER_KEY_H

#include <stdint.h>
typedef enum{
    KEY_S1,
    KEY_S2,
    KEY_S3,
    KEY_MAX
} KEY_e;
// key状态枚举定义
typedef enum {
    KEY_DOWN = 0, // 按键按下时对应电平
    KEY_UP = 1,   // 按键弹起时对应电平

    KEY_HOLD, // 长按按键(用于定时按键扫描)

} KEY_STATUS_e;
// 按键消息结构体
typedef struct
{
    KEY_e key;           // 按键编号
    KEY_STATUS_e status; // 按键状态
} KEY_MSG_t;
extern volatile KEY_MSG_t keymsg;
extern void KeyIRQHandler();

#endif