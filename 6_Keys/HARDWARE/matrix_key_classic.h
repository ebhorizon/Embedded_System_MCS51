<<<<<<< HEAD
#ifndef _MATRIX_KEY_CLASSIC_H_
#define _MATRIX_KEY_CLASSIC_H_

#include <reg52.h>

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// 定义按键使用引脚
// !!!!----此处排线要反插----!!!!
#define MATRIXKEYS P3

// 扫描哪个按键按下了
u8 MatrixKeyScan();

=======
#ifndef _MATRIX_KEY_CLASSIC_H_
#define _MATRIX_KEY_CLASSIC_H_

#include <reg52.h>

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// 定义按键使用引脚
// !!!!----此处排线要反插----!!!!
#define MATRIXKEYS P3

// 扫描哪个按键按下了
u8 MatrixKeyScan();

>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
#endif