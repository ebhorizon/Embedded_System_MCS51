#include <reg52.h>
#include "74xx595.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

// 行选
u8 code LedRow[]       = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
// 列选：中
u8 code LedCol_zhong[] = {0x18,0xFF,0xDB,0xDB,0xFF,0xDB,0x18,0x18};
// 列选：央
u8 code LedCol_yang[]  = {0x18,0x7C,0x5A,0x5A,0xFF,0x38,0x6C,0xC7};

void Delay(u16 i)
{
	while(i--);
}

void main()
{	
	// 规定自下到上，自右到左为自高到低
	
	u8 i, j;	// 8位数据循环用
	u16 stop;	// 视觉停留刷新用
	u8 temp[2];	// 保存显示数组
	
	while(1)
	{		
		// 循环亮灯
		for(i = 0; i < 8; i++)
		{
			for(j = 0; j < 8; j++)
			{
				// 这个行选每次都要初始化的
				temp[1] = 0x01 << i;
				temp[0] = ~(~0xFE << j);
				_74XX595_SendByte(2, temp);
				Delay(30000);
			}
		}

		// 显示“中”
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
		
		// 显示“央”
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