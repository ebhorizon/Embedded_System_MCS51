/* 0	1	2	3
   4	5	6	7
   8	9	A	B
   C	D	E	F */

#include <reg52.h>
#include "1seg.h"
#include "4gpio_matrix_key.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

void main()
{
	u8 keyVal;
	
	// LED_1Seg_Display(8, 1);
	while(1)
	{
		keyVal = GPIOKeyScanAgain();
		if(keyVal) LED_1Seg_Display(keyVal - 1, 0);
	}
}