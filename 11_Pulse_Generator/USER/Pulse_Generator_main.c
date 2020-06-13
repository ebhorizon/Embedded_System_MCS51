// 使用NE555脉冲发生芯片产生脉冲
// 使用LCD1602显示

#include <reg52.h>
#include "lcd1602.h"

// 定义常用类型
#ifndef u8
#define u8  unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif
#ifndef u32
#define u32 unsigned long
#endif

// 定义LCD1602显示的文字
u8 code displayWords1[16] = "Cymometer       ";
u8 code displayWords2[16] = "Freq:         Hz";
u32 Freq = 0;

void TINT0_Init()
{
	// 定时器T0做定时器，工作方式1（16位定时器）
	TMOD |= 0x01;
	
	// 设置定时器晶振为12MHZ时定时50ms
	TH0   = 15536 / 256;
	TL0   = 15536 % 256;
	
	ET0   = 1;
	EA    = 1;
	
	TR0   = 1;
}

void TINT1_Init()
{
	// 定时器T1做计数器，工作方式1（16位定时器）
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
	
	// 显示初始化
	LCD1602_SetLine(1);
	for(i = 0; i < 16; i++)	LCD1602_WriteDat(displayWords1[i]);
	LCD1602_SetLine(2);
	for(i = 0; i < 16; i++) LCD1602_WriteDat(displayWords2[i]);
	
	while(1)
	{
		if(!TR0)						// 定时结束
		{
			Freq += (TL1 + TH1 * 256);	// 加上未计满的数
			
			disVal[0] = '0' + Freq % 1000000 / 100000;
			disVal[1] = '0' + Freq % 100000 / 10000;
			disVal[2] = '0' + Freq % 10000 / 1000;
			disVal[3] = '0' + Freq % 1000 / 100;
			disVal[4] = '0' + Freq % 100 / 10;
			disVal[5] = '0' + Freq % 10;
			for(i = 0; i < 5; i++)		// 替换最高位的0为空格直到遇到不是0
			{
				if(disVal[i] == '0') disVal[i] = ' ';			
				else break;		
			}
			
			// 从48H开始写6位，刚好“Hz”为54H和55H
			LCD1602_WriteCmd(0xC8);
			for(i = 0; i < 6; i++) LCD1602_WriteDat(disVal[i]);
			
			// 显示完记得清零
			Freq = 0;
			TH1  = 0;
			TL1  = 0;
			
			// 重新开始定时和计数
			TR0  = 1;					//开启定时器
			TR1  = 1;					//开启计数器
		}
	}
}

void TINT0_50ms() interrupt 1
{
	// 定时1s
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
	// 进入中断说明计数满65536
	Freq += 65536;
}