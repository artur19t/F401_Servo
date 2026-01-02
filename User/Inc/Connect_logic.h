#ifndef _CONNECT_LOGIC
#define _CONNECT_LOGIC
#include "main.h"
enum parse_status_t;
void USART2_logic(uint8_t *buf, uint16_t len);
enum parse_status_t parse_from_uart(const uint8_t *buf, uint16_t len, uint32_t *value);

#endif