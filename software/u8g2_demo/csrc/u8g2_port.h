#ifndef U8G2_PORT_H
#define U8G2_PORT_H

#include "platform.h"
#include "u8x8.h"

uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_gpio_and_delay_ls(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

#endif 
