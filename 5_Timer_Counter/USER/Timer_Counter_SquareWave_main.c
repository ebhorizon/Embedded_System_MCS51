#include <reg52.h>

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

// 定义方波的频率：8Hz ~ 500kHz
#define SW_FREQ 100

/* 1. 使用12MHz晶振，时钟周期为1/12us，机器周期为(12 * 1 / 12) = 1us
   2. TH = (2^16 - HalfPeriod) / (2^8) = (65536 - HalfPeriod) / 256
   3. TL = (2^16 - HalfPeriod) % (2^8) = (65536 - HalfPeriod) % 256 */
u8 TH_Init = (65536 - 1000000 / SW_FREQ / 2) / 256;
u8 TL_Init = (65536 - 1000000 / SW_FREQ / 2) % 256;

// 定义方波输出端
sbit SW_Out = P1^0;

// 定时/计数器0的初始化函数
void TINT0_Init()
{
	/* 定时器0，工作方式1，或运算防止移植的时候影响其他定时器
	   方式1：16位加1计数器 */
	TMOD |= 0x01;
	
	// 打开定时器0
	TR0 = 1;
	
	// 此处注意，由于需要重装载，不要让程序过多计算
	TH0 = TH_Init;
	TL0 = TL_Init;
	
	// 定时器0中断和总中断开关打开
	ET0 = 1;
	EA  = 1;
}

void main()
{
	TINT0_Init();
	SW_Out = 1;
	while(1);
}

void TINT0() interrupt 1
{
	// 重装载
	TH0 = TH_Init;
	TL0 = TL_Init;
	
	// 电平翻转
	SW_Out = ~SW_Out;
}