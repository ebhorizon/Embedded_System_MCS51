#ifndef _8SEG_H_
#define _8SEG_H_

#include <reg52.h>

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// ����ܶ�ѡ�ӿ�
#define LED_SEG P2
// �����λѡ�ӿ�
#define LED_BIT P1

// ����ʹ�õ���CA����CC�����
#define CA

// ˢ����
#define REFRESH 100

/* ��������������8λ����ʾ������Ĳ�����
   1. ��Ҫ��ʾ���ַ�����ռ8λ��0~F�Լ�����ʾ����ĸȫ��д
   2. 8Ҫ��ʾС�����״̬��ת��Ϊ16���ƣ��Ӹߵ���
   P.S. Ҫ��ʾ�����ַ���Ҫ�޸������ѡ�����飬Ȼ�󲹳�����if���� */
void LED_8Seg_Display(u8 disStr[8], u8 dp);

#endif