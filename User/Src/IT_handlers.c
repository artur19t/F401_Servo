#include "IT_handlers.h"

void USART2_IRQHandler (void)
{
  if(LL_USART_IsActiveFlag_IDLE(USART2))
  {
    (void)USART1->SR;
    (void)USART1->DR;
    uint16_t received = RX_SIZE - LL_DMA_GetDataLength(DMA1, LL_DMA_STREAM_5);
    LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_5);
    LL_USART_ClearFlag_IDLE(USART2);
    USART2_logic(rx_buf,received);
    LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_5, RX_SIZE);
    LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_5);
  }
}
