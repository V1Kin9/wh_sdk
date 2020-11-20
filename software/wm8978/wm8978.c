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
		WM8978_I2S_Cfg(2,0);		//����I2S�ӿ�ģʽ
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
		WM8978_ADDA_Cfg(1,1);		//����DAC
		//WM8978_ADDA_Cfg(1,0);		//����DAC
		WM8978_Input_Cfg(0,1,0);	//�ر�����ͨ��
		WM8978_Output_Cfg(1,1);		//����DAC���
		WM8978_HPvol_Set(20,20);
		WM8978_SPKvol_Set(0x3F);
		WM8978_MIC_Gain(50);
		WM8978_I2S_Cfg(2,0);		//����I2S�ӿ�ģʽ
#endif
//		printf("playmode end\r\n");
//		WM8978_ADDA_Cfg(1,0);		//����DAC
//		WM8978_Input_Cfg(0,0,0);	//�ر�����ͨ��
//		WM8978_Output_Cfg(1,0);		//����DAC���
//		WM8978_HPvol_Set(ucLHPvol,ucRHPvol);
//		WM8978_SPKvol_Set(ucSPKvol);
//		WM8978_MIC_Gain(0);
//		WM8978_I2S_Cfg(2,0);		//����I2S�ӿ�ģʽ

		//record
		WM8978_ADDA_Cfg(1,1);		//����ADC
		WM8978_Input_Cfg(0,1,0);	//��������ͨ��(MIC)
		WM8978_Output_Cfg(1,0);		//����BYPASS���
		WM8978_HPvol_Set(20,20);
		WM8978_SPKvol_Set(0);
		WM8978_MIC_Gain(0);		//MIC��������(����ʵս������ֵ)
		WM8978_I2S_Cfg(2,0);		//�����ֱ�׼,16λ���ݳ���
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
//WM8978���Ĵ���
//���Ƕ�ȡ���ؼĴ���ֵ�������ڵĶ�Ӧֵ
//reg:�Ĵ�����ַ 
//����ֵ:�Ĵ���ֵ
u16 WM8978_Read_Reg(u8 reg)
{  
	return WM8978_REGVAL_TBL[reg];	
} 

u8 WM8978_Update_Reg(u8 reg,u16 val)
{
	val = WM8978_Read_Reg(reg)|val;
	WM8978_write_reg(reg,val);
}

//WM8978 DAC/ADC����
//adcen:adcʹ��(1)/�ر�(0)
//dacen:dacʹ��(1)/�ر�(0)
void WM8978_ADDA_Cfg(u8 dacen,u8 adcen)
{
	u16 regval;
	regval=WM8978_Read_Reg(3);	//��ȡR3
	if(dacen)regval|=3<<0;		//R3���2��λ����Ϊ1,����DACR&DACL
	else regval&=~(3<<0);		//R3���2��λ����,�ر�DACR&DACL.
	WM8978_write_reg(3,regval);	//����R3
	regval=WM8978_Read_Reg(2);	//��ȡR2
	if(adcen)regval|=3<<0;		//R2���2��λ����Ϊ1,����ADCR&ADCL
	else regval&=~(3<<0);		//R2���2��λ����,�ر�ADCR&ADCL.
	WM8978_write_reg(2,regval);	//����R2	
}



