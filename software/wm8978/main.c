/*********************************************************************************
*
*       PROJECT:        WH32_DDR 
* 
*       FILENAME:       wm8978.c 
* 
*       FUNCTION:       wm8978 driver 
* 
*       AUTHOR:         zengxr 
* 
*       DATE:           Fri Apr 10 12:10:02 CST 2020 
* 
*       ISFINISH:       NO 
* 
*       STATUS:  
*********************************************************************************/
#include "platform.h"
#include "main.h"

#define printf if(IF_DEBUG) printf
int main(void)
{
    /* write your code here */
	app_uart_init();
	app_i2c_init();
	if(wm8978_init()){
		printf("wm8978 init fail \r\n");
	}else{
		printf("wm8978 init secc\r\n");
	}
	i2s_init();	
	printf("s\r\n");
	u32 i=0;
	while(1){
#if 1
	   //player_init();	
	//	printf("wm8978_init = %d\r\n",wm8978_init());
		printf("play times = %d\r\n",i++);
		player_init();
#else
		for(i = 0; i < 31 ; i++)
		printf("%d value = %d \r\n",i,app_get_gpio_value_with_auto_set_mode(i));
#endif
	}
	return 0;
}
