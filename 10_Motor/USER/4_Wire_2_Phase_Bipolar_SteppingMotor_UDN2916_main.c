#include <reg52.h>
#include "key.h"
#include "udn2916.h"

// UDN2916������������˫���Ե��

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

#define SPEED 2
// K1���ƿ��ص��Ĺ�����K2���ƿ���˫�Ĺ�����K3���ƿ��ص�˫�Ĺ���
u8 KeyStat[3] = {0, 0, 0};

void Delay(u8 t)
{ 
	u8 i, j;
  
	for(j = 0; j <= t; j++)
		for(i = 0; i <= 120; i++);
}

void KeyAction()
{
	if(KeyStat[0])				// ����
	{
		// A+ -> B+ -> A- -> B- -> A+
		
		// A+ & 0
		UDN2916_Setting(0x30);	// 00 110 000
		Delay(SPEED);
		
		// 0 & B+
		UDN2916_Setting(0x06);	// 00 000 110
		Delay(SPEED);
		
		// A- & 0
		UDN2916_Setting(0x31);	// 00 110 001
		Delay(SPEED);
		
		// 0 & B-
		UDN2916_Setting(0x0E);	// 00 001 110
		Delay(SPEED);
	}
	else if(KeyStat[1])			// ˫��
	{
		// A+B+ -> A-B+ -> A-B- -> A+B- -> A+B+
		
		// A+ & B+
		UDN2916_Setting(0x00);	// 00 000 000
		Delay(SPEED);
		
		// A- & B+
		UDN2916_Setting(0x01);	// 00 000 001
		Delay(SPEED);
		
		// A- & B-
		UDN2916_Setting(0x09);	// 00 001 001
		Delay(SPEED);
		
		// A+ & B-
		UDN2916_Setting(0x08);	// 00 001 000
		Delay(SPEED);
	}
	else if(KeyStat[2])			// ��˫��
	{
		// A+ -> A+B+ -> B+ -> A-B+ -> A- -> A-B- -> B- -> A+B- -> A+
		
		// A+ & 0
		UDN2916_Setting(0x30);	// 00 110 000
		Delay(SPEED);
		
		// A+ & B+
		UDN2916_Setting(0x00);	// 00 000 000
		Delay(SPEED);
		
		// 0 & B+
		UDN2916_Setting(0x06);	// 00 000 110
		Delay(SPEED);
		
		// A- & B+
		UDN2916_Setting(0x01);	// 00 000 001
		Delay(SPEED);
		
		// A- & 0
		UDN2916_Setting(0x31);	// 00 110 001
		Delay(SPEED);
		
		// A- & B-
		UDN2916_Setting(0x09);	// 00 001 001
		Delay(SPEED);
		
		// 0 & B-
		UDN2916_Setting(0x0E);	// 00 001 110
		Delay(SPEED);
		
		// A+ & B-
		UDN2916_Setting(0x08);	// 00 001 000
		Delay(SPEED);
	}
	else
	{
		UDN2916_Setting(0xFF);
	}
}

void main()
{
	KeyInit();					// ������ʱ����ʼ��
	UDN2916_Setting(0xFF);		// ���������ʼ��
	while(1)
	{
		switch(KeyScan())
		{
			case 1:
			{
				KeyStat[0] = !KeyStat[0];
				KeyStat[1] = 0;
				KeyStat[2] = 0;
			}
			break;
			case 2:
			{
				KeyStat[1] = !KeyStat[1];
				KeyStat[0] = 0;
				KeyStat[2] = 0;
			}
			break;
			case 3:
			{
				KeyStat[2] = !KeyStat[2];
				KeyStat[0] = 0;
				KeyStat[1] = 0;
			}
			break;
			default: break;
		}
		KeyAction();
	}
}