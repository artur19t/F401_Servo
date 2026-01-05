#include "Connect_logic.h"

uint8_t len = 0;
static uint8_t buf_dma[RX_SIZE];
enum parse_status_t
{
    PARSE_OK = 0,
    PARSE_ERR_EMPTY,
    PARSE_ERR_NOT_DIGIT,
    PARSE_ERR_OVERFLOW
};

void USART2_logic(uint8_t *buf, uint16_t dSize, bool need_s)
{
  uint32_t val = 0;
  uint8_t res = 0;
  DMA_buf(buf, dSize, need_s);
  if(!need_s)
  {
    res = parse_from_uart(buf_dma, len, &val);
    uint32_t timer_val = 600;
    timer_val += (uint32_t)(val*8.89);
    LL_TIM_OC_SetCompareCH1(TIM3, timer_val);
    len = 0;
  }
}
void DMA_buf(uint8_t *bufAddr, uint16_t dSize, bool need_s)
{
  for(uint16_t i = 0; i < dSize; i++)
  {
    uint8_t c = bufAddr[i];
    if(c == '\r' || c == '\n')
    {
      break;
    }
    buf_dma[len] = c;
    len++;
  }
  if (!need_s)
  {
    buf_dma[len] = '\0';
  }
}
enum parse_status_t parse_from_uart(const uint8_t *buf, uint16_t len, uint32_t *value)
{
  uint32_t result = 0;

  if (buf == NULL || len == 0)
  {
    return PARSE_ERR_EMPTY;
  }
  for (size_t i = 0; i < len; i++)
  {
    if (buf[i] < '0' || buf[i] > '9')
    {
      return PARSE_ERR_NOT_DIGIT;
    }
    uint8_t digit = buf[i] - '0';

    if (result > (UINT32_MAX - digit) / 10)
    {
      return PARSE_ERR_OVERFLOW;
    }
    result = result * 10 + digit;
  }

  *value = result;
  return PARSE_OK;
}
