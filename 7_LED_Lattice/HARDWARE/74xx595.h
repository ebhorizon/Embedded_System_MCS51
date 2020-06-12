#ifndef _74XX595_H_
#define _74XX595_H_

#include <reg52.h>
#include <intrins.h>

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

sbit _74XX595_SER = P3^4;	// 串行数据输入
sbit _74XX595_RCK = P3^5;	// 存储寄存器时钟输入
sbit _74XX595_SCK = P3^6;	// 移位寄存器时钟输入

// 接受和发送数据，num代表级联的个数
void _74XX595_SendByte(u8 num, u8 dat[]);

#endif