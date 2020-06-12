<<<<<<< HEAD
#include "8seg.h"

#ifdef CA
// 共阳数码管段选，0 ~ F & . & 空
u8 code SegSel_CA[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 
						  0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 
						  0xC6, 0xA1, 0x86, 0x8E, 0x7F, 0xFF};
#elif defined CC
// 为了方便查阅才写出来，也可以直接CA的段选取反
u8 code SegSel_CC[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 
						  0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 
						  0x39, 0x5E, 0x79, 0x71, 0x80, 0x00};
#endif

// 数码管的位选						  
u8 code SegBit[]    = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void LED_8Seg_Delay(u8 t)
{
	while(t--);
}

#ifdef CA
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
		LED_BIT = SegBit[i];
		
		// 段选
		if(disStr[i] >= '0' && disStr[i] <= '9')
		{
			disCode = SegSel_CA[disStr[i] - '0'];
		}
		else if(disStr[i] >= 'A' && disStr[i] <= 'F')
		{
			disCode = SegSel_CA[disStr[i] - 'A' + 10];
		}
		else
		{
			disCode = SegSel_CA[17];
		}
		LED_SEG = ~(~disCode + ((dp >> (7 - i)) & 0x01) * ~SegSel_CA[16]);
		
		LED_8Seg_Delay(REFRESH);
		
		// 消隐
		LED_SEG = SegSel_CA[17];
	}
}
#elif defined CC
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
		LED_BIT = ~SegBit[i];
		
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
}
#endif
=======
#include "8seg.h"

#ifdef CA
// 共阳数码管段选，0 ~ F & . & 空
u8 code SegSel_CA[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 
						  0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 
						  0xC6, 0xA1, 0x86, 0x8E, 0x7F, 0xFF};
#elif defined CC
// 为了方便查阅才写出来，也可以直接CA的段选取反
u8 code SegSel_CC[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 
						  0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 
						  0x39, 0x5E, 0x79, 0x71, 0x80, 0x00};
#endif

// 数码管的位选						  
u8 code SegBit[]    = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void LED_8Seg_Delay(u8 t)
{
	while(t--);
}

#ifdef CA
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
		LED_BIT = SegBit[i];
		
		// 段选
		if(disStr[i] >= '0' && disStr[i] <= '9')
		{
			disCode = SegSel_CA[disStr[i] - '0'];
		}
		else if(disStr[i] >= 'A' && disStr[i] <= 'F')
		{
			disCode = SegSel_CA[disStr[i] - 'A' + 10];
		}
		else
		{
			disCode = SegSel_CA[17];
		}
		LED_SEG = ~(~disCode + ((dp >> (7 - i)) & 0x01) * ~SegSel_CA[16]);
		
		LED_8Seg_Delay(REFRESH);
		
		// 消隐
		LED_SEG = SegSel_CA[17];
	}
}
#elif defined CC
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
		LED_BIT = ~SegBit[i];
		
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
}
#endif
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
