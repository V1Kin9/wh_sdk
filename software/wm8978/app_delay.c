#include "main.h"

void delay_us(u32 time)
{
#if IF_DEBUG 
	volatile u32 i;
	u8 j = 0;
	for(i = 0 ; i < time ;i++){
		for(j = 0; j < 2; j++) ;
	}
#endif	
#if 0 
	time *= 50;
	while(time--);	
#endif
}

void delay_ms(u32 time)
{
	volatile u32 i;
	for(i = 0 ; i < time ;i++){
		delay_us(1000);
	}	
}

void delay_s(u32 time)
{
	volatile u32 i;
	for(i = 0 ; i < time ;i++){
		delay_ms(1000);
	}	
}


