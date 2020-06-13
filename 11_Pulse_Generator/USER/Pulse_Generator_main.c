// ʹ��NE555���巢��оƬ��������
// ʹ��LCD1602��ʾ

#include <reg52.h>
#include "lcd1602.h"

// ���峣������
#ifndef u8
#define u8  unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif
#ifndef u32
#define u32 unsigned long
#endif

// ����LCD1602��ʾ������
u8 code displayWords1[16] = "Cymometer       ";
u8 code displayWords2[16] = "Freq:         Hz";
u32 Freq = 0;

void TINT0_Init()
{
	// ��ʱ��T0����ʱ����������ʽ1��16λ��ʱ����
	TMOD |= 0x01;
	
	// ���ö�ʱ������Ϊ12MHZʱ��ʱ50ms
	TH0   = 15536 / 256;
	TL0   = 15536 % 256;
	
	ET0   = 1;
	EA    = 1;
	
	TR0   = 1;
}

void TINT1_Init()
{
	// ��ʱ��T1����������������ʽ1��16λ��ʱ����
	TMOD |= 0x50;
	
	ET1   = 1;
	// EA    = 1;
	
	TR1   = 1;
}

void main()
{
	u8 i, disVal[6];
	
	LCD1602_Init();
	TINT0_Init();
	TINT1_Init();
	
	// ��ʾ��ʼ��
	LCD1602_SetLine(1);
	for(i = 0; i < 16; i++)	LCD1602_WriteDat(displayWords1[i]);
	LCD1602_SetLine(2);
	for(i = 0; i < 16; i++) LCD1602_WriteDat(displayWords2[i]);
	
	while(1)
	{
		if(!TR0)						// ��ʱ����
		{
			Freq += (TL1 + TH1 * 256);	// ����δ��������
			
			disVal[0] = '0' + Freq % 1000000 / 100000;
			disVal[1] = '0' + Freq % 100000 / 10000;
			disVal[2] = '0' + Freq % 10000 / 1000;
			disVal[3] = '0' + Freq % 1000 / 100;
			disVal[4] = '0' + Freq % 100 / 10;
			disVal[5] = '0' + Freq % 10;
			for(i = 0; i < 5; i++)		// �滻���λ��0Ϊ�ո�ֱ����������0
			{
				if(disVal[i] == '0') disVal[i] = ' ';			
				else break;		
			}
			
			// ��48H��ʼд6λ���պá�Hz��Ϊ54H��55H
			LCD1602_WriteCmd(0xC8);
			for(i = 0; i < 6; i++) LCD1602_WriteDat(disVal[i]);
			
			// ��ʾ��ǵ�����
			Freq = 0;
			TH1  = 0;
			TL1  = 0;
			
			// ���¿�ʼ��ʱ�ͼ���
			TR0  = 1;					//������ʱ��
			TR1  = 1;					//����������
		}
	}
}

void TINT0_50ms() interrupt 1
{
	// ��ʱ1s
	static u8 timeCount = 0;
	
	TH0 = 15536 / 256;
	TL0 = 15536 % 256;
	
	if(++timeCount == 20)
	{
		TR0 = 0;
		TR1 = 0;
		timeCount = 0;
	}
}

void TINT1_Counter() interrupt 3
{
	// �����ж�˵��������65536
	Freq += 65536;
}