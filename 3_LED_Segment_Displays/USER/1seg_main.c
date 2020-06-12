#include <reg52.h>
#include "1seg.h"

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

sbit Logic_Level = P2^7;	// ���ж��߼���ƽ������

void Delay(u16 t)
{
	while(t--);
}

void main()
{
	u8 i;
	
	while(1)
	{
		for(i = 0; i < 18; i++)
		{
			LED_1Seg_Display(i, 0);
			Delay(60000);
		}
		Delay(60000);
		
		LED_1Seg_LogicLevel(Logic_Level);
		Delay(60000);
	}
}