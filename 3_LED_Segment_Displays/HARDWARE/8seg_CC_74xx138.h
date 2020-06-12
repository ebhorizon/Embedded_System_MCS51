<<<<<<< HEAD
#ifndef _8SEG_CC_74XX138_H_
#define _8SEG_CC_74XX138_H_

#include <reg52.h>
#include "74xx138.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// 数码管段选接口
#define LED_SEG P1

// 刷新率
#define REFRESH 100

/* 这个函数定义的是8位的显示，传入的参数：
   1. 是要显示的字符串，占8位，0~F以及不显示，字母全大写
   2. 8要显示小数点的状态，转化为16进制，从高到低
   P.S. 要显示其他字符需要修改上面段选的数组，然后补充下面if函数 */
void LED_8Seg_Display(u8 disStr[8], u8 dp);

=======
#ifndef _8SEG_CC_74XX138_H_
#define _8SEG_CC_74XX138_H_

#include <reg52.h>
#include "74xx138.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// 数码管段选接口
#define LED_SEG P1

// 刷新率
#define REFRESH 100

/* 这个函数定义的是8位的显示，传入的参数：
   1. 是要显示的字符串，占8位，0~F以及不显示，字母全大写
   2. 8要显示小数点的状态，转化为16进制，从高到低
   P.S. 要显示其他字符需要修改上面段选的数组，然后补充下面if函数 */
void LED_8Seg_Display(u8 disStr[8], u8 dp);

>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
#endif