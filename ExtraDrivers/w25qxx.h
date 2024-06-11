#ifndef __W25QXX_H
#define __W25QXX_H

#include "main.h"
//  硬件引脚定义
// W25QXX_CS     PB6
#define W25QXX_CS_L HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET)
#define W25QXX_CS_H HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET)

// W25X系列/Q系列芯片列表
// W25Q80  ID  0XEF13
// W25Q16  ID  0XEF14
// W25Q32  ID  0XEF15
// W25Q64  ID  0XEF16
// W25Q128 ID  0XEF17
#define W25Q80 0XEF13
#define W25Q16 0XEF14
#define W25Q32 0XEF15
#define W25Q64 0XEF16
#define W25Q128 0XEF17

extern unsigned short W25QXX_TYPE; // 定义W25QXX芯片型号
extern char W25Qxx_password[256];         // 前六个字符是114514，从第七个开始是密码
//////////////////////////////////////////////////////////////////////////////////
// 指令表
#define W25X_WriteEnable 0x06
#define W25X_WriteDisable 0x04
#define W25X_ReadStatusReg 0x05
#define W25X_WriteStatusReg 0x01
#define W25X_ReadData 0x03
#define W25X_FastReadData 0x0B
#define W25X_FastReadDual 0x3B
#define W25X_PageProgram 0x02
#define W25X_BlockErase 0xD8
#define W25X_SectorErase 0x20
#define W25X_ChipErase 0xC7
#define W25X_PowerDown 0xB9
#define W25X_ReleasePowerDown 0xAB
#define W25X_DeviceID 0xAB
#define W25X_ManufactDeviceID 0x90
#define W25X_JedecDeviceID 0x9F

void W25QXX_Init(void);
unsigned short W25QXX_ReadID(void);     // 读取FLASH ID
unsigned char W25QXX_ReadSR(void);      // 读取状态寄存器
void W25QXX_Write_SR(unsigned char sr); // 写状态寄存器
void W25QXX_Write_Page(unsigned char *pBuffer, unsigned int WriteAddr, unsigned short NumByteToWrite);
void W25QXX_Write_Enable(void);  // 写使能
void W25QXX_Write_Disable(void); // 写保护
void W25QXX_Write_NoCheck(unsigned char *pBuffer, unsigned int WriteAddr, unsigned short NumByteToWrite);
void W25QXX_Read(unsigned char *pBuffer, unsigned int ReadAddr, unsigned short NumByteToRead);    // 读取flash
void W25QXX_Write(unsigned char *pBuffer, unsigned int WriteAddr, unsigned short NumByteToWrite); // 写入flash
void W25QXX_Erase_Chip(void);                                                                     // 整片擦除
void W25QXX_Erase_Sector(unsigned int Dst_Addr);                                                  // 扇区擦除
void W25QXX_Wait_Busy(void);                                                                      // 等待空闲
void W25QXX_PowerDown(void);                                                                      // 进入掉电模式
void W25QXX_WAKEUP(void);                                                                         // 唤醒
void W25Qxx_readPassword();
void W25Qxx_writePassword(const char *passwd);
#endif
