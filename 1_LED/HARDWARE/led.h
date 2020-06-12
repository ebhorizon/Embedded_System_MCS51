#ifndef _LED_H_
#define _LED_H_

#include <reg52.h>
#include <intrins.h>

// 定义常用类型
#ifndef	u16
#define	u16	unsigned int
#endif
#ifndef	u8
#define	u8	unsigned char
#endif

// 定义LED * 8接P0口
#define LED	P0
sbit LED0 = P0^0;			// 使用P0.0点亮LED0

// 定义LED一端接GND还是VCC
#define LED_DEFAULT 0x00	// 默认接地的初始化

// LED0位操作点亮
void LED0_Light_Bit();
// LED0字操作点亮
void LED0_Light_Word();
// LED0闪烁
void LED0_Flash(u8 flashCount);
// LED左移
void LED_ToLeft();
// LED右移
void LED_ToRight();
// LED循环左移
void LED_ROL(u8 ROLCount);
// LED循环右移
void LED_ROR(u8 RORCount);
// PWM（脉宽调制）调节亮度
void LED_PWM(u8 PWMCount);

#endif
