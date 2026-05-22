#include "mcu_compat.h"
#include "OLED.h"
#include "UART.h"
#include "ADC.h"
#include "Delay.h"

/* XPT2046 命令：单端 12-bit */
#define ADC_CH0  0x94

void main()
{
    unsigned int adc_val;

    OLED_Init();
    UART_Init();
    ADC_Init();
    OLED_ShowString(0, 0, "ADC+UART OK");

    while (1) {
        adc_val = ADC_ReadValue(ADC_CH0);

        UART_SendNumber(adc_val);
        UART_SendString("\r\n");

        Delay(10);  /* ~10ms 采样间隔 */
    }
}
