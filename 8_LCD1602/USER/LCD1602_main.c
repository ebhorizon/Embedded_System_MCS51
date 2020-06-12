<<<<<<< HEAD
#include <reg52.h>
#include "lcd1602.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

void main()
{
	u8 i;
	u8 displayWords1[] = " Linkat Horizon ";
	u8 displayWords2[] = " Happy Coding!! ";
	
	LCD1602_Init();
	
	// 第一行
	LCD1602_SetLine(1);
	for(i = 0; i < 16; i++)	LCD1602_WriteDat(displayWords1[i]);
	
	// 第二行
	LCD1602_SetLine(2);
	for(i = 0; i < 16; i++) LCD1602_WriteDat(displayWords2[i]);
	
	while(1);
=======
#include <reg52.h>
#include "lcd1602.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

void main()
{
	u8 i;
	u8 displayWords1[] = " Linkat Horizon ";
	u8 displayWords2[] = " Happy Coding!! ";
	
	LCD1602_Init();
	
	// 第一行
	LCD1602_SetLine(1);
	for(i = 0; i < 16; i++)	LCD1602_WriteDat(displayWords1[i]);
	
	// 第二行
	LCD1602_SetLine(2);
	for(i = 0; i < 16; i++) LCD1602_WriteDat(displayWords2[i]);
	
	while(1);
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
}