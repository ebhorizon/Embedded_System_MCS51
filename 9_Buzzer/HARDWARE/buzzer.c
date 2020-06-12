#include "buzzer.h"

/* 钢琴的88键音频率计算法：
   十二平均律的音阶系数为2^(1 / 12) = 1.0594630944，A1为27.5Hz，从而可得频率值
   为了减少计算时带来的时间延迟，保存各个A阶（A1 ~ A8）为数组即可 */
float code Freq_A[8] = {27.5, 55.0, 110.0, 220.0, 440.0, 880.0, 1760.0, 3520.0};
// 提前计算音阶系数
float Coef = 1.0594630944;
u8 TINT0_H, TINT0_L;

void Buzzer_Delay_nms(u16 t)
{
	u8 i = 245;
	
	while(t--)
	{
		while(i--);
		i = 245;
		while(i--);
	}
}

// 返回频率的定时器初值设置值
#if CRYSTAL == 12
u16 Buzzer_InitValue(u8 index)
{
	float Freq = 0.0;
	u8 i;
	
	Freq += Freq_A[index / 12];
	for(i = 0; i < (index - 1) % 12; i++)
	{
		Freq *= Coef;
	}
	
	return((u16)(65536 - 500000 / Freq));
}
#elif CRYSTAL == 11.0592
u16 Buzzer_InitValue(u8 index)
{
	float Freq = 0.0;
	u8 i;
	
	Freq += Freq_A[index / 12];
	for(i = 0; i < (index - 1) % 12; i++)
	{
		Freq *= Coef;
	}
	
	return((u16)(65536 - 460800 / Freq));
}
#endif

// 定时器0初始化
void TINT0_Init()
{
	TMOD |= 0x01;
	ET0   = 1;
	EA    = 1;
}

// 蜂鸣器初始化
void Buzzer_Init()
{
	TINT0_Init();	// 音调定时器
}

// 蜂鸣器发声函数
void Buzzer_Play(u8 index, u16 delay)
{
	u16 initVal = Buzzer_InitValue(index); 
	
	TINT0_H   = initVal / 256;
	TINT0_L   = initVal % 256;
	TH0       = TINT0_H;				// 赋值定时器时间，决定频率
	TL0       = TINT0_L;
	TR0       = 1;       				// 打开定时器0播放
	Buzzer_Delay_nms(delay);
}

void TINT0() interrupt 1
{
	TR0    = 0;

	Buzzer = !Buzzer;
	TH0    = TINT0_H;
	TL0    = TINT0_L;
	
	TR0    = 1;
}