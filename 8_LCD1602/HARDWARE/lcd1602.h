<<<<<<< HEAD
#ifndef _LCD1602_H_
#define _LCD1602_H_

#include <reg52.h>

#ifndef u8
#define u8 unsigned char
#endif

#ifndef u16
#define u16 unsigned int
#endif

#define LCD1602_DATAPINS P0		// LCD1602数据引脚
sbit LCD1602_E  = P2^7;			// LCD1602使能信号
sbit LCD1602_RW = P2^5;			// LCD1602读/写选择（H/L）
sbit LCD1602_RS = P2^6;			// LCD1602数据/命令选择（H/L）

// LCD1602写数据——8位数据线
void LCD1602_WriteDat(u8 dat);
// 初始化函数，可以修改为自己喜欢的模式
void LCD1602_Init();
// 设置为第一行还是第二行，1为第一行，2为第二行
void LCD1602_SetLine(u8 line);

=======
#ifndef _LCD1602_H_
#define _LCD1602_H_

#include <reg52.h>

#ifndef u8
#define u8 unsigned char
#endif

#ifndef u16
#define u16 unsigned int
#endif

#define LCD1602_DATAPINS P0		// LCD1602数据引脚
sbit LCD1602_E  = P2^7;			// LCD1602使能信号
sbit LCD1602_RW = P2^5;			// LCD1602读/写选择（H/L）
sbit LCD1602_RS = P2^6;			// LCD1602数据/命令选择（H/L）

// LCD1602写数据——8位数据线
void LCD1602_WriteDat(u8 dat);
// 初始化函数，可以修改为自己喜欢的模式
void LCD1602_Init();
// 设置为第一行还是第二行，1为第一行，2为第二行
void LCD1602_SetLine(u8 line);

>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
#endif