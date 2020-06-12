#include "led.h"

void LED_Delay(u16 t)
{
	while(t--);
}

// 初始化全灭
void LED_Init()
{
	LED	= LED_DEFAULT;
	LED_Delay(50000);
	LED_Delay(50000);
}

// LED0位操作点亮
void LED0_Light_Bit()
{
	LED_Init();
	LED0 = (~LED_DEFAULT) & 0x01;	// 取反的最低位
	LED_Delay(50000);
}

// LED0字操作点亮
void LED0_Light_Word()
{
	LED_Init();
	// 此处修改可以点亮多位
	LED0 |= ~LED_DEFAULT;
	LED_Delay(50000);
}

// LED0闪烁
void LED0_Flash(u8 flashCount)
{
	LED_Init();
	for(; flashCount > 0; flashCount--)
	{
		// 改变延迟时间可以改变闪烁频率
		LED0 = (~LED_DEFAULT) & 0x01;	// 取反的最低位
		LED_Delay(20000);
		LED0 = LED_DEFAULT    & 0x01;	// 取反的最低位
		LED_Delay(20000);
	}
}

// LED左移
void LED_ToLeft()
{
	u8 i, ledStat;
	
	LED_Init();
	ledStat = 0x01;
	// 此处用到的取反思想要记住
	(LED_DEFAULT == 0x00) ? (LED = ledStat) : (LED = ~ledStat);
	for(i = 0; i < 8; i++)
	{
		LED_Delay(10000);
		ledStat = ledStat << 1;
		(LED_DEFAULT == 0x00) ? (LED = ledStat) : (LED = ~ledStat);
	}	
	LED_Delay(10000);
}

// LED右移
void LED_ToRight()
{
	u8 i, ledStat;
	
	LED_Init();
	ledStat = 0x80;
	(LED_DEFAULT == 0x00) ? (LED = ledStat) : (LED = ~ledStat);
	for(i = 0; i < 8; i++)
	{
		LED_Delay(10000);
		ledStat = ledStat >> 1;
		(LED_DEFAULT == 0x00) ? (LED = ledStat) : (LED = ~ledStat);
	}	
	LED_Delay(10000);
}

// LED循环左移
// 可以参考上面的取反思想，也可以直接调用库函数（比较方便的标准操作）
void LED_ROL(u8 ROLCount)
{
	u8 i;
	
	LED_Init();
	for(; ROLCount > 0; ROLCount--)
	{
		(LED_DEFAULT == 0x00) ? (LED = 0x01) : (LED = 0xFE);
		for(i = 0; i < 7; i++)
		{
			LED_Delay(10000);
			LED = _crol_(LED, 1);
		}
		LED_Delay(10000);
	}
}

// LED循环右移
void LED_ROR(u8 RORCount)
{
	u8 i;
	
	LED_Init();
	for(; RORCount > 0; RORCount--)
	{
		(LED_DEFAULT == 0x00) ? (LED = 0x80) : (LED = 0x7F);
		for(i = 0; i < 7; i++)
		{
			LED_Delay(10000);
			LED = _cror_(LED, 1);
		}
		LED_Delay(10000);
	}
}

// 其他代码就是自由发挥了，不再赘述

// PWM（脉宽调制）调节亮度
// 原理很简单，改变高电平（或者说点亮的电平）的占比时间——占空比即可
void LED_PWM(u8 PWMCount)
{
	u16  T    = 500;
	u16  Toff = 0;
	
	LED_Init();
	for(; PWMCount > 0; PWMCount--)
	{
		for(Toff = 1; Toff < T; Toff++)
		{
			(LED_DEFAULT == 0x00) ? (LED = 0xFF) : (LED = 0x00);
			LED_Delay(Toff);
			
			(LED_DEFAULT == 0x00) ? (LED = 0x00) : (LED = 0xFF);
			LED_Delay(T - Toff);
		}
		
		for(Toff = T - 1; Toff > 0 ; Toff--)
		{
			(LED_DEFAULT == 0x00) ? (LED = 0xFF) : (LED = 0x00);
			LED_Delay(Toff);
			
			(LED_DEFAULT == 0x00) ? (LED = 0x00) : (LED = 0xFF);
			LED_Delay(T - Toff);
		}
	}
}
