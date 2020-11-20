#include "main.h"


#define IIC_SCL_H()  app_set_gpio_pin_value(17,1)
#define IIC_SCL_L()  app_set_gpio_pin_value(17,0)
#define IIC_SDA_H()  app_set_gpio_pin_value(16,1)
#define IIC_SDA_L()  app_set_gpio_pin_value(16,0)
#define IIC_SDA_RD() app_get_gpio_value_with_auto_set_mode(16)


#define GPIO_MODE_OUT 1
#define GPIO_MODE_IN  0
/***************************
GPIO20 => sda
GPIO21 => scl
GPIO22 => csb  nouse
GPIO23 => mode if set 0 2wire mode, if set 1 is 3wire mode


***************************/
#define SDA_PIN_NUM 16
#define SCL_PIN_NUM 17
#define CSB_PIN_NUM 18
#define MOD_PIN_NUM 19

#define IIC_DATA_DELAY() delay_us(10)
#define IIC_READ_ACK_DELAY() delay_us(10)

void app_i2c_init()
{
//set io pin to input or output
	//use soft simulate i2c
	IOMUX_CONFIG_GPIO20 = 0x00;   //audio_sdin
    IOMUX_CONFIG_GPIO21 = 0x00;   //audio_scl
    IOMUX_CONFIG_GPIO22 = 0x00;   //audio_csb
    IOMUX_CONFIG_GPIO23 = 0x00;   //audio_mode
//set GPIO deriction

	IOMUX_CONTROL |= (0xb<<16);   //set input or output
//set wm8978 control mode is 2 wires mode
	IOMUX_DATA_ALL &=~ (1<<19);   //set mode to 0,set 2 wire mode
//	app_config_gpio_pin_mode(SDA_PIN_NUM , GPIO_MODE_OUT);
//	app_config_gpio_pin_mode(SCL_PIN_NUM , GPIO_MODE_OUT);
//	app_config_gpio_pin_mode(CSB_PIN_NUM , GPIO_MODE_IN);
//	app_config_gpio_pin_mode(MOD_PIN_NUM , GPIO_MODE_OUT);

	

//all wire set 0
	IIC_SCL_L();
    IIC_SDA_L();
}


void app_i2c_start(void)
{
    IIC_SDA_H();
	IIC_SCL_H();  //  
    
    IIC_DATA_DELAY(); //
    IIC_SDA_L(); //
    
    IIC_DATA_DELAY(); //
    IIC_SCL_L();
}
void app_i2c_stop(void)
{
    IIC_SDA_L();
    IIC_SCL_L();  //

    IIC_DATA_DELAY();
    IIC_SCL_H();//

    IIC_DATA_DELAY(); //
    IIC_SDA_H(); //
}

u8 app_i2c_senddata8(u8 data)
{
    u8 i;
    u8 Ack;

    for(i=0;i<8;i++)
    {
        if(data & 0x80)  //
        {
            IIC_SDA_H();
        }
        else
        {
            IIC_SDA_L();
        }

		 IIC_DATA_DELAY();
        IIC_SCL_H();

        IIC_DATA_DELAY();
        IIC_SCL_L();

        data <<=1;
    }
#if 0 
	IIC_SDA_H();
    IIC_DATA_DELAY();
    IIC_SCL_H();
	Ack =IIC_SDA_RD();
   	IIC_DATA_DELAY(); 
   	IIC_SCL_L();
    return Ack;
#else
	IIC_SDA_H();
	app_config_gpio_pin_mode(16,0);  //set io mode input
	IIC_READ_ACK_DELAY();
    IIC_SCL_H();
    Ack = (u8)app_get_gpio_pin_value(16);  //get io port value
   	if(Ack){
		printf("NAck!\r\n");
	}
	IIC_DATA_DELAY(); 
   	IIC_SCL_L();
    app_config_gpio_pin_mode(16,1);   //set io mode output
    return Ack;
#endif


}

u8 app_i2c_revdata8(u8 Ack)
{
    u8 i;
    u8 data;

    IIC_SDA_H();

    for(i=0;i<8;i++)
    {
        IIC_DATA_DELAY();
        IIC_SCL_H();

        data <<=1;
        data |=IIC_SDA_RD();

        IIC_DATA_DELAY();
        IIC_SCL_L();
    }


    if(Ack)  
    {
        IIC_SDA_H();
    }
    else
    {
        IIC_SDA_L();
    }
    IIC_DATA_DELAY();
    IIC_SCL_H();

    IIC_DATA_DELAY();
    IIC_SCL_L();

    return data;
}
