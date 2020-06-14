#ifndef _4GPIO_MATRIX_KEY_H_
#define _4GPIO_MATRIX_KEY_H_

#include <reg52.h>

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

#define GPIOKEYS P2	// 只使用P2.0 ~ P2.3

// 加消抖的扫描
u8 GPIOKeyScanAgain();

#endif