#ifndef ADC_H
#define ADC_H

#define XPT2046_DIN P34
#define XPT2046_CS P35
#define XPT2046_CLK P36
#define XPT2046_DOUT P37

void ADC_Init();
unsigned int ADC_ReadValue(unsigned char cmd);

#endif
