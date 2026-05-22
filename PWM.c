#include <STC89C5xRC.H>
#include "PWM.h"

static unsigned char pwm_counter = 0;
static unsigned char pwm_duty_a = 0;
static unsigned char pwm_duty_b = 0;

/* Timer 0 ISR — 软件 PWM，100 步分辨率 */
void timer0_isr(void) interrupt 1
{
    /* Timer 0 mode 2 自动重载，无需手动赋值 */

    if (++pwm_counter >= 100) {
        pwm_counter = 0;
    }

    P10 = (pwm_counter < pwm_duty_a) ? 1 : 0;
    P11 = (pwm_counter < pwm_duty_b) ? 1 : 0;
}

void PWM_Init(void)
{
    P10 = 0;
    P11 = 0;

    /* Timer 0, mode 2 (8-bit 自动重载) */
    TMOD &= 0xF0;
    TMOD |= 0x02;

    /* 默认 100Hz：tick = 100µs → TH0 = 256 - 100 = 156 */
    TH0 = 156;
    TL0 = 156;

    ET0 = 1;  /* 允许 Timer 0 中断 */
    TR0 = 1;  /* 启动 Timer 0 */
}

void PWM_SetDutyCycle(unsigned char duty)
{
    if (duty > 100) duty = 100;
    pwm_duty_a = duty;
}

void PWM_SetDutyCycleB(unsigned char duty)
{
    if (duty > 100) duty = 100;
    pwm_duty_b = duty;
}

void PWM_SetFrequency(unsigned int freq_hz)
{
    unsigned char tick;

    if (freq_hz < 40)  freq_hz = 40;
    if (freq_hz > 300) freq_hz = 300;

    /* tick_us = 10000 / freq_hz → 机器周期数 (12MHz 下 1µs = 1 周期) */
    tick = 10000U / freq_hz;

    TH0 = 256 - tick;
    TL0 = 256 - tick;
}
