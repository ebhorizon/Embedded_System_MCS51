#ifndef _ULN2003_H_
#define _ULN2003_H_

#include <reg52.h>

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

sbit ULN2003_A_IN = P1^0;
sbit ULN2003_B_IN = P1^1;
sbit ULN2003_C_IN = P1^2;
sbit ULN2003_D_IN = P1^3;

// 开关函数，只使用u8的低4位，低到高分别为A到D
void ULN2003_DCBA_Switch(u8 DCBA);

#endif