#include "main.h" 
#define wm8978_WriteReg WM8978_write_reg
//because wm8978 can not read reg, so we use some cache to save the value of reg which writed from us
static u16 WM8978_REGVAL_TBL[58]=
{
	0X0000,0X0000,0X0000,0X0000,0X0050,0X0000,0X0140,0X0000,
	0X0000,0X0000,0X0000,0X00FF,0X00FF,0X0000,0X0100,0X00FF,
	0X00FF,0X0000,0X012C,0X002C,0X002C,0X002C,0X002C,0X0000,
	0X0032,0X0000,0X0000,0X0000,0X0000,0X0000,0X0000,0X0000,
	0X0038,0X000B,0X0032,0X0000,0X0008,0X000C,0X0093,0X00E9,
	0X0000,0X0000,0X0000,0X0000,0X0003,0X0010,0X0010,0X0100,
	0X0100,0X0002,0X0001,0X0001,0X0039,0X0039,0X0039,0X0039,
	0X0001,0X0001
}; 

//wm8978_init
u8 wm8978_init(void)
{
	u8 res = 0;
	res |=WM8978_write_reg(0,0);	//sotf reset wm8978
#if 1 
	res |= WM8978_write_reg(49,0x3<<1); //R49,TSDEN,
	//record
	res |=WM8978_write_reg(1, (1<<8 )|(1 << 3) | (3 << 0)|(1<<2)); //set VMIDSEL , BUFIOEN , BUFDCOPEN
	res |=WM8978_write_reg(6,(0<<8)); //set mclk,
	res |=WM8978_write_reg(44,(1<<2)|(1<<6)|(0<<1)|(0<<5));  //enable R2 LIN RIN
	res |= WM8978_write_reg(45,(0x00)|(1<<6));   //L PGA , PGAMUTEL ,
	res |= WM8978_write_reg(46,(0x100)|(1<<6));   //R PGA , PGAMUTER ,
	res |=WM8978_write_reg(47,(7<<4));  //PGABOOSTL open 20dB gain
	res |=WM8978_write_reg(48,(7<<4));  //PGABOOSTR open 20dB gain
	res |=WM8978_write_reg(2,(1<<4)|(1<<5)|(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<7)|(1<<(u16)8)); //boost enable R and L , ADV enbale R and L ,
	//play
	res |=WM8978_write_reg(3,(1<<0)|(1<<1)|(1<<2)|(1<<3)); //enable DAC LR , enable LMIXEN and RMIXEN
	res |=WM8978_write_reg(50,(1<<0)); //DACL2LMIX
	
	res |=WM8978_write_reg(51,(1<<0)); //DACR2RMIX
	res |= WM8978_write_reg(14,(1<<3)|(0<<8)|(0<<7));   //R14,ADC 128, if want low power set to 0 , filter ,
	res |= WM8978_write_reg(10,1<<3);   //R14,DAC 128, if want low power set to 0
    res |= WM8978_write_reg(52,0xf);
    res |= WM8978_write_reg(53,0x10f);
	res |=WM8978_write_reg(5,0);
	res |=WM8978_write_reg(7,3<<1);
//	res |=WM8978_write_reg(0,0);
//	res |=WM8978_write_reg(0,0);

//	WM8978_HPvol_Set(20,20);
	WM8978_I2S_Cfg(2,0);		// set reg 4
	

#elif 0 

	res |= WM8978_write_reg(1, (1<<8 )|(3 << 3) | (3 << 0)|(1<<2));	//R1,MICEN set to 1,enable MIC , BIASEN set 1, VMIDSEL[1:0] set to :11(5K)
//	res |= WM8978_write_reg(1, (1<<8 )|(1 << 3) | (3 << 0)|(1<<2));	//
	res |= WM8978_write_reg(2,((u16)1<<8)|((u16)1<<7)|(0<<6)|(0x3<<0)|(3<<4));	//R2,ROUT1,LOUT1 output enable (we can use headphone),BOOSTENR , BOOSTENL enable
	res |= WM8978_write_reg(3,(1<<6)|(1<<5)|(1<<3)|(1<<2)|(1<<1)|(1));	//R3,LOUT2,ROUT2 ouput enable, then can use speaker, RMIX LMIX enable
	res |= WM8978_write_reg(4,(0x10<<3)|(0x00<<5));
	res |= WM8978_write_reg(6,0);		//R6,MCLK is provided from outside
	res |= WM8978_write_reg(10,1<<3);	//R10,SOFTMUTE
	res |= WM8978_write_reg(14,1<<3);	//R14,ADC 128

	res |= WM8978_write_reg(49,0x3<<1);	//R49,TSDEN,

//	res |= WM8978_write_reg(50,1);	//R49,TSDEN,
//	res |= WM8978_write_reg(51,1);	//R49,TSDEN,
	
//	res |= WM8978_write_reg(44,0);	//R43,INVROUT2
	WM8978_Input_Cfg(0,1,0);
	WM8978_HPvol_Set(10,10);
	res |= WM8978_write_reg(44,(1<<6)|(1<<2));	//R47
		WM8978_I2S_Cfg(2,0);		//设置I2S接口模式
//	res |= WM8978_write_reg(47,7<<4);	//R47
//	res |= WM8978_write_reg(48,7<<4);	//R48
//	res |= WM8978_write_reg(45,0x3f);	//R47
//	res |= WM8978_write_reg(46,0x3f);	//R48
//	res |= WM8978_write_reg(46,0x100);	//R48
//recorder
#endif
#if 0
	WM8978_write_reg(0,0);	
	WM8978_write_reg(1,0x001b);	
	WM8978_write_reg(2,0x01b0);	
	WM8978_write_reg(3,0x006c);	
	WM8978_write_reg(6,0x0000);	
	WM8978_write_reg(43,1<<4);	
	WM8978_write_reg(47,1<<8);	
	WM8978_write_reg(48,1<<8);	
	WM8978_write_reg(49,1<<1);	
	WM8978_write_reg(10,1<<3);	
	WM8978_write_reg(14,1<<3);	
#endif
	return res;
}

