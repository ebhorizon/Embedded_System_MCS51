<<<<<<< HEAD
#ifndef _74XX138_H_
#define _74XX138_H_

#include <reg52.h>
// #include <intrins.h>

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// ����3-8��������ABC��
sbit _74XX138_A = P2^2;
sbit _74XX138_B = P2^3;
sbit _74XX138_C = P2^4;

// ����ʹ�ڼ�λΪ�͵�ƽ
void _74XX138_SetLow(u8 dat);

=======
#ifndef _74XX138_H_
#define _74XX138_H_

#include <reg52.h>
// #include <intrins.h>

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// ����3-8��������ABC��
sbit _74XX138_A = P2^2;
sbit _74XX138_B = P2^3;
sbit _74XX138_C = P2^4;

// ����ʹ�ڼ�λΪ�͵�ƽ
void _74XX138_SetLow(u8 dat);

>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
#endif