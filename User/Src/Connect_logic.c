#include "Connect_logic.h"

enum parse_status_t
{
    PARSE_OK = 0,
    PARSE_ERR_EMPTY,
    PARSE_ERR_NOT_DIGIT,
    PARSE_ERR_OVERFLOW
};

void USART2_logic(uint8_t *buf, uint16_t len)
{
  uint32_t val = 0;
  uint8_t res = 0;
  res = parse_from_uart(buf, len, &val);
  if (res == PARSE_OK)
  {
    uint32_t timer_val = 1000;
    timer_val += (uint32_t)(val*5.55);
    LL_TIM_OC_SetCompareCH1(TIM3, timer_val);
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
