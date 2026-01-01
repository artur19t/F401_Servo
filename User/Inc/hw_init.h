#ifndef _HW_INIT
#define _HW_INIT

#include "main.h"

#define RX_SIZE 256

extern uint8_t rx_buf[RX_SIZE];

void GPIO_PWM3_UsrInit(void);
void PWM3_CH1_UsrInit(void);
void USART2_UsrInit(void);
void GPIO_USART2_UsrInit(void);
void DMA1_UsrInit(void);

#endif