void WM8978_PlayMode(void)
{
		printf("playmode start\r\n");
#if 0
		WM8978_ADDA_Cfg(1,1);		//开启DAC
		//WM8978_ADDA_Cfg(1,0);		//开启DAC
		WM8978_Input_Cfg(0,1,0);	//关闭输入通道
		WM8978_Output_Cfg(1,1);		//开启DAC输出
		WM8978_HPvol_Set(20,20);
		WM8978_SPKvol_Set(0x3F);
		WM8978_MIC_Gain(50);
		WM8978_I2S_Cfg(2,0);		//设置I2S接口模式
#endif
//		printf("playmode end\r\n");
//		WM8978_ADDA_Cfg(1,0);		//开启DAC
//		WM8978_Input_Cfg(0,0,0);	//关闭输入通道
//		WM8978_Output_Cfg(1,0);		//开启DAC输出
//		WM8978_HPvol_Set(ucLHPvol,ucRHPvol);
//		WM8978_SPKvol_Set(ucSPKvol);
//		WM8978_MIC_Gain(0);
//		WM8978_I2S_Cfg(2,0);		//设置I2S接口模式

		//record
		WM8978_ADDA_Cfg(1,1);		//开启ADC
		WM8978_Input_Cfg(0,1,0);	//开启输入通道(MIC)
		WM8978_Output_Cfg(1,0);		//开启BYPASS输出
		WM8978_HPvol_Set(20,20);
		WM8978_SPKvol_Set(0);
		WM8978_MIC_Gain(0);		//MIC增益设置(多年实战下来的值)
		WM8978_I2S_Cfg(2,0);		//飞利浦标准,16位数据长度
}


//WM8978 write reg
u8 WM8978_write_reg(u8 reg,u16 val)
{ 
	u8 ack;
	printf("reg = %d  value = 0x%x\r\n",reg,val);	
	app_i2c_start();
	
	ack = app_i2c_senddata8((WM8978_ADDR<<1)|0);  //WM8978 0b00110100
	if(ack)return 1;	
	
	ack = app_i2c_senddata8((reg<<1)|((val>>8)&0X01));
	if(ack)return 2;
	
	ack = app_i2c_senddata8(val&0XFF);
	if(ack)return 3;

	app_i2c_stop();
	
	WM8978_REGVAL_TBL[reg]=val;	
	
	return 0;	
}  
//WM8978读寄存器
//就是读取本地寄存器值缓冲区内的对应值
//reg:寄存器地址 
//返回值:寄存器值
u16 WM8978_Read_Reg(u8 reg)
{  
	return WM8978_REGVAL_TBL[reg];	
} 

u8 WM8978_Update_Reg(u8 reg,u16 val)
{
	val = WM8978_Read_Reg(reg)|val;
	WM8978_write_reg(reg,val);
}

//WM8978 DAC/ADC配置
//adcen:adc使能(1)/关闭(0)
//dacen:dac使能(1)/关闭(0)
void WM8978_ADDA_Cfg(u8 dacen,u8 adcen)
{
	u16 regval;
	regval=WM8978_Read_Reg(3);	//读取R3
	if(dacen)regval|=3<<0;		//R3最低2个位设置为1,开启DACR&DACL
	else regval&=~(3<<0);		//R3最低2个位清零,关闭DACR&DACL.
	WM8978_write_reg(3,regval);	//设置R3
	regval=WM8978_Read_Reg(2);	//读取R2
	if(adcen)regval|=3<<0;		//R2最低2个位设置为1,开启ADCR&ADCL
	else regval&=~(3<<0);		//R2最低2个位清零,关闭ADCR&ADCL.
	WM8978_write_reg(2,regval);	//设置R2	
}



