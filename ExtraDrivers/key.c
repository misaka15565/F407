#include "key.h"
#include "main.h"
volatile KEY_MSG_t keymsg;

#define KEYs_GPIO_Port KEY1_GPIO_Port
uint16_t KEYs_Pin[KEY_MAX] = {KEY1_Pin, KEY2_Pin, KEY3_Pin};

void KeyIRQHandler() {
    static uint8_t key_time[KEY_MAX] = {0};
    for(uint8_t i=0;i<KEY_MAX;++i){
        if(HAL_GPIO_ReadPin(KEYs_GPIO_Port, KEYs_Pin[i]) == GPIO_PIN_SET){
            key_time[i]++;
            if(key_time[i] > 10){
                keymsg.key = i;
                keymsg.status = KEY_DOWN;
                break;
            }
        }else{
            if(key_time[i] > 10){
                keymsg.key = i;
                keymsg.status = KEY_UP;
            }
            key_time[i] = 0;
        }
    }
}
