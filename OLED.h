#ifndef OLED_H
#define OLED_H

#include "mcu_compat.h"

#define OLED_ADDRESS 0x78 // OLED I2C地址
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_GND P2_2 // 定义OLED的GND连接到P2.2
#define OLED_VCC P2_3 // 定义OLED的VCC连接到P2.3
#define OLED_SCL P2_1 // 定义OLED的SCL连接到P2.1
#define OLED_SDA P2_0 // 定义OLED的SDA连接到P2.0

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(unsigned char Line, unsigned char Column, char Char);
void OLED_ShowString(unsigned char Line, unsigned char Column, char *String);
void OLED_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length);
void OLED_ShowSignedNum(unsigned char Line, unsigned char Column, int Number, unsigned char Length);
void OLED_ShowFloat(unsigned char Line, unsigned char Column, float Number, unsigned char FLen);
void OLED_I2C_SendByte(unsigned char byte);
void OLED_ShowBlock(unsigned char Line, unsigned char Column);
void OLED_WriteDataBuffer(const unsigned char xdata *Data, unsigned char Length);

/* 低级绘图接口（用于简单绘图刷新） */
void OLED_SetCursor(unsigned char Y, unsigned char X);
void OLED_WriteData(unsigned char Data);

#endif // OLED_H
