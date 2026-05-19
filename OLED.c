#include "mcu_compat.h"
#include <stdio.h>
#include "OLED.h"
#include "OLED_Font.h"

#define OLED_ADDRESS 0x78 // OLED I2C地址
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

static unsigned char OLED_I2CAddr = OLED_ADDRESS;

static void OLED_I2C_Start(void)
{
    OLED_SDA = 1;
    OLED_SCL = 1;
    OLED_SDA = 0;
    OLED_SCL = 0;
}

static void OLED_I2C_Stop(void)
{
    OLED_SDA = 0;
    OLED_SCL = 1;
    OLED_SDA = 1;
}

static unsigned char OLED_I2C_SendByteAck(unsigned char byte)
{
    unsigned char i;
    unsigned char ack;
    for (i = 0; i < 8; i++) {
        OLED_SDA = (byte & 0x80) ? 1 : 0;
        byte <<= 1;
        OLED_SCL = 1;
        OLED_SCL = 0;
    }
    OLED_SDA = 1;
    OLED_SCL = 1;
    ack = OLED_SDA;
    OLED_SCL = 0;
    return ack;
}

void OLED_I2C_SendByte(unsigned char byte)
{
    (void)OLED_I2C_SendByteAck(byte);
}

static void OLED_DelayMs(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++) {
            ;
        }
    }
}

static unsigned char OLED_WriteCommandAck(unsigned char command)
{
    unsigned char ok = 0;
    OLED_I2C_Start();
    ok = (OLED_I2C_SendByteAck(OLED_I2CAddr) == 0);
    if (ok) {
        ok = (OLED_I2C_SendByteAck(0x00) == 0);
    }
    if (ok) {
        ok = (OLED_I2C_SendByteAck(command) == 0);
    }
    OLED_I2C_Stop();
    return ok;
}

static unsigned char OLED_WriteDataAck(unsigned char dataByte)
{
    unsigned char ok = 0;
    OLED_I2C_Start();
    ok = (OLED_I2C_SendByteAck(OLED_I2CAddr) == 0);
    if (ok) {
        ok = (OLED_I2C_SendByteAck(0x40) == 0);
    }
    if (ok) {
        ok = (OLED_I2C_SendByteAck(dataByte) == 0);
    }
    OLED_I2C_Stop();
    return ok;
}

static unsigned char OLED_DetectAddress(void)
{
    OLED_I2CAddr = 0x78;
    if (OLED_WriteCommandAck(0xAE)) {
        return 1;
    }

    OLED_I2CAddr = 0x7A;
    if (OLED_WriteCommandAck(0xAE)) {
        return 1;
    }

    OLED_I2CAddr = OLED_ADDRESS;
    return 0;
}

void OLED_WriteCommand(unsigned char command)
{
    OLED_I2C_Start();
    OLED_I2C_SendByte(OLED_I2CAddr);
    OLED_I2C_SendByte(0x00);
    OLED_I2C_SendByte(command);
    OLED_I2C_Stop();
}

void OLED_WriteData(unsigned char Data)
{
    OLED_I2C_Start();
    OLED_I2C_SendByte(OLED_I2CAddr);
    OLED_I2C_SendByte(0x40);
    OLED_I2C_SendByte(Data);
    OLED_I2C_Stop();
}

void OLED_WriteDataBuffer(const unsigned char xdata *Data, unsigned char Length)
{
    unsigned char i;

    OLED_I2C_Start();
    OLED_I2C_SendByte(OLED_I2CAddr);
    OLED_I2C_SendByte(0x40);
    for (i = 0; i < Length; i++) {
        OLED_I2C_SendByte(Data[i]);
    }
    OLED_I2C_Stop();
}

/**
 * @brief  OLED设置光标位置
 * @param  Y 以页为单位，范围：1~8
 * @param  X 以列为单位，范围：1~128
 * @retval 无
 */
void OLED_SetCursor(unsigned char Y, unsigned char X)
{
    OLED_WriteCommand(0xB0 + (Y - 1));                 // 设置页地址
    OLED_WriteCommand(0x10 | (((X - 1) & 0xF0) >> 4)); // 设置列地址高4位
    OLED_WriteCommand(0x00 | ((X - 1) & 0x0F));        // 设置列地址低4位
}

void OLED_Init()
{
    OLED_DelayMs(100); // 等待上电稳定
    (void)OLED_DetectAddress();

    OLED_WriteCommand(0xAE); // 关闭显示
    OLED_WriteCommand(0xD5); // 设置时钟分频比/振荡器频率
    OLED_WriteCommand(0x80);
    OLED_WriteCommand(0xA8); // 设置多重复用率
    OLED_WriteCommand(0x3F);
    OLED_WriteCommand(0xD3); // 设置显示偏移
    OLED_WriteCommand(0x00);
    OLED_WriteCommand(0x40); // 设置起始行
    OLED_WriteCommand(0x8D); // 使能电荷泵
    OLED_WriteCommand(0x14);
    OLED_WriteCommand(0x20); // 设置内存寻址模式
    OLED_WriteCommand(0x02); // 页寻址模式（SSD1306最稳定模式）
    OLED_WriteCommand(0xA1); // 段重映射
    OLED_WriteCommand(0xC8); // COM 扫描方向
    OLED_WriteCommand(0xDA); // COM 引脚配置
    OLED_WriteCommand(0x12);
    OLED_WriteCommand(0x81); // 对比度
    OLED_WriteCommand(0xCF);
    OLED_WriteCommand(0xD9); // 预充电周期
    OLED_WriteCommand(0xF1);
    OLED_WriteCommand(0xDB); // VCOMH 去选择电平
    OLED_WriteCommand(0x30);
    OLED_WriteCommand(0xA4); // 使用 RAM 内容显示
    OLED_WriteCommand(0xA6); // 正常显示
    OLED_WriteCommand(0x2E); // 关闭滚动
    OLED_Clear();
    OLED_WriteCommand(0xAF); // 打开显示
}

