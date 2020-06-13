#include <reg52.h>
#include "key.h"
#include "uln2003.h"

// ULN2003ֻ�����������Ե����

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

void main()
{
	u8 DC_Motor = 0;
	
	KeyInit();					// ������ʼ��
	ULN2003_DCBA_Switch(0x00);	// оƬ�������ų�ʼ���ر�
	
	while(1)
	{
		if(KeyScan() == 1)		// K1����
		{
			DC_Motor = !DC_Motor;
			ULN2003_DCBA_Switch(0x00 | DC_Motor);
		}
	}
}