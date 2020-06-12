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
}