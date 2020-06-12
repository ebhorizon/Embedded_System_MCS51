<<<<<<< HEAD
#ifndef _74XX138_H_
#define _74XX138_H_

#include <reg52.h>
// #include <intrins.h>

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// 定义3-8译码器的ABC脚
sbit _74XX138_A = P2^2;
sbit _74XX138_B = P2^3;
sbit _74XX138_C = P2^4;

// 输入使第几位为低电平
void _74XX138_SetLow(u8 dat);

=======
#ifndef _74XX138_H_
#define _74XX138_H_

#include <reg52.h>
// #include <intrins.h>

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// 定义3-8译码器的ABC脚
sbit _74XX138_A = P2^2;
sbit _74XX138_B = P2^3;
sbit _74XX138_C = P2^4;

// 输入使第几位为低电平
void _74XX138_SetLow(u8 dat);

>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
#endif