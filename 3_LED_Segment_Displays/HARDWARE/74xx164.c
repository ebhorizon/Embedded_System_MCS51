<<<<<<< HEAD
#include "74xx164.h"

void _74XX164_Delay(u8 t)
{
	while(t--);
}

// 74XX164发送一个字节
void _74XX164_SendByte(u8 dat)
{
    u8 i;
	
    for(i = 0; i < 8; i++)
    {
		_74XX164_Data = dat >> 7;	// 高位到低位发送
		dat 		<<= 1;			// 数据左移准备下次发送
        _74XX164_CLK  = 0;			// 等待数据
		// _nop_();
		// _nop_();
        _74XX164_CLK  = 1;			// 上升沿发送数据
    }
}

// 74XX164开启
void _74XX164_Enable()
{
	_74XX164_CLR = 1;
}

// 74XX164关闭
void _74XX164_Disable()
{
	_74XX164_CLR = 0;
	_74XX164_Delay(500);
=======
#include "74xx164.h"

void _74XX164_Delay(u8 t)
{
	while(t--);
}

// 74XX164发送一个字节
void _74XX164_SendByte(u8 dat)
{
    u8 i;
	
    for(i = 0; i < 8; i++)
    {
		_74XX164_Data = dat >> 7;	// 高位到低位发送
		dat 		<<= 1;			// 数据左移准备下次发送
        _74XX164_CLK  = 0;			// 等待数据
		// _nop_();
		// _nop_();
        _74XX164_CLK  = 1;			// 上升沿发送数据
    }
}

// 74XX164开启
void _74XX164_Enable()
{
	_74XX164_CLR = 1;
}

// 74XX164关闭
void _74XX164_Disable()
{
	_74XX164_CLR = 0;
	_74XX164_Delay(500);
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
}