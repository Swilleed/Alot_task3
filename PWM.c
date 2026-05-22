#include <STC89C5xRC.H>
#include "PWM.h"

static unsigned char pwm_counter = 0;
static unsigned char pwm_duty_a = 0;
static unsigned char pwm_duty_b = 0;

/* Timer 0 16-bit 重载值（mode 1 手动重载） */
static unsigned int reload_val;

/* Timer 0 ISR — mode 1，手动重载 */
void timer0_isr(void) interrupt 1 using 1
{
    TL0 = (unsigned char)reload_val;
    TH0 = (unsigned char)(reload_val >> 8);

    if (++pwm_counter >= 100) {
        pwm_counter = 0;
    }

    P10 = (pwm_counter < pwm_duty_a) ? 1 : 0;
    P11 = (pwm_counter < pwm_duty_b) ? 1 : 0;
}

void PWM_Init(void)
{
    pwm_duty_a = 50;
    pwm_duty_b = 0;

    P10 = 1;
    P11 = 0;

    /* Timer 0 mode 1（16-bit 手动重载） */
    TMOD &= 0xF0;
    TMOD |= 0x01;

    /* 默认 5Hz @ 11.0592MHz：tick = 9216/5 = 1843 → reload = 65536-1843 */
    reload_val = 63693;
    TL0 = (unsigned char)reload_val;
    TH0 = (unsigned char)(reload_val >> 8);

    ET0 = 1;
    TR0 = 1;
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
    unsigned int tick;

    if (freq_hz < 1)   freq_hz = 1;
    if (freq_hz > 300) freq_hz = 300;

    tick = 9216U / freq_hz;

    EA = 0;
    reload_val = 65536U - tick;
    EA = 1;
}