//WM8978 输入通道配置 
//micen:MIC开启(1)/关闭(0)
//lineinen:Line In开启(1)/关闭(0)
//auxen:aux开启(1)/关闭(0) 
void WM8978_Input_Cfg(u8 micen,u8 lineinen,u8 auxen)
{
#if 1 
	u16 regval;  
	regval=WM8978_Read_Reg(2);	//读取R2
	if(micen)regval|=3<<2;		//开启INPPGAENR,INPPGAENL(MIC的PGA放大)
	else regval&=~(3<<2);		//关闭INPPGAENR,INPPGAENL.
 	WM8978_write_reg(2,regval);	//设置R2 
	
	regval=WM8978_Read_Reg(44);	//读取R44
	if(micen)regval|=3<<4|3<<0;	//开启LIN2INPPGA,LIP2INPGA,RIN2INPPGA,RIP2INPGA.
	else regval&=~(3<<4|3<<0);	//关闭LIN2INPPGA,LIP2INPGA,RIN2INPPGA,RIP2INPGA.
	WM8978_write_reg(44,regval);//设置R44
	
	if(lineinen)WM8978_LINEIN_Gain(63);//LINE IN 0dB增益
	else WM8978_LINEIN_Gain(0);	//关闭LINE IN
	if(auxen)WM8978_AUX_Gain(7);//AUX 6dB增益
	else WM8978_AUX_Gain(0);	//关闭AUX输入  
#endif


}
//WM8978 输出配置 
//dacen:DAC输出(放音)开启(1)/关闭(0)
//bpsen:Bypass输出(录音,包括MIC,LINE IN,AUX等)开启(1)/关闭(0) 
void WM8978_Output_Cfg(u8 dacen,u8 bpsen)
{
	u16 regval=0;
	if(dacen)regval|=1<<0;	//DAC输出使能
	if(bpsen)
	{
		regval|=1<<1;		//BYPASS使能
		regval|=5<<2;		//0dB增益
	} 
	WM8978_write_reg(50,regval);//R50设置
	WM8978_write_reg(51,regval);//R51设置 
}
//WM8978 MIC增益设置(不包括BOOST的20dB,MIC-->ADC输入部分的增益)
//gain:0~63,对应-12dB~35.25dB,0.75dB/Step
void WM8978_MIC_Gain(u8 gain)
{
	gain&=0X3F;
	WM8978_write_reg(45,gain);		//R45,左通道PGA设置 
	WM8978_write_reg(46,gain|1<<8);	//R46,右通道PGA设置
}
//WM8978 L2/R2(也就是Line In)增益设置(L2/R2-->ADC输入部分的增益)
//gain:0~7,0表示通道禁止,1~7,对应-12dB~6dB,3dB/Step
void WM8978_LINEIN_Gain(u8 gain)
{
	u16 regval;
	gain&=0X07;
	regval=WM8978_Read_Reg(47);	//读取R47
	regval&=~(7<<4);			//清除原来的设置 
 	WM8978_write_reg(47,regval|gain<<4);//设置R47
	regval=WM8978_Read_Reg(48);	//读取R48
	regval&=~(7<<4);			//清除原来的设置 
 	WM8978_write_reg(48,regval|gain<<4);//设置R48
} 
//WM8978 AUXR,AUXL(PWM音频部分)增益设置(AUXR/L-->ADC输入部分的增益)
//gain:0~7,0表示通道禁止,1~7,对应-12dB~6dB,3dB/Step
void WM8978_AUX_Gain(u8 gain)
{
	u16 regval;
	gain&=0X07;
	regval=WM8978_Read_Reg(47);	//读取R47
	regval&=~(7<<0);			//清除原来的设置 
 	WM8978_write_reg(47,regval|gain<<0);//设置R47
	regval=WM8978_Read_Reg(48);	//读取R48
	regval&=~(7<<0);			//清除原来的设置 
 	WM8978_write_reg(48,regval|gain<<0);//设置R48
}  
//设置I2S工作模式
//fmt:0,LSB(右对齐);1,MSB(左对齐);2,飞利浦标准I2S;3,PCM/DSP;
//len:0,16位;1,20位;2,24位;3,32位;  
void WM8978_I2S_Cfg(u8 fmt,u8 len)
{
	fmt&=0X03;
	len&=0X03;//限定范围
	WM8978_write_reg(4,(fmt<<3)|(len<<5));	//R4,WM8978工作模式设置	
}	

