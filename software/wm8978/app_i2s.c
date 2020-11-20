#include "main.h"

void i2s_init()
{
	//iomux_init(I2S);
#if 1 
	//double stereo 16K
	(*((volatile int *)(0x10004d20))) = 47;	//divide clock (1+7)*2 _sclk;  32bit 16K
	(*((volatile int *)(0x10004d24))) = 11;	//divide clock (1+1)*2 _mclk;
#else
	//double stereo 48K
	(*((volatile int *)(0x10004d20))) = 7;	//divide clock (1+7)*2 _sclk;  32bit 16K
	(*((volatile int *)(0x10004d24))) = 1;	//divide clock (1+1)*2 _mclk;
#endif
	I2S_IER = 1; //enable I2S
	I2S_IRER = 1; //enable reciver
	I2S_ITER = 1; //enable transmiter
#if 1 
    I2S_TER =0;
	I2S_RER =0;
//	I2S_RCR = 0x04; //24-bits data resolution the receriver
//	I2S_TCR = 0X04; //24-bits data resolution the transmitter
	I2S_RCR = 0x02; //16-bits data resolution the receriver
	I2S_TCR = 0X02; //16-bits data resolution the transmitter
	I2S_TER =1;
	I2S_RER =1;

#endif

	I2S_CER =0;  //i2s as master,should set this reg
	I2S_CCR = ((2<<3)|(0x2));  //32 sclk cyccles
//	I2S_CCR = ((1<<3)|(0x2));  //24 sclk cyccles
//	I2S_CCR = ((0<<3)|(0x2));  //16 sclk cyccles
	I2S_CER = 1;  //i2s as master,should set this reg
	

	I2S_IRER =0; //enable reciver
	I2S_ITER =0; //enable transmiter
	I2S_RXFFR = 1; //clear the receiver fifo
	I2S_TXFFR = 1; //clear the transmitter fifo
	I2S_RFF = 1; //flushed an individual RX FIFO
	I2S_TFF = 1; //flushed an individual TX FIFO
	I2S_IRER = 1; //enable reciver
	I2S_ITER = 1; //enable transmiter
#if 1	
	I2S_TER =0;
	I2S_RER =0;
//	I2S_RCR = 0x04; //24-bits data resolution the receriver
//	I2S_TCR = 0X04; //24-bits data resolution the transmitter
	I2S_RCR = 0x02; //16-bits data resolution the receriver
	I2S_TCR = 0X02; //16-bits data resolution the transmitter
	I2S_TER =1;
	I2S_RER =1;
#endif
	I2S_IMR =0; //do not mask interrupt
	
	I2S_IRER =0; //enable reciver
	I2S_ITER =0; //enable transmiter
	I2S_RFCR = 0X7; //interrupt tregger level is 4
	I2S_TFCR = 0X7; //interrupt tregger level is 4
	I2S_IRER = 1; //enable reciver
	I2S_ITER = 1; //enable transmiter

	
	I2S_IRER =1; //enable reciver
	
	I2S_RER = 1;
	I2S_TER = 1;




#if 0 
 	unsigned int i = 0;
	u32 re_temp;
				printf("the reg is 0x%04x\r\n",I2S_ISR);
	while(1){
		//I2S_LRBR = i;
			if((I2S_ISR &(1<<4))){
				I2S_LTHR = 0xcccc;
				I2S_RTHR = 0x1111;
	//		    printf("data trans ok\r\n");	
			}else{
//				printf("the fifo is not ready\r\n");
//				printf("the reg is 0x%04x\r\n",I2S_ISR);
			}
	}
#endif
}
