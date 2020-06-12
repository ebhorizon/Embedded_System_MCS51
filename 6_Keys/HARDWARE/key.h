#ifndef _KEY_H_
#define _KEY_H_

#include <reg52.h>

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// 定义按键使用引脚
#define KEYS P1

// 此处的按键程序使用到定时器0，不想使用可以调用普通按键程序
void KeyInit();
// 扫描哪个按键按下了
u8 KeyScan();

#endif