#ifndef _74XX595_H_
#define _74XX595_H_

#include <reg52.h>
#include <intrins.h>

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

sbit _74XX595_SER = P3^4;	// ������������
sbit _74XX595_RCK = P3^5;	// �洢�Ĵ���ʱ������
sbit _74XX595_SCK = P3^6;	// ��λ�Ĵ���ʱ������

// ���ܺͷ������ݣ�num�������ĸ���
void _74XX595_SendByte(u8 num, u8 dat[]);

#endif