//WM8978 ����ͨ������ 
//micen:MIC����(1)/�ر�(0)
//lineinen:Line In����(1)/�ر�(0)
//auxen:aux����(1)/�ر�(0) 
void WM8978_Input_Cfg(u8 micen,u8 lineinen,u8 auxen)
{
#if 1 
	u16 regval;  
	regval=WM8978_Read_Reg(2);	//��ȡR2
	if(micen)regval|=3<<2;		//����INPPGAENR,INPPGAENL(MIC��PGA�Ŵ�)
	else regval&=~(3<<2);		//�ر�INPPGAENR,INPPGAENL.
 	WM8978_write_reg(2,regval);	//����R2 
	
	regval=WM8978_Read_Reg(44);	//��ȡR44
	if(micen)regval|=3<<4|3<<0;	//����LIN2INPPGA,LIP2INPGA,RIN2INPPGA,RIP2INPGA.
	else regval&=~(3<<4|3<<0);	//�ر�LIN2INPPGA,LIP2INPGA,RIN2INPPGA,RIP2INPGA.
	WM8978_write_reg(44,regval);//����R44
	
	if(lineinen)WM8978_LINEIN_Gain(63);//LINE IN 0dB����
	else WM8978_LINEIN_Gain(0);	//�ر�LINE IN
	if(auxen)WM8978_AUX_Gain(7);//AUX 6dB����
	else WM8978_AUX_Gain(0);	//�ر�AUX����  
#endif


}
//WM8978 ������� 
//dacen:DAC���(����)����(1)/�ر�(0)
//bpsen:Bypass���(¼��,����MIC,LINE IN,AUX��)����(1)/�ر�(0) 
void WM8978_Output_Cfg(u8 dacen,u8 bpsen)
{
	u16 regval=0;
	if(dacen)regval|=1<<0;	//DAC���ʹ��
	if(bpsen)
	{
		regval|=1<<1;		//BYPASSʹ��
		regval|=5<<2;		//0dB����
	} 
	WM8978_write_reg(50,regval);//R50����
	WM8978_write_reg(51,regval);//R51���� 
}
//WM8978 MIC��������(������BOOST��20dB,MIC-->ADC���벿�ֵ�����)
//gain:0~63,��Ӧ-12dB~35.25dB,0.75dB/Step
void WM8978_MIC_Gain(u8 gain)
{
	gain&=0X3F;
	WM8978_write_reg(45,gain);		//R45,��ͨ��PGA���� 
	WM8978_write_reg(46,gain|1<<8);	//R46,��ͨ��PGA����
}
//WM8978 L2/R2(Ҳ����Line In)��������(L2/R2-->ADC���벿�ֵ�����)
//gain:0~7,0��ʾͨ����ֹ,1~7,��Ӧ-12dB~6dB,3dB/Step
void WM8978_LINEIN_Gain(u8 gain)
{
	u16 regval;
	gain&=0X07;
	regval=WM8978_Read_Reg(47);	//��ȡR47
	regval&=~(7<<4);			//���ԭ�������� 
 	WM8978_write_reg(47,regval|gain<<4);//����R47
	regval=WM8978_Read_Reg(48);	//��ȡR48
	regval&=~(7<<4);			//���ԭ�������� 
 	WM8978_write_reg(48,regval|gain<<4);//����R48
} 
//WM8978 AUXR,AUXL(PWM��Ƶ����)��������(AUXR/L-->ADC���벿�ֵ�����)
//gain:0~7,0��ʾͨ����ֹ,1~7,��Ӧ-12dB~6dB,3dB/Step
void WM8978_AUX_Gain(u8 gain)
{
	u16 regval;
	gain&=0X07;
	regval=WM8978_Read_Reg(47);	//��ȡR47
	regval&=~(7<<0);			//���ԭ�������� 
 	WM8978_write_reg(47,regval|gain<<0);//����R47
	regval=WM8978_Read_Reg(48);	//��ȡR48
	regval&=~(7<<0);			//���ԭ�������� 
 	WM8978_write_reg(48,regval|gain<<0);//����R48
}  
//����I2S����ģʽ
//fmt:0,LSB(�Ҷ���);1,MSB(�����);2,�����ֱ�׼I2S;3,PCM/DSP;
//len:0,16λ;1,20λ;2,24λ;3,32λ;  
void WM8978_I2S_Cfg(u8 fmt,u8 len)
{
	fmt&=0X03;
	len&=0X03;//�޶���Χ
	WM8978_write_reg(4,(fmt<<3)|(len<<5));	//R4,WM8978����ģʽ����	
}	

