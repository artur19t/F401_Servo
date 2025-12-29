#include "hw_init.h"

//PB4

void GPIO_PWM3_UsrInit(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_GPIO_InitTypeDef GPIO_UsrStruct = {0};
  GPIO_UsrStruct.Alternate = LL_GPIO_AF_2;
  GPIO_UsrStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_UsrStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_UsrStruct.Pin = LL_GPIO_PIN_4;
  GPIO_UsrStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_UsrStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  LL_GPIO_Init(GPIOB, &GPIO_UsrStruct);
}

void PWM3_CH1_UsrInit(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
  
  LL_TIM_SetPrescaler(TIM3, 84-1); //1MHz
  LL_TIM_SetAutoReload(TIM3, 20000-1); //50Hz
  
  // --- Set PWM mode 1Ch
  LL_TIM_OC_SetMode(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
  LL_TIM_OC_SetCompareCH1(TIM3, 1400);
  LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH1);
  
  LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH1);
  // --- Enable TIM3
  LL_TIM_EnableARRPreload(TIM3);
  LL_TIM_EnableCounter(TIM3);
  LL_TIM_GenerateEvent_UPDATE(TIM3);
}