//设置耳机左右声道音量
//voll:左声道音量(0~63)
//volr:右声道音量(0~63)
void WM8978_HPvol_Set(u8 voll,u8 volr)
{
	voll&=0X3F;
	volr&=0X3F;//限定范围
	if(voll==0)voll|=1<<6;//音量为0时,直接mute
	if(volr==0)volr|=1<<6;//音量为0时,直接mute 
	WM8978_write_reg(52,voll);			//R52,耳机左声道音量设置
	WM8978_write_reg(53,volr|(1<<8));	//R53,耳机右声道音量设置,同步更新(HPVU=1)
}
//设置喇叭音量
//voll:左声道音量(0~63) 
void WM8978_SPKvol_Set(u8 volx)
{ 
	volx&=0X3F;//限定范围
	if(volx==0)volx|=1<<6;//音量为0时,直接mute 
 	WM8978_write_reg(54,volx);			//R54,喇叭左声道音量设置
	WM8978_write_reg(55,(u16)volx|(1<<8));	//R55,喇叭右声道音量设置,同步更新(SPKVU=1)	
}
//设置3D环绕声
//depth:0~15(3D强度,0最弱,15最强)
void WM8978_3D_Set(u8 depth)
{ 
	depth&=0XF;//限定范围 
 	WM8978_write_reg(41,depth);	//R41,3D环绕设置 	
}
//设置EQ/3D作用方向
//dir:0,在ADC起作用
//    1,在DAC起作用(默认)
void WM8978_EQ_3D_Dir(u8 dir)
{
	u16 regval; 
	regval=WM8978_Read_Reg(0X12);
	if(dir)regval|=1<<8;
	else regval&=~(1<<8); 
 	WM8978_write_reg(18,regval);//R18,EQ1的第9位控制EQ/3D方向
}

//设置EQ1
//cfreq:截止频率,0~3,分别对应:80/105/135/175Hz
//gain:增益,0~24,对应-12~+12dB
void WM8978_EQ1_Set(u8 cfreq,u8 gain)
{ 
	u16 regval;
	cfreq&=0X3;//限定范围 
	if(gain>24)gain=24;
	gain=24-gain;
	regval=WM8978_Read_Reg(18);
	regval&=0X100;
	regval|=cfreq<<5;	//设置截止频率 
	regval|=gain;		//设置增益	
 	WM8978_write_reg(18,regval);//R18,EQ1设置 	
}
//设置EQ2
//cfreq:中心频率,0~3,分别对应:230/300/385/500Hz
//gain:增益,0~24,对应-12~+12dB
void WM8978_EQ2_Set(u8 cfreq,u8 gain)
{ 
	u16 regval=0;
	cfreq&=0X3;//限定范围 
	if(gain>24)gain=24;
	gain=24-gain; 
	regval|=cfreq<<5;	//设置截止频率 
	regval|=gain;		//设置增益	
 	WM8978_write_reg(19,regval);//R19,EQ2设置 	
}
//设置EQ3
//cfreq:中心频率,0~3,分别对应:650/850/1100/1400Hz
//gain:增益,0~24,对应-12~+12dB
void WM8978_EQ3_Set(u8 cfreq,u8 gain)
{ 
	u16 regval=0;
	cfreq&=0X3;//限定范围 
	if(gain>24)gain=24;
	gain=24-gain; 
	regval|=cfreq<<5;	//设置截止频率 
	regval|=gain;		//设置增益	
 	WM8978_write_reg(20,regval);//R20,EQ3设置 	
}
//设置EQ4
//cfreq:中心频率,0~3,分别对应:1800/2400/3200/4100Hz
//gain:增益,0~24,对应-12~+12dB
void WM8978_EQ4_Set(u8 cfreq,u8 gain)
{ 
	u16 regval=0;
	cfreq&=0X3;//限定范围 
	if(gain>24)gain=24;
	gain=24-gain; 
	regval|=cfreq<<5;	//设置截止频率 
	regval|=gain;		//设置增益	
 	WM8978_write_reg(21,regval);//R21,EQ4设置 	
}
//设置EQ5
//cfreq:中心频率,0~3,分别对应:5300/6900/9000/11700Hz
//gain:增益,0~24,对应-12~+12dB
void WM8978_EQ5_Set(u8 cfreq,u8 gain)
{ 
	u16 regval=0;
	cfreq&=0X3;//限定范围 
	if(gain>24)gain=24;
	gain=24-gain; 
	regval|=cfreq<<5;	//设置截止频率 
	regval|=gain;		//设置增益	
 	WM8978_write_reg(22,regval);//R22,EQ5设置 	
}

