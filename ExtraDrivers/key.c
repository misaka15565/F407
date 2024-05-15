#include "key.h"
#include "main.h"


#define KEYs_GPIO_Port KEY1_GPIO_Port
uint16_t KEYs_Pin[KEY_MAX] = {KEY1_Pin, KEY2_Pin, KEY3_Pin};

struct KEY_MSG_Queue {
    KEY_MSG_t msg[20];
    uint8_t head;
    uint8_t num;
};
static volatile struct KEY_MSG_Queue key_msg_queue = {};
void KeyQueueInit() {
    key_msg_queue.head = 0;
    key_msg_queue.num = 0;
}
void KeyInQueue(KEY_MSG_t msg) {
    if (key_msg_queue.num < 20) {
        key_msg_queue.msg[(key_msg_queue.head + key_msg_queue.num) % 20] = msg;
        key_msg_queue.num++;
    } else {
        key_msg_queue.msg[key_msg_queue.head] = msg;
        key_msg_queue.head = (key_msg_queue.head + 1) % 20;
    }
}
KEY_MSG_t key_getmsg() {
    KEY_MSG_t msg = key_msg_queue.msg[key_msg_queue.head];
    if (key_msg_queue.num == 0) {
        msg.key = KEY_MAX;
        msg.status = KEY_UP;
        return msg;
    }
    key_msg_queue.head = (key_msg_queue.head + 1) % 20;
    key_msg_queue.num--;
    return msg;
}

void KeyIRQHandler() {
    KEY_MSG_t keymsg;
    static uint8_t key_time[KEY_MAX] = {0};
    for (uint8_t i = 0; i < KEY_MAX; ++i) {
        if (HAL_GPIO_ReadPin(KEYs_GPIO_Port, KEYs_Pin[i]) == GPIO_PIN_RESET) {
            key_time[i]++;
            if (key_time[i] == 10) {
                keymsg.key = i;
                keymsg.status = KEY_DOWN;
                KeyInQueue(keymsg);
            }
        } else {
            if (key_time[i] > 10) {
                keymsg.key = i;
                keymsg.status = KEY_UP;
            }
            key_time[i] = 0;
        }
    }
}
