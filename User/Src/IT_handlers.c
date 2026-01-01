#include "IT_handlers.h"

void USART2_IRQHandler (void)
{
  if(LL_USART_IsActiveFlag_IDLE(USART2))
  {
    LL_USART_ClearFlag_IDLE(USART2);
  }
}
