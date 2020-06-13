#include <reg52.h>
#include "key.h"
#include "uln2003.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

#define PWM_CYCLE 100	// PWM一周期10ms
u8 PWM_H = 50;

void INT1_Init()
{
	TMOD |= 0x10;
	TR1   = 1;
	TH1   = (65536 - 100) / 256;
	TL1   = (65536 - 100) % 256;
	ET1   = 1;
	EA    = 1;
}

void main()
{
	u8 DC_Motor = 0;
	
	INT1_Init();				// PWM定时器初始化
	KeyInit();					// 按键初始化
	ULN2003_DCBA_Switch(0x00);	// 芯片连接引脚初始化关闭
	
	while(1)
	{
		if(KeyScan() == 1)		// K1按下，加速
		{
			if(PWM_H < PWM_CYCLE) PWM_H++;
		}
		
		if(KeyScan() == 2)		// K2按下，减速
		{
			if(PWM_H > 0)         PWM_H--;
		}
	}
}

void INT1_100us() interrupt 3
{
	static u8 PWMCount = 0;
	
	TH1 = (65536 - 100) / 256;
	TL1 = (65536 - 100) % 256;
	
	PWMCount++;
	if(PWMCount == PWM_H) ULN2003_DCBA_Switch(0x00);
	if(PWMCount == PWM_CYCLE)
	{
		PWMCount = 0;
		if(PWM_H)	// 真的是要开的速度（非零）
		{
			ULN2003_DCBA_Switch(0x01);
		}
	}
}