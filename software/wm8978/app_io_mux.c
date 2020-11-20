#include "main.h"

#ifdef USE_IOMUX
//typedef enum {UART1,UART2,I2C,SPI,CAN,I2S,CCIN}iomux_type;  //define in head file
void iomux_init(iomux_type type)
{
	switch(type){
		case UART1:
			IOMUX_CONFIG_GPIO29 = 0x02;
			IOMUX_CONFIG_GPIO30 = 0x01;
		break;
		case UART2:
		break;
		case I2C:
		break;
		case SPI:
		break;
		case CAN:
		break;
		case I2S:
			IOMUX_CONFIG_GPIO24 = 33;   //i2s_mclk
			IOMUX_CONFIG_GPIO25 = 29;   //i2s_sdin
			IOMUX_CONFIG_GPIO26 = 28;   //i2s_sdout
			IOMUX_CONFIG_GPIO27 = 30;   //i2s_sclk
			IOMUX_CONFIG_GPIO28 = 27;   //i2s_lrck WS
#if 0
#define IOTEST  (*((volatile char*) 0x10004824))
			IOTEST = 36;
			printf("check reg value:\r\n");
			printf("*0x%x = %d\r\n",&IOMUX_CONFIG_GPIO24,IOMUX_CONFIG_GPIO24);
			printf("*0x%x = %d\r\n",&IOMUX_CONFIG_GPIO25,IOMUX_CONFIG_GPIO25);
			printf("*0x%x = %d\r\n",&IOMUX_CONFIG_GPIO26,IOMUX_CONFIG_GPIO26);
			printf("*0x%x = %d\r\n",&IOMUX_CONFIG_GPIO27,IOMUX_CONFIG_GPIO27);
			printf("*0x%x = %d\r\n",&IOMUX_CONFIG_GPIO28,IOMUX_CONFIG_GPIO28);
			printf("  *0x%x = %d\r\n",&IOTEST,IOTEST);
#endif
		break;
		case CCIN:
		break;
	}
}
void iomux_deinit(iomux_type type)
{
	switch(type){
		case UART1:
		break;
		case UART2:
		break;
		case I2C:
		break;
			IOMUX_CONFIG_GPIO20 = 0x00;   //audio_sdin
			IOMUX_CONFIG_GPIO21 = 0x00;   //audio_sclk
			IOMUX_CONFIG_GPIO22 = 0x00;   //audio_csb
			IOMUX_CONFIG_GPIO23 = 0x00;   //audio_mode
		case CAN:
		break;
		case I2S:
		break;
		case CCIN:
		break;	
	}
}

#endif



/**
  set IO pin mode, input or output ,if "pin_io_mode" is 1, the pin is output ,else isinput.
  **/
void app_config_gpio_pin_mode(u32 pin_num,u32 pin_io_mode)
{
	    IOMUX_CONTROL &=~ (1<<pin_num);
	    IOMUX_CONTROL |= (pin_io_mode<<pin_num);
}
void app_set_gpio_pin_value(u32 pin_num,u32 pin_value)
{
	    if(pin_value)
	        IOMUX_DATA_ALL |=  (1 << pin_num);
	    else
	        IOMUX_DATA_ALL  &=~ (1 << pin_num);
}
u32 app_get_gpio_pin_value(u32 pin_num)
{
	    return ((IOMUX_DATA_ALL&(1<<pin_num))>>pin_num);
}
u8 app_get_gpio_value_with_auto_set_mode(u32 pin_num)
{
	    volatile u8 temp;
	   // app_config_gpio_pin_mode(pin_num,1);   //set io mode output
		//app_set_gpio_pin_value(pin_num,0);  //set io port to 0
	    app_config_gpio_pin_mode(pin_num,0);  //set io mode input
		delay_ms(10);
	    temp = (u8)app_get_gpio_pin_value(pin_num);  //get io port value
	    app_config_gpio_pin_mode(pin_num,1);   //set io mode output
	    return temp;
}

