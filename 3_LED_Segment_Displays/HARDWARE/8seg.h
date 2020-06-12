#ifndef _8SEG_H_
#define _8SEG_H_

#include <reg52.h>

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// 数码管段选接口
#define LED_SEG P2
// 数码管位选接口
#define LED_BIT P1

// 定义使用的是CA还是CC数码管
#define CA

// 刷新率
#define REFRESH 100

/* 这个函数定义的是8位的显示，传入的参数：
   1. 是要显示的字符串，占8位，0~F以及不显示，字母全大写
   2. 8要显示小数点的状态，转化为16进制，从高到低
   P.S. 要显示其他字符需要修改上面段选的数组，然后补充下面if函数 */
void LED_8Seg_Display(u8 disStr[8], u8 dp);

#endif