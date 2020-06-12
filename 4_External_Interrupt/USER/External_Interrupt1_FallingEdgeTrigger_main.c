/* 外部中断1——下降沿触发 */

#include <reg52.h>

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

#define LED P0				// 定义LED接在P0
sbit KEY = P3^2;			// 定义触发外部中断0的按键

// 外部中断0初始化函数
void EINT1_Init()
{
	// 触发方式：下降沿触发
	IT0 = 1;
	// 开启外部中断1
	EX1 = 1;
	// 开启全局中断
	EA  = 1;
}

void Delay10ms()   			//误差 0us
{
    u8 a, b, c;
    for(c = 1; c > 0; c--)
        for(b = 38; b > 0; b--)
            for(a = 130; a > 0; a--);
}

void main()
{
	LED = 0x33;				// LED显示：0011 0011
	EINT1_Init();
	while(1);
}

/* 1. 中断函数可以不写返回类型
   2. 中断函数可以加一句using表示使用的寄存器组（0 ~ 3） */
void EINT1() interrupt 2
{
	// 进入中断时，LED灯亮灭状态翻转
	
	// ----!!!!!!!!此处的按键程序不标准，仅作为测试使用!!!!!!!!----
	if(!INT1)				// 按键按下就是接GND
	{
		Delay10ms();
		while(!INT1);		// 判断按键是否松开
		LED = ~LED;
	}
}