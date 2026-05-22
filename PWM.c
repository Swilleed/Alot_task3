#include <STC89C5xRC.H>
#include "PWM.h"

void PWM_Init()
{
    // 配置 P1.0 和 P1.1 为输出（将对应位设为高）
    P1 |= 0x03;

    // 配置定时器2为自动重载模式，用作 PWM 基准周期
    T2MOD = 0x00;  // 普通自动重载
    RCAP2H = 0xFF; // 设定重载值（高位）
    RCAP2L = 0x00; // 设定重载值（低位）
    TH2 = RCAP2H;
    TL2 = RCAP2L;
    T2CON |= 0x04; // 启动定时器2（TR2 = 1）
}

void PWM_SetDutyCycle(unsigned char duty_cycle)
{
    if (duty_cycle > 100) {
        duty_cycle = 100; // 限制占空比在0-100范围内
    }
    // 将 0-100% 映射到 0-255 的比较值（越大占空比越高）
    TL2 = (unsigned char)((duty_cycle * 255U) / 100U);
}