//���ö���������������
//voll:����������(0~63)
//volr:����������(0~63)
void WM8978_HPvol_Set(u8 voll,u8 volr)
{
	voll&=0X3F;
	volr&=0X3F;//�޶���Χ
	if(voll==0)voll|=1<<6;//����Ϊ0ʱ,ֱ��mute
	if(volr==0)volr|=1<<6;//����Ϊ0ʱ,ֱ��mute 
	WM8978_write_reg(52,voll);			//R52,������������������
	WM8978_write_reg(53,volr|(1<<8));	//R53,������������������,ͬ������(HPVU=1)
}
//������������
//voll:����������(0~63) 
void WM8978_SPKvol_Set(u8 volx)
{ 
	volx&=0X3F;//�޶���Χ
	if(volx==0)volx|=1<<6;//����Ϊ0ʱ,ֱ��mute 
 	WM8978_write_reg(54,volx);			//R54,������������������
	WM8978_write_reg(55,(u16)volx|(1<<8));	//R55,������������������,ͬ������(SPKVU=1)	
}
//����3D������
//depth:0~15(3Dǿ��,0����,15��ǿ)
void WM8978_3D_Set(u8 depth)
{ 
	depth&=0XF;//�޶���Χ 
 	WM8978_write_reg(41,depth);	//R41,3D�������� 	
}
//����EQ/3D���÷���
//dir:0,��ADC������
//    1,��DAC������(Ĭ��)
void WM8978_EQ_3D_Dir(u8 dir)
{
	u16 regval; 
	regval=WM8978_Read_Reg(0X12);
	if(dir)regval|=1<<8;
	else regval&=~(1<<8); 
 	WM8978_write_reg(18,regval);//R18,EQ1�ĵ�9λ����EQ/3D����
}

//����EQ1
//cfreq:��ֹƵ��,0~3,�ֱ��Ӧ:80/105/135/175Hz
//gain:����,0~24,��Ӧ-12~+12dB
void WM8978_EQ1_Set(u8 cfreq,u8 gain)
{ 
	u16 regval;
	cfreq&=0X3;//�޶���Χ 
	if(gain>24)gain=24;
	gain=24-gain;
	regval=WM8978_Read_Reg(18);
	regval&=0X100;
	regval|=cfreq<<5;	//���ý�ֹƵ�� 
	regval|=gain;		//��������	
 	WM8978_write_reg(18,regval);//R18,EQ1���� 	
}
//����EQ2
//cfreq:����Ƶ��,0~3,�ֱ��Ӧ:230/300/385/500Hz
//gain:����,0~24,��Ӧ-12~+12dB
void WM8978_EQ2_Set(u8 cfreq,u8 gain)
{ 
	u16 regval=0;
	cfreq&=0X3;//�޶���Χ 
	if(gain>24)gain=24;
	gain=24-gain; 
	regval|=cfreq<<5;	//���ý�ֹƵ�� 
	regval|=gain;		//��������	
 	WM8978_write_reg(19,regval);//R19,EQ2���� 	
}
//����EQ3
//cfreq:����Ƶ��,0~3,�ֱ��Ӧ:650/850/1100/1400Hz
//gain:����,0~24,��Ӧ-12~+12dB
void WM8978_EQ3_Set(u8 cfreq,u8 gain)
{ 
	u16 regval=0;
	cfreq&=0X3;//�޶���Χ 
	if(gain>24)gain=24;
	gain=24-gain; 
	regval|=cfreq<<5;	//���ý�ֹƵ�� 
	regval|=gain;		//��������	
 	WM8978_write_reg(20,regval);//R20,EQ3���� 	
}
//����EQ4
//cfreq:����Ƶ��,0~3,�ֱ��Ӧ:1800/2400/3200/4100Hz
//gain:����,0~24,��Ӧ-12~+12dB
void WM8978_EQ4_Set(u8 cfreq,u8 gain)
{ 
	u16 regval=0;
	cfreq&=0X3;//�޶���Χ 
	if(gain>24)gain=24;
	gain=24-gain; 
	regval|=cfreq<<5;	//���ý�ֹƵ�� 
	regval|=gain;		//��������	
 	WM8978_write_reg(21,regval);//R21,EQ4���� 	
}
//����EQ5
//cfreq:����Ƶ��,0~3,�ֱ��Ӧ:5300/6900/9000/11700Hz
//gain:����,0~24,��Ӧ-12~+12dB
void WM8978_EQ5_Set(u8 cfreq,u8 gain)
{ 
	u16 regval=0;
	cfreq&=0X3;//�޶���Χ 
	if(gain>24)gain=24;
	gain=24-gain; 
	regval|=cfreq<<5;	//���ý�ֹƵ�� 
	regval|=gain;		//��������	
 	WM8978_write_reg(22,regval);//R22,EQ5���� 	
}

