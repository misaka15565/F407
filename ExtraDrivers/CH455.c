#include "CH455.h"
#include "softiic.h"

const uint8_t BCD_decode_tab[0x10] =
    {0X3F, 0X06, 0X5B, 0X4F,
     0X66, 0X6D, 0X7D, 0X07,
     0X7F, 0X6F, 0X77, 0X7C,
     0X58, 0X5E, 0X79, 0X71}; // BCD

uint8_t ch455_key; // CH455的按键键值

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