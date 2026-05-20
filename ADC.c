#include <STC89C5xRC.H>
#include "ADC.h"

void ADC_Init()
{
    XPT2046_DIN = 0;  // 初始化DIN引脚为低电平
    XPT2046_CS = 1;   // 初始化CS引脚为高电平（不选中）
    XPT2046_CLK = 0;  // 初始化CLK引脚为低电平
    XPT2046_DOUT = 1; // 初始化DOUT引脚为高电平
}

unsigned int ADC_ReadValue(unsigned char cmd)
{
    unsigned int adc_value = 0;
    unsigned char i;

    XPT2046_CS = 0; // 选中ADC芯片
    for (i = 0; i < 8; i++) {
        XPT2046_DIN = (cmd & 0x80) ? 1 : 0; // 发送命令的最高位 0x80 = 10000000b
        cmd <<= 1;                          // 左移命令以准备发送下一位
        XPT2046_CLK = 1;                    // 上升沿时钟
        XPT2046_CLK = 0;                    // 下降沿时钟
    }

    for (i = 0; i < 12; i++) {
        adc_value <<= 1; // 左移adc_value以准备接收下一位
        XPT2046_CLK = 1; // 上升沿时钟
        if (XPT2046_DOUT) {
            adc_value |= 0x01; // 如果DOUT为高电平，设置adc_value的最低位为1
        }
        XPT2046_CLK = 0; // 下降沿时钟
    }

    XPT2046_CS = 1; // 不选中ADC芯片
    return adc_value;
}
