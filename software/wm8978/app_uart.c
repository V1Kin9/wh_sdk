#include "main.h"


void app_uart_init()
{
	uart_init(115200);	
//	(*((volatile char *)(0x1000481d))) = 0x2; 
//	(*((volatile char *)(0x1000481e))) = 0x1;
//	iomux_init(UART1);	
}
