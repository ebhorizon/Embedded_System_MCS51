#include <reg52.h>
#include "key.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

// 定义从左到右对应位置的LED
#define LEDS P0

void main()
{
	u8 keyVal = 0;
	
	KeyInit();
	LEDS = 0x00;
	while(1)
	{
		// 检测按键是否发生，返回对应的键值
		keyVal = KeyScan();
		if(keyVal)
		{
			LEDS = 0x01 << (keyVal - 1);
		}
    } 
}