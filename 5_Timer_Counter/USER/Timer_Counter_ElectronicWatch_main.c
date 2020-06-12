<<<<<<< HEAD
/* ���׵��ӱ� */

#include <reg52.h>
#include "74xx138.h"

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif
#ifndef u32
#define u32 unsigned long
#endif

#define SEG_SEL P0					// ��ѡ����

//--���������궨����ڵ���--//
#define TIMING			50000		// ��ʱ���ļ�ʱʱ�䣬Ĭ��Ϊ50ms(50000)
#define TIMING_COUNT	20			// ��ʱ���ļ�ʱ������Ĭ��Ϊ20

//--��������ܶ�ѡ����0��9--//
u8 code segCC_SegSel[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
//--�������ʾ���ݣ�00-00-00--//
u8 DisplayCode[8]        = {0x3f, 0x3f, 0x40, 0x3f, 0x3f, 0x40, 0x3f, 0x3f};
//--�洢ʱ����ı���--//
u32 timestamp  = 0;

void Delay1ms(u16 n)
{
    u8 i, j;
    for(i = 0; i < n; i++)
		for(j = 0; j < 125; j++);
}

void SegDisplay()
{	  
	u8 i;
	
	for(i = 0; i < 8; i++)
	{
		_74XX138_SetLow(i);
		SEG_SEL = DisplayCode[i];
		Delay1ms(1);
		
		// ���������
		SEG_SEL = 0x00;
	}
}

void DisplayCode_Update()
{
	u8 disHour   = timestamp / 60 / 60;
	u8 disMinute = timestamp / 60 % 60;
	u8 disSecond = timestamp % 60;
	
	DisplayCode[0] = segCC_SegSel[disHour   / 10];
	DisplayCode[1] = segCC_SegSel[disHour   % 10];
	DisplayCode[3] = segCC_SegSel[disMinute / 10];
	DisplayCode[4] = segCC_SegSel[disMinute % 10];
	DisplayCode[6] = segCC_SegSel[disSecond / 10];
	DisplayCode[7] = segCC_SegSel[disSecond % 10];
}

void Timer0Init()
{
	/* ��ʱ��0��������ʽ1���������ֹ��ֲ��ʱ��Ӱ��������ʱ��
	   ��ʽ1��16λ��1������ */
	TMOD |= 0x01;
	
	// �򿪶�ʱ��0
	TR0 = 1;
	
	/* 1. ʹ��12MHz����ʱ������Ϊ1/12us����������Ϊ(12 * 1 / 12) = 1us
	   2. ����50ms = 50000us
	   3. TH = (2^16 - 50000) / (2^8) = 15536 / 256
	   4. TL = (2^16 - 50000) % (2^8) = 15536 % 256
	   5. 1s = 1000ms = 20 * 50ms */
	TH0 = (65536 - TIMING) / 256;
	TL0 = (65536 - TIMING) % 256;
	
	// ��ʱ��0�жϺ����жϿ��ش�
	ET0 = 1;
	EA  = 1;
}

void main()
{
	Timer0Init();
	
	while(1)
	{
		SegDisplay();
		DisplayCode_Update();
    }
}

void Timer0() interrupt 1
{
	// 1s��Ҫ��¼20��50ms
	static u8 tCount = 0;
	
	// ��ʱ��0�ߵ�λ�ĸ�ֵ
	TH0 = (65536 - TIMING) / 256;
	TL0 = (65536 - TIMING) % 256;
	
	// �ۼӲ��ж��Ƿ�1s
	if(++tCount == TIMING_COUNT)
	{
		// �ۼӲ��жϣ�ʱ��Ϊ24-00-00 = 86400ʱ����
		if(++timestamp == 86400) timestamp = 0;
		// ����1s����
		tCount = 0;
	}
=======
/* ���׵��ӱ� */

#include <reg52.h>
#include "74xx138.h"

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif
#ifndef u32
#define u32 unsigned long
#endif

#define SEG_SEL P0					// ��ѡ����

//--���������궨����ڵ���--//
#define TIMING			50000		// ��ʱ���ļ�ʱʱ�䣬Ĭ��Ϊ50ms(50000)
#define TIMING_COUNT	20			// ��ʱ���ļ�ʱ������Ĭ��Ϊ20

//--��������ܶ�ѡ����0��9--//
u8 code segCC_SegSel[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
//--�������ʾ���ݣ�00-00-00--//
u8 DisplayCode[8]        = {0x3f, 0x3f, 0x40, 0x3f, 0x3f, 0x40, 0x3f, 0x3f};
//--�洢ʱ����ı���--//
u32 timestamp  = 0;

void Delay1ms(u16 n)
{
    u8 i, j;
    for(i = 0; i < n; i++)
		for(j = 0; j < 125; j++);
}

void SegDisplay()
{	  
	u8 i;
	
	for(i = 0; i < 8; i++)
	{
		_74XX138_SetLow(i);
		SEG_SEL = DisplayCode[i];
		Delay1ms(1);
		
		// ���������
		SEG_SEL = 0x00;
	}
}

void DisplayCode_Update()
{
	u8 disHour   = timestamp / 60 / 60;
	u8 disMinute = timestamp / 60 % 60;
	u8 disSecond = timestamp % 60;
	
	DisplayCode[0] = segCC_SegSel[disHour   / 10];
	DisplayCode[1] = segCC_SegSel[disHour   % 10];
	DisplayCode[3] = segCC_SegSel[disMinute / 10];
	DisplayCode[4] = segCC_SegSel[disMinute % 10];
	DisplayCode[6] = segCC_SegSel[disSecond / 10];
	DisplayCode[7] = segCC_SegSel[disSecond % 10];
}

void Timer0Init()
{
	/* ��ʱ��0��������ʽ1���������ֹ��ֲ��ʱ��Ӱ��������ʱ��
	   ��ʽ1��16λ��1������ */
	TMOD |= 0x01;
	
	// �򿪶�ʱ��0
	TR0 = 1;
	
	/* 1. ʹ��12MHz����ʱ������Ϊ1/12us����������Ϊ(12 * 1 / 12) = 1us
	   2. ����50ms = 50000us
	   3. TH = (2^16 - 50000) / (2^8) = 15536 / 256
	   4. TL = (2^16 - 50000) % (2^8) = 15536 % 256
	   5. 1s = 1000ms = 20 * 50ms */
	TH0 = (65536 - TIMING) / 256;
	TL0 = (65536 - TIMING) % 256;
	
	// ��ʱ��0�жϺ����жϿ��ش�
	ET0 = 1;
	EA  = 1;
}

void main()
{
	Timer0Init();
	
	while(1)
	{
		SegDisplay();
		DisplayCode_Update();
    }
}

void Timer0() interrupt 1
{
	// 1s��Ҫ��¼20��50ms
	static u8 tCount = 0;
	
	// ��ʱ��0�ߵ�λ�ĸ�ֵ
	TH0 = (65536 - TIMING) / 256;
	TL0 = (65536 - TIMING) % 256;
	
	// �ۼӲ��ж��Ƿ�1s
	if(++tCount == TIMING_COUNT)
	{
		// �ۼӲ��жϣ�ʱ��Ϊ24-00-00 = 86400ʱ����
		if(++timestamp == 86400) timestamp = 0;
		// ����1s����
		tCount = 0;
	}
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
}