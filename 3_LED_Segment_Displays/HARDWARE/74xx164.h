#ifndef _74XX164_H_
#define _74XX164_H_

#include <reg52.h>
// #include <intrins.h>

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// 定义74XX164的引脚接法
sbit _74XX164_CLR  = P2^0;
sbit _74XX164_CLK  = P2^1;
// 因为数据是AB相与，所以随便一端接高电平VCC即可，想启用的话只需定义两个引脚即可
sbit _74XX164_Data = P2^2;

// 74XX164发送一个字节
void _74XX164_SendByte(u8 dat);
// 74XX164开启
void _74XX164_Enable();
// 74XX164关闭
void _74XX164_Disable();

#endif