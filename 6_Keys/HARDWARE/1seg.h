#ifndef _1SEG_H_
#define _1SEG_H_

#include <reg52.h>

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// һλLED����ܽ���P0
#define LED_SEG P0

// ����ʹ�õ���CA����CC�����
#define CA

// ѡ��Ҫ��ʾ������
void LED_1Seg_Display(u8 dat, u8 dp);
// ����߼���ƽ
// void LED_1Seg_LogicLevel(u8 dat);

#endif