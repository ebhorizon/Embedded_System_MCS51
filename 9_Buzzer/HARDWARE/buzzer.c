<<<<<<< HEAD
#include "buzzer.h"

/* ���ٵ�88����Ƶ�ʼ��㷨��
   ʮ��ƽ���ɵ�����ϵ��Ϊ2^(1 / 12) = 1.0594630944��A1Ϊ27.5Hz���Ӷ��ɵ�Ƶ��ֵ
   Ϊ�˼��ټ���ʱ������ʱ���ӳ٣��������A�ף�A1 ~ A8��Ϊ���鼴�� */
float code Freq_A[8] = {27.5, 55.0, 110.0, 220.0, 440.0, 880.0, 1760.0, 3520.0};
// ��ǰ��������ϵ��
float Coef = 1.0594630944;
u8 TINT0_H, TINT0_L;

void Buzzer_Delay_nms(u16 t)
{
	u8 i = 245;
	
	while(t--)
	{
		while(i--);
		i = 245;
		while(i--);
	}
}

// ����Ƶ�ʵĶ�ʱ����ֵ����ֵ
#if CRYSTAL == 12
u16 Buzzer_InitValue(u8 index)
{
	float Freq = 0.0;
	u8 i;
	
	Freq += Freq_A[index / 12];
	for(i = 0; i < (index - 1) % 12; i++)
	{
		Freq *= Coef;
	}
	
	return((u16)(65536 - 500000 / Freq));
}
#elif CRYSTAL == 11.0592
u16 Buzzer_InitValue(u8 index)
{
	float Freq = 0.0;
	u8 i;
	
	Freq += Freq_A[index / 12];
	for(i = 0; i < (index - 1) % 12; i++)
	{
		Freq *= Coef;
	}
	
	return((u16)(65536 - 460800 / Freq));
}
#endif

// ��ʱ��0��ʼ��
void TINT0_Init()
{
	TMOD |= 0x01;
	ET0   = 1;
	EA    = 1;
}

// ��������ʼ��
void Buzzer_Init()
{
	TINT0_Init();	// ������ʱ��
}

// ��������������
void Buzzer_Play(u8 index, u16 delay)
{
	u16 initVal = Buzzer_InitValue(index); 
	
	TINT0_H   = initVal / 256;
	TINT0_L   = initVal % 256;
	TH0       = TINT0_H;				// ��ֵ��ʱ��ʱ�䣬����Ƶ��
	TL0       = TINT0_L;
	TR0       = 1;       				// �򿪶�ʱ��0����
	Buzzer_Delay_nms(delay);
}

void TINT0() interrupt 1
{
	TR0    = 0;

	Buzzer = !Buzzer;
	TH0    = TINT0_H;
	TL0    = TINT0_L;
	
	TR0    = 1;
=======
#include "buzzer.h"

// �����Ǹ���88����ӦƵ�ʱ�����CΪC4
float code Freq[88] = 
{	/*  A,   #A,      B,       C,       #C,      D,       #D,      E,      F,       #F,      G,       #G */
/* 1 */	27.5,29.135,  30.868,  32.703,  34.648,	 36.708,  38.891,  41.203, 43.654,  46.249,  48.999,  51.913,
/* 2 */	55,  58.271,  61.735,  65.406,	69.296,	 73.416,  77.782,  82.407, 87.307,  92.499,  97.999,  103.826,
/* 3 */	110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814,174.614, 184.997, 195.998, 207.652,
/* 4 */	220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628,349.228, 369.994, 391.995, 415.305,
/* 5 */	440, 466.164, 493.883, 523.251, 554.365, 587.33,  622.254, 659.255,698.456, 739.989, 783.991, 830.609,
/* 6 */	880, 932.328, 987.767, 1046.502,1108.731,1174.659,1244.51 ,1318.51,1396.913,1479.978,1567.982,1661.219,
/* 7 */	1760,1864.655,1975.533,2093.004,2217.461,2349.318,2489.016,2637.02,2793.826,2959.955,3135.96,3322.437,
/* 8 */	3520,3729.31, 3951.066,4186.009
};

u8 TINT0_H, TINT0_L;

void Buzzer_Delay_nms(u16 t)
{
	u8 i = 245;
	
	while(t--)
	{
		while(i--);
		i = 245;
		while(i--);
	}
}

// ����Ƶ�ʵĶ�ʱ����ֵ����ֵ
#if CRYSTAL == 12
u16 Buzzer_InitValue(u8 index)
{
	return((u16)(65536 - 500000 / Freq[index]));
}
#elif CRYSTAL == 11.0592
u16 Buzzer_InitValue(u8 index)
{
	return((u16)(65536 - 460800 / Freq[index]));
}
#endif

// ��ʱ��0��ʼ��
void TINT0_Init()
{
	TMOD |= 0x01;
	ET0   = 1;
	EA    = 1;
}

// ��������ʼ��
void Buzzer_Init()
{
	TINT0_Init();	// ������ʱ��
}

// ��������������
void Buzzer_Play(u8 index, u16 delay)
{
	u16 initVal = Buzzer_InitValue(index); 
	
	TINT0_H   = initVal / 256;
	TINT0_L   = initVal % 256;
	TH0       = TINT0_H;				// ��ֵ��ʱ��ʱ�䣬����Ƶ��
	TL0       = TINT0_L;
	TR0       = 1;       				// �򿪶�ʱ��0����
	Buzzer_Delay_nms(delay);
}

void TINT0() interrupt 1
{
	TR0    = 0;

	Buzzer = !Buzzer;
	TH0    = TINT0_H;
	TL0    = TINT0_L;
	
	TR0    = 1;
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
}