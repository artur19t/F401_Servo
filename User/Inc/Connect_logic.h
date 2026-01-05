#ifndef _CONNECT_LOGIC
#define _CONNECT_LOGIC
#include "main.h"

extern uint8_t len;
enum parse_status_t;
void USART2_logic(uint8_t *buf, uint16_t len, bool need_s);
void DMA_buf(uint8_t *bufAddr, uint16_t dSize, bool need_s);
enum parse_status_t parse_from_uart(const uint8_t *buf, uint16_t len, uint32_t *value);

#endif