#include "main.h"
#define printf if(IF_DEBUG) printf
void wav_decoder(u8 * data)
{
	u32 samplerate,bitw=16,chanel=2,MusicLen;
	u32 music_time;
	u32 bytepersec;
	u8 * wav_head = data;
	u8 res;
	char buf[20];
#if 0 
	while(wm8978_init())
	{
		printf("wm8978 init error\r\n");
		delay_ms(500);
	}
	printf("wm8978 is ok\r\n");
	
#endif
//	WM8978_HPvol_Set(63,63);	//set headphone volume 
//	WM8978_SPKvol_Set(50);		//set speaker volume
	samplerate = (wav_head[0x1b]<<24)|
				(wav_head[0x1a]<<16) |
				(wav_head[0x19]<<8) |
				(wav_head[0x18]<<0);
	printf("sample rate = %d\r\n",samplerate);
	bytepersec= ((wav_head[0x1f]&0xff)<<24)
				|((wav_head[0x1e]&0xff)<<16) 
				|((wav_head[0x1d]&0xff)<<8)
				|((wav_head[0x1c]&0xff)<<0);
	printf("byte per sec = %d\r\n",bytepersec);	
	chanel = (wav_head[0x17]<<8)|(wav_head[0x16]<<0);
	printf("channel = %d\r\n",chanel);	
	MusicLen= (wav_head[0x07]<<24)|
		(wav_head[0x06]<<16) |
		(wav_head[0x05]<<8) |
		(wav_head[0x04]<<0);
	MusicLen+=8;
	if(wav_head[0x10]==0x10)
	{
		//f_read(&fp,&wav_head[32],44-32,&Num);
		
		MusicLen-=44;
		printf("MusicLen:%u\r\n",MusicLen);	
		data = wav_head+44;
	}
	else if(wav_head[0x10]==0x12)  
	{
		//f_read(&fp,&wav_head[32],58-32,&Num);
		MusicLen-=58;
		printf("MusicLen:%u\r\n",MusicLen);
		data = wav_head+58;
	}
	else if(wav_head[0x10]==0x32)	
	{	
		//f_read(&fp,&wav_head[32],90-32,&Num);
		MusicLen-=90;
		data = wav_head+90;
		printf("MusicLen:%u\r\n",MusicLen);
	}
	else if(wav_head[0x10]==0x14)
	{			
		//f_read(&fp,&wav_head[32],60-32,&Num);
		MusicLen-=60;
		printf("MusicLen:%u\r\n",MusicLen);
		data = wav_head+60;
	}
	music_time=	MusicLen/bytepersec;
	printf("misic time = %02d:%02d\r\n",music_time/60,music_time%60);
	bitw = (wav_head[0x23]<<8)|(wav_head[0x22]<<0);
	printf("bitwidth = %d \r\n",bitw);
//	WM8978_I2S_Cfg(2,0);//use Philips standard 16 data width
	//I2S2_Init(bitw);
//	WM8978_ADDA_Cfg(1,0);  //open DAC	
///	WM8978_Input_Cfg(0,0,0);  //stop input channel
//	WM8978_Output_Cfg(1,0);	  //open DAC output
	//I2S2_SampleRate_Set(samplerate);  //set I2S sample rate
	//I2S2_TX_DMA_Init(buf0,buf1,8192/2);  
#if 1
	u32 i ;
	u32 music_data;
	u32 temp;
	WM8978_PlayMode();
while(1){
	
	for(i = 0; i < MusicLen;){
		music_data = 0;
		music_data |=data[i+1];
		music_data <<=8;
		music_data |= data[i];
		i++;
		//printf("%d: = 0x%04x\r\n",i,music_data)
		if(I2S_ISR & (1<<4)){
	//		printf("fifo is ok\r\n");
#if 0
 			while(1){
			if((I2S_ISR & (1<<4) ) && (I2S_ISR & (1<<4) )){
			#if 1 
			I2S_LTHR = I2S_LRBR;
			I2S_RTHR = I2S_RRBR;
			#else
				I2S_RTHR = 0;
				temp = I2S_RRBR;
				I2S_LTHR = I2S_LRBR;
				//I2S_RTHR = I2S_RRBR;
			#endif
			}
		}
#else
		I2S_LTHR = music_data;
		I2S_RTHR = music_data; 
		
		//printf("L:%x\r\n",I2S_LRBR);
		//printf("R:%x\r\n",I2S_RRBR);
#endif
			i++;
		}else{
			i--;
		//	printf("the fifo is not ok\r\n");
		//	continue;
		}

	}
		printf("play one time over i=%d \r\n",i);
		delay_ms(2000);
}
#endif
	return ;
}


void player_init()
{
	wav_decoder(Music2);
}


