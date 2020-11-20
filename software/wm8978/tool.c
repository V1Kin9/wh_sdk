#include "main.h"



int reg_write_read_test_if_ok(int addr,int len){	
	volatile unsigned char *reg = (unsigned char *)addr;
	int i,j;
	for(j = 0 ; j < len ; j++){
		for(i = 0 ; i <= 256 ; i++  ){
			*(reg+j) = (unsigned char)i;
			if(*(reg+j) != (unsigned char)i){
				printf("mem 0x%x  write or read value = %d disenable!!\r\n",reg+j,i);
				break;
			}else if(i == 255){
				printf("mem 0x%x is ok\r\n",reg+j);
			}
		}
	}
	return 1;
}

char test_one_bit_is_ok(int addr , int bit_pos){
	volatile unsigned char *reg = (unsigned char *)addr;
	int i = 0;
	i = (*reg)&(1<<bit_pos);
	*reg &=~(1<<bit_pos);
	if(*reg & (1<<bit_pos)){
		return 'N';
	}
	*reg |= (1<<bit_pos);
	if(!( *reg & (1<<bit_pos))){
		return 'N';
	}
	*reg &=~(1<<bit_pos);
	if(*reg & (1<<bit_pos)){
		return 'N';
	}
	*reg |= i;
	return 'Y';

}

int reg_bit_write_read_test_if_ok(int addr,int len){    
    int i,j;
	printf(" bit pos:  7  6  5  4  3  2  1  0\r\n");
	for(i = 0 ; i <= len ; i++){  
		printf("0x%x:",addr+i);
		for(j = 7;j>0;j--){
			printf("%c  ",test_one_bit_is_ok(addr+i,j));
		}
		printf("%c\r\n",test_one_bit_is_ok(addr+i,j));
	}
   return 1;
}

void peri_test_reg()
{
	printf("test GPIO reg\r\n");
	reg_bit_write_read_test_if_ok(0x10000000,7);
	printf("test UART0 reg\r\n");
	reg_bit_write_read_test_if_ok(0x10000010,7);
	printf("test UART1 reg\r\n");
	reg_bit_write_read_test_if_ok(0x100000c0,7);
	printf("test SPI reg\r\n");
	reg_bit_write_read_test_if_ok(0x10000018,3);
	printf("test I2C reg\r\n");
	reg_bit_write_read_test_if_ok(0x10000060,7);
	printf("test ETIMER0 reg\r\n");
	reg_bit_write_read_test_if_ok(0x10000080,0x1f);
	printf("test ETIMER1 reg\r\n");
	reg_bit_write_read_test_if_ok(0x100000a0,0x1f);
//	printf("test VGA reg\r\n");
//	reg_bit_write_read_test_if_ok(0x10003000,0xffc);
	printf("test CAN reg\r\n");
	reg_bit_write_read_test_if_ok(0x10000040,0x1f);
//	printf("test SDCARD reg\r\n");
//	reg_bit_write_read_test_if_ok(0x10004000,0x3ff);
}
