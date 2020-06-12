<<<<<<< HEAD
#include "lcd1602.h"

void LCD1602_Delay1ms(u16 c)
{
	u8 a, b;
	for(; c > 0; c--)
		for(b = 199; b > 0; b--)
			for(a = 1; a > 0; a--);
}

// LCD1602写指令——8位数据线
void LCD1602_WriteCmd(u8 cmd)
{
	LCD1602_E  = 0;
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	
	LCD1602_DATAPINS = cmd;
	LCD1602_Delay1ms(1);
	
	LCD1602_E = 1;
	LCD1602_Delay1ms(5);
	LCD1602_E = 0;
}

// LCD1602写数据——8位数据线
void LCD1602_WriteDat(u8 dat)
{
	LCD1602_E  = 0;
	// 写入数据至CGRAM或DDRAM
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	
	LCD1602_DATAPINS = dat;
	LCD1602_Delay1ms(1);
	
	LCD1602_E = 1;
	LCD1602_Delay1ms(5);
	LCD1602_E = 0;
}

// 设置为第一行还是第二行，1为第一行，2为第二行
void LCD1602_SetLine(u8 line)
{
	// 光标起始地址要加上80H
	if(line == 1) LCD1602_WriteCmd(0x80);	// 00H + 80H
	if(line == 2) LCD1602_WriteCmd(0xC0);	// 40H + 80H
}

// 初始化函数，可以修改为自己喜欢的模式
void LCD1602_Init()
{
	/* LCD1602功能设置——001(DL) NFXX
       DL：表示在高电平时为8位总线，低电平时为4位总线（低四位不用）
       N： 表示在低电平时为单行显示，高电平时双行显示
       F： 表示在低电平时显示5 × 7点阵每字符，高电平时显示5 × 10点阵每字符 */ 
	LCD1602_WriteCmd(0x38);
	/* LCD1602显示开关控制——0000 1DCB
       D： 用于控制整体显示的开与关，高电平表示开显示，低电平表示关显示
       C： 用于控制光标的开与关，高电平表示有光标，低电平表示无光标
       B： 用于控制光标是否闪烁，高电平闪烁，低电平不闪烁 */
	LCD1602_WriteCmd(0x0C);
	/* LCD1602输入方式设置——0000 01(ID)S
       ID：表示光标的移动方向，高电平右移，低电平左移
	   S： 表示显示屏上所有文字是否左移或右移，高电平表示有效，低电平表示无效 */
	LCD1602_WriteCmd(0x06);
	// 清屏
	LCD1602_WriteCmd(0x01);
=======
#include "lcd1602.h"

void LCD1602_Delay1ms(u16 c)
{
	u8 a, b;
	for(; c > 0; c--)
		for(b = 199; b > 0; b--)
			for(a = 1; a > 0; a--);
}

// LCD1602写指令——8位数据线
void LCD1602_WriteCmd(u8 cmd)
{
	LCD1602_E  = 0;
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	
	LCD1602_DATAPINS = cmd;
	LCD1602_Delay1ms(1);
	
	LCD1602_E = 1;
	LCD1602_Delay1ms(5);
	LCD1602_E = 0;
}

// LCD1602写数据——8位数据线
void LCD1602_WriteDat(u8 dat)
{
	LCD1602_E  = 0;
	// 写入数据至CGRAM或DDRAM
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	
	LCD1602_DATAPINS = dat;
	LCD1602_Delay1ms(1);
	
	LCD1602_E = 1;
	LCD1602_Delay1ms(5);
	LCD1602_E = 0;
}

// 设置为第一行还是第二行，1为第一行，2为第二行
void LCD1602_SetLine(u8 line)
{
	// 光标起始地址要加上80H
	if(line == 1) LCD1602_WriteCmd(0x80);	// 00H + 80H
	if(line == 2) LCD1602_WriteCmd(0xC0);	// 40H + 80H
}

// 初始化函数，可以修改为自己喜欢的模式
void LCD1602_Init()
{
	/* LCD1602功能设置——001(DL) NFXX
       DL：表示在高电平时为8位总线，低电平时为4位总线（低四位不用）
       N： 表示在低电平时为单行显示，高电平时双行显示
       F： 表示在低电平时显示5 × 7点阵每字符，高电平时显示5 × 10点阵每字符 */ 
	LCD1602_WriteCmd(0x38);
	/* LCD1602显示开关控制——0000 1DCB
       D： 用于控制整体显示的开与关，高电平表示开显示，低电平表示关显示
       C： 用于控制光标的开与关，高电平表示有光标，低电平表示无光标
       B： 用于控制光标是否闪烁，高电平闪烁，低电平不闪烁 */
	LCD1602_WriteCmd(0x0C);
	/* LCD1602输入方式设置——0000 01(ID)S
       ID：表示光标的移动方向，高电平右移，低电平左移
	   S： 表示显示屏上所有文字是否左移或右移，高电平表示有效，低电平表示无效 */
	LCD1602_WriteCmd(0x06);
	// 清屏
	LCD1602_WriteCmd(0x01);
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
}