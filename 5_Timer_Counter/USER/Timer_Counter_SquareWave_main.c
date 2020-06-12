#include <reg52.h>

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

// ���巽����Ƶ�ʣ�8Hz ~ 500kHz
#define SW_FREQ 100

/* 1. ʹ��12MHz����ʱ������Ϊ1/12us����������Ϊ(12 * 1 / 12) = 1us
   2. TH = (2^16 - HalfPeriod) / (2^8) = (65536 - HalfPeriod) / 256
   3. TL = (2^16 - HalfPeriod) % (2^8) = (65536 - HalfPeriod) % 256 */
u8 TH_Init = (65536 - 1000000 / SW_FREQ / 2) / 256;
u8 TL_Init = (65536 - 1000000 / SW_FREQ / 2) % 256;

// ���巽�������
sbit SW_Out = P1^0;

// ��ʱ/������0�ĳ�ʼ������
void TINT0_Init()
{
	/* ��ʱ��0��������ʽ1���������ֹ��ֲ��ʱ��Ӱ��������ʱ��
	   ��ʽ1��16λ��1������ */
	TMOD |= 0x01;
	
	// �򿪶�ʱ��0
	TR0 = 1;
	
	// �˴�ע�⣬������Ҫ��װ�أ���Ҫ�ó���������
	TH0 = TH_Init;
	TL0 = TL_Init;
	
	// ��ʱ��0�жϺ����жϿ��ش�
	ET0 = 1;
	EA  = 1;
}

void main()
{
	TINT0_Init();
	SW_Out = 1;
	while(1);
}

void TINT0() interrupt 1
{
	// ��װ��
	TH0 = TH_Init;
	TL0 = TL_Init;
	
	// ��ƽ��ת
	SW_Out = ~SW_Out;
}