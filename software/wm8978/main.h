#ifndef __MAIN_H_
#define __MAIN_H_

#define IF_DEBUG 1 
typedef unsigned int u32;
typedef  int i32;
typedef unsigned short int u16;
typedef short int i16;
typedef unsigned char  u8;
typedef char i8;


#if 0
typedef u32 uint32_t;
typedef i32 int32_t;
typedef u16 uint16_t;
typedef i16 int16_t;
typedef u8 uint8_t;
typedef i8 int8_t;
#endif

#include "app_uart.h"
#include "wm8978.h"
#include "app_soft_i2c.h"
#include "app_io_mux.h"
#include "app_delay.h"
#include "music.h"
#include "app_i2s.h"
#include "player.h"
#include "app_speaker.h"



#endif
