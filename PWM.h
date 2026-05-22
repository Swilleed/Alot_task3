#ifndef PWM_H
#define PWM_H

void PWM_Init(void);
void PWM_SetDutyCycle(unsigned char duty);    /* 0-100%，通道 A (P1.0) */
void PWM_SetDutyCycleB(unsigned char duty);   /* 0-100%，通道 B (P1.1) */
void PWM_SetFrequency(unsigned int freq_hz);  /* 40-300 Hz */

#endif
