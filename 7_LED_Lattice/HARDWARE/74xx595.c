#include "74xx595.h"

// 接受和发送数据，num代表级联的个数
void _74XX595_SendByte(u8 num, u8 dat[])
{
	u8 i;
	u8 temp = num;
	
	// 存储和移位寄存器置高电平初始化
	_74XX595_RCK = 1;
	_74XX595_SCK = 1;
	
	// 级联个数循环
	while(temp--)
	{
		for(i = 0; i < 8; i++)
		{
			// 先发送数据最高位
			_74XX595_SER = dat[num - 1 - temp] >> 7;
			// 再将数据左移
			dat[num - 1 - temp] <<= 1;
			
			// 上升沿移位
			_74XX595_SCK = 0;
			_nop_(); _nop_();
			_74XX595_SCK = 1;
		}
	}
	
	// 上升沿数据输出
	_74XX595_RCK = 0;
	_nop_(); _nop_();
	_74XX595_RCK = 1;
}