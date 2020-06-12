/* ע�⣬ʹ��74xx138оƬ�������������������ֻ�����ڹ�������ܣ������������Ҫ���������ܵ� */

#include <reg52.h>
#include "8seg_CC_74xx138.h"

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// ��ʾһλ���λ��0 ~ F��С������˸
void Dis1Bit()
{
	u8 i, disCode[8] = "        ";
	u16 t;
	
	for(i = 0; i < 16; i++)
	{
		if(i >= 0 && i <= 9) disCode[7] = '0' + i;
		else				 disCode[7] = 'A' + i - 10;
		
		// ���forѭ��������ʱ
		for(t = 200; t > 0; t--)
		{
			LED_8Seg_Display(disCode, !(i % 2 == 0));
		}
	}
}

// ��ʾȫ��λ��0 ~ F��С������˸
void Dis8Bit()
{
	u8 i, disCode[8];
	u16 t;
	
	for(i = 0; i < 16; i++)
	{
		if(i >= 0 && i <= 9)
		{
			for(t = 0; t < 8; t++) disCode[t] = '0' + i;
		}
		else
		{
			for(t = 0; t < 8; t++) disCode[t] = 'A' + i - 10;
		}	
		
		// ���forѭ��������ʱ
		for(t = 200; t > 0; t--)
		{
			LED_8Seg_Display(disCode, (i % 2 == 0 ? 0x00 : 0xFF));
		}
	}
}

void main()
{
	while(1)
	{
		Dis1Bit();
		Dis8Bit();
	}
}