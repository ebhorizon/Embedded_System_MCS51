<<<<<<< HEAD
/* 简易电子表 */

#include <reg52.h>
#include "74xx138.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif
#ifndef u32
#define u32 unsigned long
#endif

#define SEG_SEL P0					// 段选引脚

//--下面两个宏定义便于调试--//
#define TIMING			50000		// 定时器的计时时间，默认为50ms(50000)
#define TIMING_COUNT	20			// 定时器的计时个数，默认为20

//--共阴数码管段选，从0到9--//
u8 code segCC_SegSel[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
//--数码管显示数据，00-00-00--//
u8 DisplayCode[8]        = {0x3f, 0x3f, 0x40, 0x3f, 0x3f, 0x40, 0x3f, 0x3f};
//--存储时间戳的变量--//
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
		
		// 数码管消隐
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
	/* 定时器0，工作方式1，或运算防止移植的时候影响其他定时器
	   方式1：16位加1计数器 */
	TMOD |= 0x01;
	
	// 打开定时器0
	TR0 = 1;
	
	/* 1. 使用12MHz晶振，时钟周期为1/12us，机器周期为(12 * 1 / 12) = 1us
	   2. 计数50ms = 50000us
	   3. TH = (2^16 - 50000) / (2^8) = 15536 / 256
	   4. TL = (2^16 - 50000) % (2^8) = 15536 % 256
	   5. 1s = 1000ms = 20 * 50ms */
	TH0 = (65536 - TIMING) / 256;
	TL0 = (65536 - TIMING) % 256;
	
	// 定时器0中断和总中断开关打开
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
	// 1s需要记录20个50ms
	static u8 tCount = 0;
	
	// 定时器0高低位的赋值
	TH0 = (65536 - TIMING) / 256;
	TL0 = (65536 - TIMING) % 256;
	
	// 累加并判断是否1s
	if(++tCount == TIMING_COUNT)
	{
		// 累加并判断，时间为24-00-00 = 86400时清零
		if(++timestamp == 86400) timestamp = 0;
		// 重置1s计数
		tCount = 0;
	}
=======
/* 简易电子表 */

#include <reg52.h>
#include "74xx138.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif
#ifndef u32
#define u32 unsigned long
#endif

#define SEG_SEL P0					// 段选引脚

//--下面两个宏定义便于调试--//
#define TIMING			50000		// 定时器的计时时间，默认为50ms(50000)
#define TIMING_COUNT	20			// 定时器的计时个数，默认为20

//--共阴数码管段选，从0到9--//
u8 code segCC_SegSel[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
//--数码管显示数据，00-00-00--//
u8 DisplayCode[8]        = {0x3f, 0x3f, 0x40, 0x3f, 0x3f, 0x40, 0x3f, 0x3f};
//--存储时间戳的变量--//
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
		
		// 数码管消隐
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
	/* 定时器0，工作方式1，或运算防止移植的时候影响其他定时器
	   方式1：16位加1计数器 */
	TMOD |= 0x01;
	
	// 打开定时器0
	TR0 = 1;
	
	/* 1. 使用12MHz晶振，时钟周期为1/12us，机器周期为(12 * 1 / 12) = 1us
	   2. 计数50ms = 50000us
	   3. TH = (2^16 - 50000) / (2^8) = 15536 / 256
	   4. TL = (2^16 - 50000) % (2^8) = 15536 % 256
	   5. 1s = 1000ms = 20 * 50ms */
	TH0 = (65536 - TIMING) / 256;
	TL0 = (65536 - TIMING) % 256;
	
	// 定时器0中断和总中断开关打开
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
	// 1s需要记录20个50ms
	static u8 tCount = 0;
	
	// 定时器0高低位的赋值
	TH0 = (65536 - TIMING) / 256;
	TL0 = (65536 - TIMING) % 256;
	
	// 累加并判断是否1s
	if(++tCount == TIMING_COUNT)
	{
		// 累加并判断，时间为24-00-00 = 86400时清零
		if(++timestamp == 86400) timestamp = 0;
		// 重置1s计数
		tCount = 0;
	}
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
}