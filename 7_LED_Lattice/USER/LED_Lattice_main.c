#include <reg52.h>
#include "74xx595.h"

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

// ��ѡ
u8 code LedRow[]       = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
// ��ѡ����
u8 code LedCol_zhong[] = {0x18,0xFF,0xDB,0xDB,0xFF,0xDB,0x18,0x18};
// ��ѡ����
u8 code LedCol_yang[]  = {0x18,0x7C,0x5A,0x5A,0xFF,0x38,0x6C,0xC7};

void Delay(u16 i)
{
	while(i--);
}

void main()
{	
	// �涨���µ��ϣ����ҵ���Ϊ�Ըߵ���
	
	u8 i, j;	// 8λ����ѭ����
	u16 stop;	// �Ӿ�ͣ��ˢ����
	u8 temp[2];	// ������ʾ����
	
	while(1)
	{		
		// ѭ������
		for(i = 0; i < 8; i++)
		{
			for(j = 0; j < 8; j++)
			{
				// �����ѡÿ�ζ�Ҫ��ʼ����
				temp[1] = 0x01 << i;
				temp[0] = ~(~0xFE << j);
				_74XX595_SendByte(2, temp);
				Delay(30000);
			}
		}

		// ��ʾ���С�
		for(stop = 100; stop > 0; stop--)
		{
			for(i = 0; i < 8; i++)
			{
				temp[0] = ~LedCol_zhong[i];
				temp[1] = LedRow[i];
				_74XX595_SendByte(2, temp);
				Delay(10);
			}
		}
		
		// ��ʾ���롱
		for(stop = 100; stop > 0; stop--)
		{
			for(i = 0; i < 8; i++)
			{
				temp[0] = ~LedCol_yang[i];
				temp[1] = LedRow[i];
				_74XX595_SendByte(2, temp);
				Delay(10);
			}
		}
	}
}