#include "IT_handlers.h"

void USART2_IRQHandler (void)
{
  if(LL_USART_IsActiveFlag_IDLE(USART2))
  {
    LL_USART_ClearFlag_IDLE(USART2);
    LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_5);
    uint16_t received = RX_SIZE - LL_DMA_GetDataLength(DMA1, LL_DMA_STREAM_5);
    
    USART2_logic(rx_buf,received);
    
    LL_DMA_ClearFlag_TC5(DMA1);
    LL_DMA_ClearFlag_HT5(DMA1);
    LL_DMA_ClearFlag_TE5(DMA1);
    LL_DMA_ClearFlag_DME5(DMA1);
    LL_DMA_ClearFlag_FE5(DMA1);
    
    //LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_5, (uint32_t)rx_buf);
    LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_5, RX_SIZE);
    LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_5);
  }
}
