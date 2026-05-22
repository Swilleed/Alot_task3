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

/* 解析 "Value = xxx"，成功返回 1，值存入 val */
static unsigned char parse_value_cmd(const unsigned char *str, unsigned int *val)
{
    while (*str == ' ') str++;
    if (str[0] != 'V' || str[1] != 'a' || str[2] != 'l' ||
        str[3] != 'u' || str[4] != 'e') return 0;
    str += 5;
    while (*str == ' ') str++;
    if (*str != '=') return 0;
    str++;
    while (*str == ' ') str++;

    *val = 0;
    while (*str >= '0' && *str <= '9') {
        *val = *val * 10 + (*str - '0');
        str++;
    }
    return 1;
}

void main()
{
    unsigned int ch0, ch1, ch2, ch3;
    unsigned int target_val;

    OLED_Init();
    UART_Init();
    ADC_Init();
    PWM_Init();
    EA = 1;

    OLED_ShowString(0, 0, "Sys Ready");

    while (1) {
        /* 基础要求 2：串口中断接收 + Value 解析 */
        if (UART_CommandReady()) {
            if (parse_value_cmd(UART_GetCommand(), &target_val)) {
                if (target_val <= 100)
                    PWM_SetDutyCycle((unsigned char)target_val);
                OLED_ShowString(1, 0, "Val:");
                OLED_ShowNum(1, 4, target_val, 5);
            }
        }

        /* 多通道 ADC 采集 */
        ch0 = ADC_ReadValue(ADC_XP);
        ch1 = ADC_ReadValue(ADC_YP);
        ch2 = ADC_ReadValue(ADC_AIN2);
        ch3 = ADC_ReadValue(ADC_AIN3);

        /* CSV 输出 */
        UART_SendNumber(ch0);
        UART_SendByte(',');
        UART_SendNumber(ch1);
        UART_SendByte(',');
        UART_SendNumber(ch2);
        UART_SendByte(',');
        UART_SendNumber(ch3);
        UART_SendString("\r\n");
    }
}
