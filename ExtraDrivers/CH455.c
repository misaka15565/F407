#include "CH455.h"
#include "softiic.h"

const uint8_t BCD_decode_tab[0x10] =
    {0X3F, 0X06, 0X5B, 0X4F,
     0X66, 0X6D, 0X7D, 0X07,
     0X7F, 0X6F, 0X77, 0X7C,
     0X58, 0X5E, 0X79, 0X71}; // BCD

volatile uint8_t ch455_key; // CH455的按键键值

uint8_t Alarm_flag = 0;

void CH455_Write(uint16_t cmd) {
    softiic_Start();
    softiic_sendByte((uint8_t)(cmd >> 7) & CH455_I2C_MASK | CH455_I2C_ADDR);
    softiic_sendByte((uint8_t)cmd);
    softiic_Stop();
}

uint8_t CH455_Read() {
    uint8_t key;
    softiic_Start();
    softiic_sendByte((uint8_t)(CH455_GET_KEY >> 7) & CH455_I2C_MASK | 0x01 | CH455_I2C_ADDR);
    key = softiic_receiveByte();
    softiic_Stop();
    return key;
}
uint8_t CH455_Read_KeyID() {
    uint8_t res = CH455_Read();
    res = res & 0x3f;
    if (res <= 7) {
        res -= 3;
    } else if (12 <= res && res <= 15) {
        res -= 7;
    } else if (20 <= res && res <= 23) {
        res -= 11;
    } else {
        res -= 15;
    }
    return res;
}

void CH455_Show_uint(uint16_t num) {
    uint8_t i;
    uint8_t data[4];
    data[0] = num / 1000;
    data[1] = num % 1000 / 100;
    data[2] = num % 100 / 10;
    data[3] = num % 10;
    for (i = 0; i < 4; i++) {
        CH455_Write((CH455_DIG0 + i * 0x100) | BCD_decode_tab[data[i]]);
    }
}

void CH455_Show_float(float num) {
    uint8_t i;
    uint16_t data[4];
    data[0] = (int)num;
    data[1] = (int)(num * 10) % 10;
    data[2] = (int)(num * 100) % 10;
    data[3] = (int)(num * 1000) % 10;
    for (i = 0; i < 4; i++) {
        CH455_Write((CH455_DIG0 + i * 0x100) | BCD_decode_tab[data[i]] | (i == 0 ? CH455_dot : 0x00));
    }
}