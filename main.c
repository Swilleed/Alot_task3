#include "mcu_compat.h"
#include "OLED.h"
#include "UART.h"
#include "ADC.h"
#include "PWM.h"

void main()
{
    OLED_Init();
    OLED_ShowString(0, 0, "System Ready");

    while (1) {
        // TODO: 循环读取 ADC 数据，通过串口发送给上位机
    }
}
