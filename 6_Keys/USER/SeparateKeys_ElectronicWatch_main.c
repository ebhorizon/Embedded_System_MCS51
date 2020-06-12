<<<<<<< HEAD
#include <reg52.h>
#include "74xx138.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif
#ifndef u32
#define u32 unsigned long
#endif

#define SEG_SEL P0					// 段选引脚
sbit LED = P1^0;					// LED使用引脚
// 此处按键的代码由于借给闹钟暂停了，所以没有写出去用key.h调用
sbit K1  = P3^0;					// 设置时间的按键
sbit K2  = P3^1;					// 分钟 + 1
sbit K3  = P3^2;					// 小时 + 1
sbit K4  = P3^3;					// 设置LED（闹铃）的按键

// 共阴数码管段选，从0到9
u8 code segCC_SegSel[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
// 数码管显示数据，初始化00-00-00
u8 DisplayCode[8]        = {0x3f, 0x3f, 0x40, 0x3f, 0x3f, 0x40, 0x3f, 0x3f};

u32 timestamp      = 0;				// 存储显示时间戳的变量
/* 原本可以使用u16类型来定义闹钟时间戳，这样节省内存
   但是考虑到DisplayCode_Update()的修改繁琐，故不优化此处 */
u32 alarmTimestamp = 43200;			// 存储闹铃时间戳的变量，为防止一开始闹钟，设置为12-00-00
/* 数组全初始化只需写一个元素即可 */
u8  KeyCur[4]      = {1};			// 装载当前时刻按键状态值
u8  KeyPre[4]      = {1};			// 装载之前时刻按键状态值
u8  KeyBuff[4]     = {0xFF};		// 装载按键状态缓冲的变量
u8  KeyEnable[4]   = {1, 0, 0, 1};	// 四个按键是否可按的状态变量

// 延时1ms函数
void Delay1ms()
{
    u8 i;
	
	for(i = 0; i < 125; i++);
}

// 数码管显示函数
void SegDisplay()
{	  
	u8 i;
	
	for(i = 0; i < 8; i++)
	{
		_74XX138_SetLow(i);				// 数码管位选
		SEG_SEL = DisplayCode[i];		// 数码管段选
		Delay1ms();
		
		SEG_SEL = 0x00;					// 数码管消隐
	}
}

// 显示时间更新
void DisplayCode_Update(u32 disTimestamp)
{
	u8 disHour   = disTimestamp / 60 / 60;		// 小时00 ~ 23（24 == 00）
	u8 disMinute = disTimestamp / 60 % 60;		// 分钟00 ~ 59（60 == 00）
	u8 disSecond = disTimestamp % 60;			// 秒  00 ~ 59（60 == 00）
	
	DisplayCode[0] = segCC_SegSel[disHour   / 10];
	DisplayCode[1] = segCC_SegSel[disHour   % 10];
	DisplayCode[3] = segCC_SegSel[disMinute / 10];
	DisplayCode[4] = segCC_SegSel[disMinute % 10];
	DisplayCode[6] = segCC_SegSel[disSecond / 10];
	DisplayCode[7] = segCC_SegSel[disSecond % 10];
}

// 扫描哪个按键按下了
u8 KeyScan()
{
	u8 i, keyVal = 0;
	
	for(i = 0; i < 4; i++)				// 四个按键的扫描
	{
		if(KeyCur[i] != KeyPre[i])		// 当前按键点位值和之前时刻点位值发生变化
		{
			if(KeyPre[i])				// 之前时刻的点位值为高
			{
				keyVal = i + 1;
			}
			KeyPre[i] = KeyCur[i];		// 之前时刻的点位值更新
		}
	}
	
	return(keyVal);
}

// 按键检测，4次扫描状态一样才是置位
void KeyUpdate()
{
	u8 i;
	
	// 把KEYS的值装载到KeyBuff的最后一位
	KeyBuff[0] = (KeyBuff[0] << 1) | K1;
	KeyBuff[1] = (KeyBuff[1] << 1) | K2;
	KeyBuff[2] = (KeyBuff[2] << 1) | K3;
	KeyBuff[3] = (KeyBuff[3] << 1) | K4;
	
	for(i = 0; i < 4; i++)
	{
		if((KeyBuff[i] & 0x0F) == 0x00)			// 表明连续抽检到4个0
		{
			KeyCur[i] = 0;
		}
		else if((KeyBuff[i] & 0x0F) == 0x0F)	// 表明连续抽检到4个1
		{
			KeyCur[i] = 1;
		}
	}
}

void KeyAction(u8 keyVal)
{
	switch(keyVal)
	{
		case 1:
			if(KeyEnable[0])	// 若这个键能按下
			{
				// 打开或关闭定时
				TR0 = !TR0;
				if(!TR0)	// 定时器被关闭了——可以调整时间了，不可以设置闹铃了
				{
					KeyEnable[1] = 1;
					KeyEnable[2] = 1;
					KeyEnable[3] = 0;
				}
				else		// 定时器被打开了——不可以调整时间了，可以设置闹铃了
				{
					KeyEnable[1] = 0;
					KeyEnable[2] = 0;
					KeyEnable[3] = 1;
				}
			}
			break;
		case 2:
			if(KeyEnable[1])	// 若这个键能按下
			{
				// 判断是时间调整还是闹铃设置
				if(KeyEnable[0])	// 时间调整
				{
					timestamp += 60;
					if(timestamp == 86400) timestamp = 0;
				}
				else				// 闹铃设置
				{
					alarmTimestamp += 60;
					if(alarmTimestamp == 86400) alarmTimestamp = 0;
				}
			}
			break;
		case 3:
			if(KeyEnable[2])	// 若这个键能按下
			{
				// 判断是时间调整还是闹铃设置
				if(KeyEnable[0])	// 时间调整
				{
					timestamp += 3600;
					if(timestamp >= 86400) timestamp = 0;
				}
				else				// 闹铃设置
				{
					alarmTimestamp += 3600;
					if(alarmTimestamp >= 86400) alarmTimestamp = 0;
				}
			}
			break;
		case 4:
			if(KeyEnable[3])	// 若这个键能按下
			{
				KeyEnable[0] = !KeyEnable[0];	// 以时间是否可以设置为闹铃是否可以设置的标准
				if(!KeyEnable[0])				// 时间不可调整，闹铃设置开始
				{
					KeyEnable[1] = 1;
					KeyEnable[2] = 1;
				}
				else							// 时间可以调整，闹铃设置结束
				{
					KeyEnable[1] = 0;
					KeyEnable[2] = 0;
				}
			}
			break;
		default: break;
	}
}

// 真正的时间所用定时器
void Timer0Init()
{
	/* 定时器0，工作方式1，或运算防止移植的时候影响其他定时器
	   方式1：16位加1计数器 */
	TMOD |= 0x01;
	
	TR0 = 1;	// 打开定时器0
	
	// 计时50ms
	TH0 = 15536 / 256;
	TL0 = 15536 % 256;
	
	// 定时器0中断和总中断开关打开
	ET0 = 1;
	EA  = 1;
}

// 按键所用的定时器
void Timer1Init()
{
	/* 定时器1，工作方式1，或运算防止移植的时候影响其他定时器
	   方式1：16位加1计数器 */
	TMOD |= 0x10;
	
	TR1 = 1;	// 打开定时器1
	
	// 计时4ms
	TH1 = 61536 / 256;
	TL1 = 61536 % 256;
	
	// 定时器0中断和总中断开关打开
	ET1 = 1;
	// EA  = 1;	// 总中断已打开
}

void main()
{
	u8 keyVal;
	
	Timer0Init();		// 时间所用定时器，中断优先级比较大
	Timer1Init();		// 按键所用定时器，中断优先级比较小
	LED = 1;			// 初始化闹钟状态为关闭状态
	
	while(1)
	{
		// 按键扫描程序
		keyVal = KeyScan();
		KeyAction(keyVal);
		
		// 闹钟你可以响了
		if(timestamp == alarmTimestamp)  LED = 0;
		
		/* 闹铃设置状态打开的时候有个特点：
           就是闹铃设置按钮可以按下，并且时间自增按钮（判断任意一个即可）可以按下 */
		if(KeyEnable[3] && KeyEnable[1]) DisplayCode_Update(alarmTimestamp);
		else 			  			     DisplayCode_Update(timestamp);
		SegDisplay();	// 数码管开始显示最新更新的显示数据
    }
}

void Timer0_50ms() interrupt 1
{
	static u8 tCount = 0;			// 显示时间时所用计数
	
	// 定时器0高低位的赋值
	TH0 = 15536 / 256;
	TL0 = 15536 % 256;
	
	if(++tCount == 20)				// 1s需要记录20个50ms
	{
		// 累加并判断，时间为24-00-00 = 86400时清零
		if(++timestamp >= 86400) timestamp = 0;
		tCount = 0;					// 将静态变量归0
	}
}

void Timer1_4ms() interrupt 3
{
	static u16 LED_tCount = 0;		// 关闭LED时所用计数
	
	// 重装载——4ms
	TH1 = 61536 / 256;
	TL1 = 61536 % 256;
	
	// 闹钟的关闭不大好使用T0因为设置时间的时候T0暂停了
	if(!LED)						// 如果闹钟打开，10s后关闭闹钟
	{
		if(++LED_tCount == 2500)	// 10s需要记录2500个4ms
		{
			LED = 1;
			LED_tCount = 0;			// 将静态变量归0
		}
	}
	
	KeyUpdate();					// 检测按键状态
=======
#include <reg52.h>
#include "74xx138.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif
#ifndef u32
#define u32 unsigned long
#endif

#define SEG_SEL P0					// 段选引脚
sbit LED = P1^0;					// LED使用引脚
// 此处按键的代码由于借给闹钟暂停了，所以没有写出去用key.h调用
sbit K1  = P3^0;					// 设置时间的按键
sbit K2  = P3^1;					// 分钟 + 1
sbit K3  = P3^2;					// 小时 + 1
sbit K4  = P3^3;					// 设置LED（闹铃）的按键

// 共阴数码管段选，从0到9
u8 code segCC_SegSel[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
// 数码管显示数据，初始化00-00-00
u8 DisplayCode[8]        = {0x3f, 0x3f, 0x40, 0x3f, 0x3f, 0x40, 0x3f, 0x3f};

u32 timestamp      = 0;				// 存储显示时间戳的变量
/* 原本可以使用u16类型来定义闹钟时间戳，这样节省内存
   但是考虑到DisplayCode_Update()的修改繁琐，故不优化此处 */
u32 alarmTimestamp = 43200;			// 存储闹铃时间戳的变量，为防止一开始闹钟，设置为12-00-00
/* 数组全初始化只需写一个元素即可 */
u8  KeyCur[4]      = {1};			// 装载当前时刻按键状态值
u8  KeyPre[4]      = {1};			// 装载之前时刻按键状态值
u8  KeyBuff[4]     = {0xFF};		// 装载按键状态缓冲的变量
u8  KeyEnable[4]   = {1, 0, 0, 1};	// 四个按键是否可按的状态变量

// 延时1ms函数
void Delay1ms()
{
    u8 i;
	
	for(i = 0; i < 125; i++);
}

// 数码管显示函数
void SegDisplay()
{	  
	u8 i;
	
	for(i = 0; i < 8; i++)
	{
		_74XX138_SetLow(i);				// 数码管位选
		SEG_SEL = DisplayCode[i];		// 数码管段选
		Delay1ms();
		
		SEG_SEL = 0x00;					// 数码管消隐
	}
}

// 显示时间更新
void DisplayCode_Update(u32 disTimestamp)
{
	u8 disHour   = disTimestamp / 60 / 60;		// 小时00 ~ 23（24 == 00）
	u8 disMinute = disTimestamp / 60 % 60;		// 分钟00 ~ 59（60 == 00）
	u8 disSecond = disTimestamp % 60;			// 秒  00 ~ 59（60 == 00）
	
	DisplayCode[0] = segCC_SegSel[disHour   / 10];
	DisplayCode[1] = segCC_SegSel[disHour   % 10];
	DisplayCode[3] = segCC_SegSel[disMinute / 10];
	DisplayCode[4] = segCC_SegSel[disMinute % 10];
	DisplayCode[6] = segCC_SegSel[disSecond / 10];
	DisplayCode[7] = segCC_SegSel[disSecond % 10];
}

// 扫描哪个按键按下了
u8 KeyScan()
{
	u8 i, keyVal = 0;
	
	for(i = 0; i < 4; i++)				// 四个按键的扫描
	{
		if(KeyCur[i] != KeyPre[i])		// 当前按键点位值和之前时刻点位值发生变化
		{
			if(KeyPre[i])				// 之前时刻的点位值为高
			{
				keyVal = i + 1;
			}
			KeyPre[i] = KeyCur[i];		// 之前时刻的点位值更新
		}
	}
	
	return(keyVal);
}

// 按键检测，4次扫描状态一样才是置位
void KeyUpdate()
{
	u8 i;
	
	// 把KEYS的值装载到KeyBuff的最后一位
	KeyBuff[0] = (KeyBuff[0] << 1) | K1;
	KeyBuff[1] = (KeyBuff[1] << 1) | K2;
	KeyBuff[2] = (KeyBuff[2] << 1) | K3;
	KeyBuff[3] = (KeyBuff[3] << 1) | K4;
	
	for(i = 0; i < 4; i++)
	{
		if((KeyBuff[i] & 0x0F) == 0x00)			// 表明连续抽检到4个0
		{
			KeyCur[i] = 0;
		}
		else if((KeyBuff[i] & 0x0F) == 0x0F)	// 表明连续抽检到4个1
		{
			KeyCur[i] = 1;
		}
	}
}

void KeyAction(u8 keyVal)
{
	switch(keyVal)
	{
		case 1:
			if(KeyEnable[0])	// 若这个键能按下
			{
				// 打开或关闭定时
				TR0 = !TR0;
				if(!TR0)	// 定时器被关闭了——可以调整时间了，不可以设置闹铃了
				{
					KeyEnable[1] = 1;
					KeyEnable[2] = 1;
					KeyEnable[3] = 0;
				}
				else		// 定时器被打开了——不可以调整时间了，可以设置闹铃了
				{
					KeyEnable[1] = 0;
					KeyEnable[2] = 0;
					KeyEnable[3] = 1;
				}
			}
			break;
		case 2:
			if(KeyEnable[1])	// 若这个键能按下
			{
				// 判断是时间调整还是闹铃设置
				if(KeyEnable[0])	// 时间调整
				{
					timestamp += 60;
					if(timestamp == 86400) timestamp = 0;
				}
				else				// 闹铃设置
				{
					alarmTimestamp += 60;
					if(alarmTimestamp == 86400) alarmTimestamp = 0;
				}
			}
			break;
		case 3:
			if(KeyEnable[2])	// 若这个键能按下
			{
				// 判断是时间调整还是闹铃设置
				if(KeyEnable[0])	// 时间调整
				{
					timestamp += 3600;
					if(timestamp >= 86400) timestamp = 0;
				}
				else				// 闹铃设置
				{
					alarmTimestamp += 3600;
					if(alarmTimestamp >= 86400) alarmTimestamp = 0;
				}
			}
			break;
		case 4:
			if(KeyEnable[3])	// 若这个键能按下
			{
				KeyEnable[0] = !KeyEnable[0];	// 以时间是否可以设置为闹铃是否可以设置的标准
				if(!KeyEnable[0])				// 时间不可调整，闹铃设置开始
				{
					KeyEnable[1] = 1;
					KeyEnable[2] = 1;
				}
				else							// 时间可以调整，闹铃设置结束
				{
					KeyEnable[1] = 0;
					KeyEnable[2] = 0;
				}
			}
			break;
		default: break;
	}
}

// 真正的时间所用定时器
void Timer0Init()
{
	/* 定时器0，工作方式1，或运算防止移植的时候影响其他定时器
	   方式1：16位加1计数器 */
	TMOD |= 0x01;
	
	TR0 = 1;	// 打开定时器0
	
	// 计时50ms
	TH0 = 15536 / 256;
	TL0 = 15536 % 256;
	
	// 定时器0中断和总中断开关打开
	ET0 = 1;
	EA  = 1;
}

// 按键所用的定时器
void Timer1Init()
{
	/* 定时器1，工作方式1，或运算防止移植的时候影响其他定时器
	   方式1：16位加1计数器 */
	TMOD |= 0x10;
	
	TR1 = 1;	// 打开定时器1
	
	// 计时4ms
	TH1 = 61536 / 256;
	TL1 = 61536 % 256;
	
	// 定时器0中断和总中断开关打开
	ET1 = 1;
	// EA  = 1;	// 总中断已打开
}

void main()
{
	u8 keyVal;
	
	Timer0Init();		// 时间所用定时器，中断优先级比较大
	Timer1Init();		// 按键所用定时器，中断优先级比较小
	LED = 1;			// 初始化闹钟状态为关闭状态
	
	while(1)
	{
		// 按键扫描程序
		keyVal = KeyScan();
		KeyAction(keyVal);
		
		// 闹钟你可以响了
		if(timestamp == alarmTimestamp)  LED = 0;
		
		/* 闹铃设置状态打开的时候有个特点：
           就是闹铃设置按钮可以按下，并且时间自增按钮（判断任意一个即可）可以按下 */
		if(KeyEnable[3] && KeyEnable[1]) DisplayCode_Update(alarmTimestamp);
		else 			  			     DisplayCode_Update(timestamp);
		SegDisplay();	// 数码管开始显示最新更新的显示数据
    }
}

void Timer0_50ms() interrupt 1
{
	static u8 tCount = 0;			// 显示时间时所用计数
	
	// 定时器0高低位的赋值
	TH0 = 15536 / 256;
	TL0 = 15536 % 256;
	
	if(++tCount == 20)				// 1s需要记录20个50ms
	{
		// 累加并判断，时间为24-00-00 = 86400时清零
		if(++timestamp >= 86400) timestamp = 0;
		tCount = 0;					// 将静态变量归0
	}
}

void Timer1_4ms() interrupt 3
{
	static u16 LED_tCount = 0;		// 关闭LED时所用计数
	
	// 重装载——4ms
	TH1 = 61536 / 256;
	TL1 = 61536 % 256;
	
	// 闹钟的关闭不大好使用T0因为设置时间的时候T0暂停了
	if(!LED)						// 如果闹钟打开，10s后关闭闹钟
	{
		if(++LED_tCount == 2500)	// 10s需要记录2500个4ms
		{
			LED = 1;
			LED_tCount = 0;			// 将静态变量归0
		}
	}
	
	KeyUpdate();					// 检测按键状态
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
}