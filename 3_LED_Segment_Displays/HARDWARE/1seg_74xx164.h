#ifndef _1SEG_74XX164_H_
#define _1SEG_74XX164_H_

#include <reg52.h>
#include "74xx164.h"

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// ����ʹ�õ���CA����CC�����
#define CC

// ѡ��Ҫ��ʾ������
void LED_1Seg_Display(u8 dat, u8 dp);

#endif