#ifndef _1SEG_74XX164_H_
#define _1SEG_74XX164_H_

#include <reg52.h>
#include "74xx164.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// 定义使用的是CA还是CC数码管
#define CC

// 选择要显示的数码
void LED_1Seg_Display(u8 dat, u8 dp);

#endif