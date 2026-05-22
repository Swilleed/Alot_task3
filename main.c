#include "mcu_compat.h"
#include "OLED.h"
#include "UART.h"
#include "ADC.h"
#include "PWM.h"
#include "Delay.h"

/* XPT2046 通道命令：单端 12-bit */
#define ADC_XP   0x94
#define ADC_YP   0xD4
#define ADC_AIN2 0xA4
#define ADC_AIN3 0xE4

void main()
{
    unsigned int ch0, ch1, ch2, ch3;

    OLED_Init();
    UART_Init();
    ADC_Init();
    PWM_Init();
    EA = 1;

    OLED_ShowString(0, 0, "Sys Ready");

    while (1) {
        ch0 = ADC_ReadValue(ADC_XP);
        ch1 = ADC_ReadValue(ADC_YP);
        ch2 = ADC_ReadValue(ADC_AIN2);
        ch3 = ADC_ReadValue(ADC_AIN3);

        /* CSV：xp,yp,ain2,ain3\r\n */
        UART_SendNumber(ch0);
        UART_SendByte(',');
        UART_SendNumber(ch1);
        UART_SendByte(',');
        UART_SendNumber(ch2);
        UART_SendByte(',');
        UART_SendNumber(ch3);
        UART_SendString("\r\n");

        /* 无 delay，由 UART 发送速度自然限制刷新率 */
    }
}
