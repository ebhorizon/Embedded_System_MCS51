<<<<<<< HEAD
#include "8seg.h"

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

// ����ܵ�λѡ						  
u8 code SegBit[]    = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void LED_8Seg_Delay(u8 t)
{
	while(t--);
}

#ifdef CA
/* ��������������8λ����ʾ������Ĳ�����
   1. ��Ҫ��ʾ���ַ�����ռ8λ��0~F�Լ�����ʾ����ĸȫ��д
   2. 8Ҫ��ʾС�����״̬��ת��Ϊ16���ƣ��Ӹߵ���
   P.S. Ҫ��ʾ�����ַ���Ҫ�޸������ѡ�����飬Ȼ�󲹳�����if���� */
void LED_8Seg_Display(u8 disStr[8], u8 dp)
{
	u8 i, disCode;
	
	for(i = 0; i < 8; i++)
	{
		// λѡ
		LED_BIT = SegBit[i];
		
		// ��ѡ
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
		
		// ����
		LED_SEG = SegSel_CA[17];
	}
}
#elif defined CC
/* ��������������8λ����ʾ������Ĳ�����
   1. ��Ҫ��ʾ���ַ�����ռ8λ��0~F�Լ�����ʾ����ĸȫ��д
   2. 8Ҫ��ʾС�����״̬��ת��Ϊ16���ƣ��Ӹߵ���
   P.S. Ҫ��ʾ�����ַ���Ҫ�޸������ѡ�����飬Ȼ�󲹳�����if���� */
void LED_8Seg_Display(u8 disStr[8], u8 dp)
{
	u8 i, disCode;
	
	for(i = 0; i < 8; i++)
	{
		// λѡ
		LED_BIT = ~SegBit[i];
		
		// ��ѡ
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
		
		// ����
		LED_SEG = SegSel_CC[17];
	}
}
#endif
=======
#include "8seg.h"

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

// ����ܵ�λѡ						  
u8 code SegBit[]    = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void LED_8Seg_Delay(u8 t)
{
	while(t--);
}

#ifdef CA
/* ��������������8λ����ʾ������Ĳ�����
   1. ��Ҫ��ʾ���ַ�����ռ8λ��0~F�Լ�����ʾ����ĸȫ��д
   2. 8Ҫ��ʾС�����״̬��ת��Ϊ16���ƣ��Ӹߵ���
   P.S. Ҫ��ʾ�����ַ���Ҫ�޸������ѡ�����飬Ȼ�󲹳�����if���� */
void LED_8Seg_Display(u8 disStr[8], u8 dp)
{
	u8 i, disCode;
	
	for(i = 0; i < 8; i++)
	{
		// λѡ
		LED_BIT = SegBit[i];
		
		// ��ѡ
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
		
		// ����
		LED_SEG = SegSel_CA[17];
	}
}
#elif defined CC
/* ��������������8λ����ʾ������Ĳ�����
   1. ��Ҫ��ʾ���ַ�����ռ8λ��0~F�Լ�����ʾ����ĸȫ��д
   2. 8Ҫ��ʾС�����״̬��ת��Ϊ16���ƣ��Ӹߵ���
   P.S. Ҫ��ʾ�����ַ���Ҫ�޸������ѡ�����飬Ȼ�󲹳�����if���� */
void LED_8Seg_Display(u8 disStr[8], u8 dp)
{
	u8 i, disCode;
	
	for(i = 0; i < 8; i++)
	{
		// λѡ
		LED_BIT = ~SegBit[i];
		
		// ��ѡ
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
		
		// ����
		LED_SEG = SegSel_CC[17];
	}
}
#endif
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
