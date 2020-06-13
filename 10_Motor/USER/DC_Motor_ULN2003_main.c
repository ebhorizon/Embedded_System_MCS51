#include <reg52.h>
#include "key.h"
#include "uln2003.h"

// ULN2003只能驱动单极性电机！

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

void main()
{
	u8 DC_Motor = 0;
	
	KeyInit();					// 按键初始化
	ULN2003_DCBA_Switch(0x00);	// 芯片连接引脚初始化关闭
	
	while(1)
	{
		if(KeyScan() == 1)		// K1按下
		{
			DC_Motor = !DC_Motor;
			ULN2003_DCBA_Switch(0x00 | DC_Motor);
		}
	}
}