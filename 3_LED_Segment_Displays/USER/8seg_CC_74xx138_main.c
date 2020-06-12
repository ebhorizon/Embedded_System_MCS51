/* 注意，使用74xx138芯片不加其他器件的情况下只能用于共阴数码管，共阳数码管需要诸如三极管等 */

#include <reg52.h>
#include "8seg_CC_74xx138.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// 显示一位最低位，0 ~ F，小数点闪烁
void Dis1Bit()
{
	u8 i, disCode[8] = "        ";
	u16 t;
	
	for(i = 0; i < 16; i++)
	{
		if(i >= 0 && i <= 9) disCode[7] = '0' + i;
		else				 disCode[7] = 'A' + i - 10;
		
		// 这个for循环用来延时
		for(t = 200; t > 0; t--)
		{
			LED_8Seg_Display(disCode, !(i % 2 == 0));
		}
	}
}

// 显示全部位，0 ~ F，小数点闪烁
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
		
		// 这个for循环用来延时
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