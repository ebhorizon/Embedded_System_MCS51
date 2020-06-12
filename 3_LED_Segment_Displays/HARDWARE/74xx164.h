#ifndef _74XX164_H_
#define _74XX164_H_

#include <reg52.h>
// #include <intrins.h>

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// ����74XX164�����Žӷ�
sbit _74XX164_CLR  = P2^0;
sbit _74XX164_CLK  = P2^1;
// ��Ϊ������AB���룬�������һ�˽Ӹߵ�ƽVCC���ɣ������õĻ�ֻ�趨���������ż���
sbit _74XX164_Data = P2^2;

// 74XX164����һ���ֽ�
void _74XX164_SendByte(u8 dat);
// 74XX164����
void _74XX164_Enable();
// 74XX164�ر�
void _74XX164_Disable();

#endif