#include <reg52.h>
#include "74xx164.h"
#include "1seg_74xx164.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

void Delay(u16 t)
{
	while(t--);
}

void main()
{
	u8 i;
	
	_74XX164_Disable();
	_74XX164_Enable();
	
	while(1)
	{
		for(i = 0; i < 18; i++)
		{
			LED_1Seg_Display(i, 0);
			Delay(60000);
			Delay(60000);
		}
	}
}
