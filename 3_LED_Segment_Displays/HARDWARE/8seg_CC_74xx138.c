<<<<<<< HEAD
#include "8seg_CC_74xx138.h"

// 共阴数码管的段选
u8 code SegSel_CC[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 
						  0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 
						  0x39, 0x5E, 0x79, 0x71, 0x80, 0x00};

void LED_8Seg_Delay(u8 t)
{
	while(t--);
}

/* 这个函数定义的是8位的显示，传入的参数：
   1. 是要显示的字符串，占8位，0~F以及不显示，字母全大写
   2. 8要显示小数点的状态，转化为16进制，从高到低
   P.S. 要显示其他字符需要修改上面段选的数组，然后补充下面if函数 */
void LED_8Seg_Display(u8 disStr[8], u8 dp)
{
	u8 i, disCode;
	
	for(i = 0; i < 8; i++)
	{
		// 位选
		_74XX138_SetLow(i);
		
		// 段选
		if(disStr[i] >= '0' && disStr[i] <= '9')
		{
			disCode = SegSel_CC[disStr[i] - '0'];
		}
		else if(disStr[i] >= 'A' && disStr[i] <= 'F')
		{
			disCode = SegSel_CC[disStr[i] - 'A' + 10];
		}
		else
		{
			disCode = SegSel_CC[17];
		}
		LED_SEG = disCode + ((dp >> (7 - i)) & 0x01) * SegSel_CC[16];
		
		LED_8Seg_Delay(REFRESH);
		
		// 消隐
		LED_SEG = SegSel_CC[17];
	}
=======
#include "8seg_CC_74xx138.h"

// 共阴数码管的段选
u8 code SegSel_CC[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 
						  0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 
						  0x39, 0x5E, 0x79, 0x71, 0x80, 0x00};

void LED_8Seg_Delay(u8 t)
{
	while(t--);
}

/* 这个函数定义的是8位的显示，传入的参数：
   1. 是要显示的字符串，占8位，0~F以及不显示，字母全大写
   2. 8要显示小数点的状态，转化为16进制，从高到低
   P.S. 要显示其他字符需要修改上面段选的数组，然后补充下面if函数 */
void LED_8Seg_Display(u8 disStr[8], u8 dp)
{
	u8 i, disCode;
	
	for(i = 0; i < 8; i++)
	{
		// 位选
		_74XX138_SetLow(i);
		
		// 段选
		if(disStr[i] >= '0' && disStr[i] <= '9')
		{
			disCode = SegSel_CC[disStr[i] - '0'];
		}
		else if(disStr[i] >= 'A' && disStr[i] <= 'F')
		{
			disCode = SegSel_CC[disStr[i] - 'A' + 10];
		}
		else
		{
			disCode = SegSel_CC[17];
		}
		LED_SEG = disCode + ((dp >> (7 - i)) & 0x01) * SegSel_CC[16];
		
		LED_8Seg_Delay(REFRESH);
		
		// 消隐
		LED_SEG = SegSel_CC[17];
	}
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
}