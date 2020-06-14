#ifndef _1SEG_H_
#define _1SEG_H_

#include <reg52.h>

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// 一位LED数码管接在P0
#define LED_SEG P0

// 定义使用的是CA还是CC数码管
#define CA

// 选择要显示的数码
void LED_1Seg_Display(u8 dat, u8 dp);
// 检测逻辑电平
// void LED_1Seg_LogicLevel(u8 dat);

#endif