void OLED_Clear()
{
    unsigned char i, j;
    for (i = 0; i < 8; i++) {
        OLED_SetCursor(i + 1, 1);
        OLED_I2C_Start();
        OLED_I2C_SendByte(OLED_I2CAddr);
        OLED_I2C_SendByte(0x40);
        for (j = 0; j < 128; j++) {
            OLED_I2C_SendByte(0x00);
        }
        OLED_I2C_Stop();
    }
}

/**
 * @brief  OLED显示一个字符
 * @param  Line 行位置，范围：1~4 (针对8x16字体)
 * @param  Column 列位置，范围：1~16
 * @param  Char 要显示的一个字符，范围：ASCII可见字符
 * @retval 无
 */
void OLED_ShowChar(unsigned char Line, unsigned char Column, char Char)
{
    unsigned char i;
    OLED_SetCursor((Line * 2) - 1, (Column - 1) * 8 + 1);
    OLED_I2C_Start();
    OLED_I2C_SendByte(OLED_I2CAddr);
    OLED_I2C_SendByte(0x40);
    for (i = 0; i < 8; i++) {
        OLED_I2C_SendByte(OLED_F8x16[Char - ' '][i]);
    }
    OLED_I2C_Stop();

    OLED_SetCursor(Line * 2, (Column - 1) * 8 + 1);
    OLED_I2C_Start();
    OLED_I2C_SendByte(OLED_I2CAddr);
    OLED_I2C_SendByte(0x40);
    for (i = 8; i < 16; i++) {
        OLED_I2C_SendByte(OLED_F8x16[Char - ' '][i]);
    }
    OLED_I2C_Stop();
}

void OLED_ShowBlock(unsigned char Line, unsigned char Column)
{
    OLED_SetCursor((Line * 2) - 1, (Column - 1) * 8 + 1);
    OLED_I2C_Start();
    OLED_I2C_SendByte(OLED_I2CAddr);
    OLED_I2C_SendByte(0x40);
    OLED_I2C_SendByte(0x01);

    OLED_I2C_Stop();
}

void OLED_ShowString(unsigned char Line, unsigned char Column, char *String)
{
    unsigned char i, j;
    unsigned char code *p;

    OLED_SetCursor((Line * 2) - 1, (Column - 1) * 8 + 1);
    OLED_I2C_Start();
    OLED_I2C_SendByte(OLED_I2CAddr);
    OLED_I2C_SendByte(0x40);
    for (i = 0; String[i] != '\0'; i++) {
        p = OLED_F8x16[String[i] - ' '];
        for (j = 0; j < 8; j++) {
            OLED_I2C_SendByte(p[j]);
        }
    }
    OLED_I2C_Stop();

    OLED_SetCursor(Line * 2, (Column - 1) * 8 + 1);
    OLED_I2C_Start();
    OLED_I2C_SendByte(OLED_I2CAddr);
    OLED_I2C_SendByte(0x40);
    for (i = 0; String[i] != '\0'; i++) {
        p = OLED_F8x16[String[i] - ' '];
        for (j = 8; j < 16; j++) {
            OLED_I2C_SendByte(p[j]);
        }
    }
    OLED_I2C_Stop();
}

static unsigned int OLED_Pow(unsigned char m, unsigned char n)
{
    unsigned int result = 1;
    while (n--) {
        result *= m;
    }
    return result;
}

/**
 * @brief  OLED显示数字（十进制，无符号）
 * @param  Line 起始行位置，范围：1~4
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：0~65535
 * @param  Length 要显示数字的长度，范围：1~5
 * @retval 无
 */
void OLED_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
    unsigned char i;
    for (i = 0; i < Length; i++) {
        OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
    }
}

/**
 * @brief  OLED显示数字（十进制，有符号）
 * @param  Line 起始行位置，范围：1~4
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：-32768~32767
 * @param  Length 要显示数字的长度，范围：1~5
 * @retval 无
 */
void OLED_ShowSignedNum(unsigned char Line, unsigned char Column, int Number, unsigned char Length)
{
    unsigned char i;
    unsigned int Number1;
    if (Number >= 0) {
        OLED_ShowChar(Line, Column, '+');
        Number1 = Number;
    }
    else {
        OLED_ShowChar(Line, Column, '-');
        Number1 = -Number;
    }
    for (i = 0; i < Length; i++) {
        OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
    }
}

/**
 * @brief  OLED显示浮点数
 * @param  Line 起始行位置，范围：1~4
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的浮点数
 * @param  FLen 小数点后的显示长度
 * @retval 无
 */
void OLED_ShowFloat(unsigned char Line, unsigned char Column, float Number, unsigned char FLen)
{
    unsigned int n = 0;
    float temp = Number;
    if (temp >= 0) {
        OLED_ShowChar(Line, Column, '+');
    }
    else {
        OLED_ShowChar(Line, Column, '-');
        temp = -temp;
    }

    if (temp > 9999.0f)
        temp = 9999.0f; // 限制显示上限

    n = (unsigned int)temp;
    OLED_ShowNum(Line, Column + 1, n, 4);

    OLED_ShowChar(Line, Column + 5, '.');

    temp -= (float)n;
    if (temp < 0)
        temp = 0;
    n = (unsigned int)(temp * OLED_Pow(10, FLen) + 0.5f);
    OLED_ShowNum(Line, Column + 6, n, FLen);
}