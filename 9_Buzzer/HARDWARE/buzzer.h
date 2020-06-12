#ifndef _BUZZER_H_
#define _BUZZER_H_

#include <reg52.h>

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// 晶振可选12MHz和11.0592MHz
#define CRYSTAL 12

// 定义是4/4（1）、3/4（2）、2/4（3）拍
#define PAT     3

sbit Buzzer = P1^5;

// 蜂鸣器初始化
void Buzzer_Init();
// 蜂鸣器发声函数
void Buzzer_Play(u8 index, u16 delay);

#endif