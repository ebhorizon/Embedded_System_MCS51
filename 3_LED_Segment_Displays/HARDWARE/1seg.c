#include "1seg.h"

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
						  
#ifdef CA
// 选择要显示的数码
void LED_1Seg_Display(u8 dat, u8 dp)
{
	LED_SEG = ~(~SegSel_CA[dat] + (~SegSel_CA[16] * dp));
}

// 检测逻辑电平
void LED_1Seg_LogicLevel(u8 dat)
{
	// 高电平显示H，低电平显示L
	LED_SEG = (dat ? 0x89 : 0xC7);
}
#elif defined CC
// 选择要显示的数码
void LED_1Seg_Display(u8 dat, u8 dp)
{
	LED_SEG = SegSel_CC[dat] + (SegSel_CC[16] * dp);
}

// 检测逻辑电平
void LED_1Seg_LogicLevel(u8 dat)
{
	// 高电平显示H，低电平显示L
	LED_SEG = (dat ? 0x76 : 0x38);
}
#endif