#include "mcu_compat.h"
#include "OLED.h"
#include "UART.h"
#include "ADC.h"
#include "PWM.h"
#include "Delay.h"

/* XPT2046 通道命令：单端 12-bit */
#define ADC_CH0  0x94
#define ADC_CH1  0xD4

void main()
{
    unsigned int ch0, ch1;

    OLED_Init();
    UART_Init();
    ADC_Init();
    PWM_Init();
    EA = 1;

    OLED_ShowString(0, 0, "Sys Ready");

    while (1) {
        ch0 = ADC_ReadValue(ADC_CH0);
        ch1 = ADC_ReadValue(ADC_CH1);

        /* CSV 格式：ch0,ch1\r\n */
        UART_SendNumber(ch0);
        UART_SendByte(',');
        UART_SendNumber(ch1);
        UART_SendString("\r\n");

        Delay(10);
    }
}
