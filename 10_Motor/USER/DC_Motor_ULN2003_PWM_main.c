#include <reg52.h>
#include "key.h"
#include "uln2003.h"

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

#define PWM_CYCLE 100	// PWMһ����10ms
u8 PWM_H = 50;

void INT1_Init()
{
	TMOD |= 0x10;
	TR1   = 1;
	TH1   = (65536 - 100) / 256;
	TL1   = (65536 - 100) % 256;
	ET1   = 1;
	EA    = 1;
}

void main()
{
	u8 DC_Motor = 0;
	
	INT1_Init();				// PWM��ʱ����ʼ��
	KeyInit();					// ������ʼ��
	ULN2003_DCBA_Switch(0x00);	// оƬ�������ų�ʼ���ر�
	
	while(1)
	{
		if(KeyScan() == 1)		// K1���£�����
		{
			if(PWM_H < PWM_CYCLE) PWM_H++;
		}
		
		if(KeyScan() == 2)		// K2���£�����
		{
			if(PWM_H > 0)         PWM_H--;
		}
	}
}

void INT1_100us() interrupt 3
{
	static u8 PWMCount = 0;
	
	TH1 = (65536 - 100) / 256;
	TL1 = (65536 - 100) % 256;
	
	PWMCount++;
	if(PWMCount == PWM_H) ULN2003_DCBA_Switch(0x00);
	if(PWMCount == PWM_CYCLE)
	{
		PWMCount = 0;
		if(PWM_H)	// �����Ҫ�����ٶȣ����㣩
		{
			ULN2003_DCBA_Switch(0x01);
		}
	}
}