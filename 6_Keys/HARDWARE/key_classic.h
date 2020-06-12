#ifndef _KEY_CLASSIC_H_
#define _KEY_CLASSIC_H_

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

// 普通的按键程序——效果其实也不错
u8 KeyScan_Classic();

#endif