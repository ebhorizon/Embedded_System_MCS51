#ifndef _4GPIO_MATRIX_KEY_H_
#define _4GPIO_MATRIX_KEY_H_

#include <reg52.h>

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

#define GPIOKEYS P2	// ֻʹ��P2.0 ~ P2.3

// ��������ɨ��
u8 GPIOKeyScanAgain();

#endif