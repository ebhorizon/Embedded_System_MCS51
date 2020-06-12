#include "1seg.h"

#ifdef CA
// ��������ܶ�ѡ��0 ~ F & . & ��
u8 code SegSel_CA[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 
						  0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 
						  0xC6, 0xA1, 0x86, 0x8E, 0x7F, 0xFF};
#elif defined CC
// Ϊ�˷�����Ĳ�д������Ҳ����ֱ��CA�Ķ�ѡȡ��
u8 code SegSel_CC[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 
						  0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 
						  0x39, 0x5E, 0x79, 0x71, 0x80, 0x00};	
#endif
						  
#ifdef CA
// ѡ��Ҫ��ʾ������
void LED_1Seg_Display(u8 dat, u8 dp)
{
	LED_SEG = ~(~SegSel_CA[dat] + (~SegSel_CA[16] * dp));
}

// ����߼���ƽ
void LED_1Seg_LogicLevel(u8 dat)
{
	// �ߵ�ƽ��ʾH���͵�ƽ��ʾL
	LED_SEG = (dat ? 0x89 : 0xC7);
}
#elif defined CC
// ѡ��Ҫ��ʾ������
void LED_1Seg_Display(u8 dat, u8 dp)
{
	LED_SEG = SegSel_CC[dat] + (SegSel_CC[16] * dp);
}

// ����߼���ƽ
void LED_1Seg_LogicLevel(u8 dat)
{
	// �ߵ�ƽ��ʾH���͵�ƽ��ʾL
	LED_SEG = (dat ? 0x76 : 0x38);
}
#endif