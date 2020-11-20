#ifndef __APP_IO_MUX_H_
#define __APP_IO_MUX_H_
#include "platform.h"

typedef enum {UART1,UART2,I2C,SPI,CAN,I2S,CCIN}iomux_type;

void iomux_init(iomux_type type);
void iomux_deinit(iomux_type type);


/**
  set IO pin mode, input or output ,if "pin_io_mode" is 1, the pin is output ,else isinput.
  **/
u8 app_get_gpio_value_with_auto_set_mode(u32 pin_num);
u32 app_get_gpio_pin_value(u32 pin_num);
void app_set_gpio_pin_value(u32 pin_num,u32 pin_value);
void app_config_gpio_pin_mode(u32 pin_num,u32 pin_io_mode);

#define IOMUX_CONFIG_GPIO0  (*((volatile char*) 0x10004800))
#define IOMUX_CONFIG_GPIO1  (*((volatile char*) 0x10004801))
#define IOMUX_CONFIG_GPIO2  (*((volatile char*) 0x10004802))
#define IOMUX_CONFIG_GPIO3  (*((volatile char*) 0x10004803))
#define IOMUX_CONFIG_GPIO4  (*((volatile char*) 0x10004804))
#define IOMUX_CONFIG_GPIO5  (*((volatile char*) 0x10004805))
#define IOMUX_CONFIG_GPIO6  (*((volatile char*) 0x10004806))
#define IOMUX_CONFIG_GPIO7  (*((volatile char*) 0x10004807))
#define IOMUX_CONFIG_GPIO8  (*((volatile char*) 0x10004808))
#define IOMUX_CONFIG_GPIO9  (*((volatile char*) 0x10004809))
#define IOMUX_CONFIG_GPIO10 (*((volatile char*) 0x1000480a))
#define IOMUX_CONFIG_GPIO11 (*((volatile char*) 0x1000480b))
#define IOMUX_CONFIG_GPIO12 (*((volatile char*) 0x1000480c))
#define IOMUX_CONFIG_GPIO13 (*((volatile char*) 0x1000480d))
#define IOMUX_CONFIG_GPIO14 (*((volatile char*) 0x1000480e))
#define IOMUX_CONFIG_GPIO15 (*((volatile char*) 0x1000480f))
#define IOMUX_CONFIG_GPIO16 (*((volatile char*) 0x10004810))
#define IOMUX_CONFIG_GPIO17 (*((volatile char*) 0x10004811))
#define IOMUX_CONFIG_GPIO18 (*((volatile char*) 0x10004812))
#define IOMUX_CONFIG_GPIO19 (*((volatile char*) 0x10004813))
#define IOMUX_CONFIG_GPIO20 (*((volatile char*) 0x10004814))
#define IOMUX_CONFIG_GPIO21 (*((volatile char*) 0x10004815))
#define IOMUX_CONFIG_GPIO22 (*((volatile char*) 0x10004816))
#define IOMUX_CONFIG_GPIO23 (*((volatile char*) 0x10004817))
#define IOMUX_CONFIG_GPIO24 (*((volatile char*) 0x10004818))
#define IOMUX_CONFIG_GPIO25 (*((volatile char*) 0x10004819))
#define IOMUX_CONFIG_GPIO26 (*((volatile char*) 0x1000481a))
#define IOMUX_CONFIG_GPIO27 (*((volatile char*) 0x1000481b))
#define IOMUX_CONFIG_GPIO28 (*((volatile char*) 0x1000481c))
#define IOMUX_CONFIG_GPIO29 (*((volatile char*) 0x1000481d))
#define IOMUX_CONFIG_GPIO30 (*((volatile char*) 0x1000481e))
#define IOMUX_CONFIG_GPIO31 (*((volatile char*) 0x1000481f))

#define IOMUX_CONTROL        (*((volatile int*) 0x10000004))
#define IOMUX_DATA_ALL       (*((volatile int *) 0x10000000))
#define IOMUX_DATA_GROUP_IO0 (*((volatile char*) 0x10000000))
#define IOMUX_DATA_GROUP_IO1 (*((volatile char*) 0x10000001))
#define IOMUX_DATA_GROUP_IO2 (*((volatile char*) 0x10000002))
#define IOMUX_DATA_GROUP_IO3 (*((volatile char*) 0x10000003))



#endif
