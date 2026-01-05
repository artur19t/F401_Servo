#include "IT_handlers.h"

uint16_t old_pos = 0;
void USART2_IRQHandler (void)
{
  if(LL_USART_IsActiveFlag_IDLE(USART2))
  {
    bool need_s = false;
    LL_USART_ClearFlag_IDLE(USART2);
    uint16_t received = RX_SIZE - LL_DMA_GetDataLength(DMA1, LL_DMA_STREAM_5);
    if (old_pos < received)
    {
      uint16_t len_b = 0;
      len_b = received - old_pos;
      USART2_logic(rx_buf+old_pos, len_b, need_s);
    }else if (old_pos>=received)
    {
      uint16_t len_b = 0;
      len_b = RX_SIZE - old_pos;
      need_s = 1;
      USART2_logic(rx_buf+old_pos, len_b, need_s);
      need_s = 0;
      len_b = received;
      USART2_logic(rx_buf, len_b, need_s);
    }
    old_pos = received;
  }
}
