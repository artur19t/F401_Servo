#include "hw_init.h"

//PA2,3
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

void GPIO_USART2_UsrInit(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  // --- USART2 TX PA2 ---
  LL_GPIO_InitTypeDef GPIO_UsrStruct = {0};
  GPIO_UsrStruct.Alternate = LL_GPIO_AF_7;
  GPIO_UsrStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_UsrStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_UsrStruct.Pin = LL_GPIO_PIN_2;
  GPIO_UsrStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_UsrStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  LL_GPIO_Init(GPIOA, &GPIO_UsrStruct);
  // --- USART2 RX PA3 ---
  memset(&GPIO_UsrStruct, 0, sizeof(LL_GPIO_InitTypeDef));
  GPIO_UsrStruct.Alternate = LL_GPIO_AF_7;
  GPIO_UsrStruct.Mode = LL_GPIO_MODE_ALTERNATE;;
  GPIO_UsrStruct.Pin = LL_GPIO_PIN_3;
  GPIO_UsrStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_UsrStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  LL_GPIO_Init(GPIOA, &GPIO_UsrStruct);
}

void PWM3_CH1_UsrInit(void)
{  
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
  // --- set tick to 50Hz ---
  LL_TIM_SetPrescaler(TIM3, 84-1); //1MHz
  LL_TIM_SetAutoReload(TIM3, 20000-1); //50Hz
  // --- Set PWM mode 1Ch ---
  LL_TIM_OC_SetMode(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
  LL_TIM_OC_SetCompareCH1(TIM3, 1500);
  LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH1);
  LL_TIM_OC_SetPolarity(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_OCPOLARITY_HIGH);
  // --- Conect to Pin ---
  LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH1);
  // --- Enable TIM3 ---
  LL_TIM_EnableARRPreload(TIM3);
  LL_TIM_EnableCounter(TIM3);
  LL_TIM_GenerateEvent_UPDATE(TIM3);
}

void USART2_UsrInit(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
  
  LL_USART_InitTypeDef USART_UsrStruct = {0};
  USART_UsrStruct.BaudRate = 9600;
  USART_UsrStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_UsrStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_UsrStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  USART_UsrStruct.Parity = LL_USART_PARITY_NONE;
  USART_UsrStruct.StopBits = LL_USART_STOPBITS_1;
  USART_UsrStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  LL_USART_Init(USART2, &USART_UsrStruct);
  
  LL_USART_ConfigAsyncMode(USART2);
  
  LL_USART_EnableIT_IDLE(USART2);
  NVIC_SetPriority(USART2_IRQn, 1);
  NVIC_EnableIRQ(USART2_IRQn);
  
  LL_USART_Enable(USART2);
}

void DMA1_UsrInit(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
  // --- USART2 TX CH4 Stream6 ---
  LL_DMA_InitTypeDef DMA_UsrStrct = {0};
  DMA_UsrStrct.Channel = LL_DMA_CHANNEL_4;
  DMA_UsrStrct.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
  DMA_UsrStrct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA_UsrStrct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_NOINCREMENT;
  DMA_UsrStrct.Mode = LL_DMA_MODE_NORMAL;
  DMA_UsrStrct.PeriphOrM2MSrcAddress = (uint32_t)&USART2->DR;
  DMA_UsrStrct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  DMA_UsrStrct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
  DMA_UsrStrct.Priority = LL_DMA_PRIORITY_LOW;
  LL_DMA_Init(DMA1, LL_DMA_STREAM_6, &DMA_UsrStrct);
  // --- USART2 RX CH4 Stream5 ---
  memset(&DMA_UsrStrct, 0, sizeof(LL_DMA_InitTypeDef));
  DMA_UsrStrct.Channel = LL_DMA_CHANNEL_4;
  DMA_UsrStrct.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
  DMA_UsrStrct.MemoryOrM2MDstAddress = (uint32_t)&rx_buf;
  DMA_UsrStrct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA_UsrStrct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
  DMA_UsrStrct.Mode = LL_DMA_MODE_NORMAL;
  DMA_UsrStrct.NbData = RX_SIZE;
  DMA_UsrStrct.PeriphOrM2MSrcAddress = (uint32_t)&USART2->DR;
  DMA_UsrStrct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  DMA_UsrStrct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
  DMA_UsrStrct.Priority = LL_DMA_PRIORITY_HIGH;
  LL_DMA_Init(DMA1, LL_DMA_STREAM_5, &DMA_UsrStrct);
  
  LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_5);
  
  LL_USART_EnableDMAReq_RX(USART2);
  LL_USART_EnableDMAReq_TX(USART2);
}
