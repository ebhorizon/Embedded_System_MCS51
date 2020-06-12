<<<<<<< HEAD
#include "key.h"

u8 KeyCur[8]  = {1};		// 装载当前时刻按键状态值
u8 KeyPre[8]  = {1};		// 装载之前时刻按键状态值
u8 KeyBuff[8] = {0xFF};

void TINT0_Init()
{
	// 方式1
	TMOD |= 0x01;
	// 打开定时器0
	TR0   = 1;
	// 装载——4ms
	TH0   = (65536 - 4000) / 256;
	TL0   = (65536 - 4000) % 256;
	// 打开中断
	EA    = 1;
	ET0   = 1;
}

// 扫描哪个按键按下了
u8 KeyScan()
{
	u8 i, keyVal = 0;
	
	for(i = 0; i < 8; i++)
	{
		// 当前按键点位值和之前时刻点位值发生变化
		if(KeyCur[i] != KeyPre[i])
		{
			// 之前时刻的点位值为高
			if(KeyPre[i])
			{
				keyVal = i + 1;
			}
			// 之前时刻的点位值更新
			KeyPre[i] = KeyCur[i];
		}
	}
	
	return(keyVal);
}

// 按键检测，4次扫描状态一样才是置位
void KeyUpdate()
{
	u8 i;
	
	for(i = 0; i < 8; i++)
	{
		// 把KEYS的值装载到KeyBuff的最后一位
		KeyBuff[i] = (KeyBuff[i] << 1) | (KEYS >> i & 0x01);
	}
	
	for(i = 0; i < 8; i++)
	{
		// 表明连续抽检到4个0
		if((KeyBuff[i] & 0x0F) == 0x00)
		{
			KeyCur[i] = 0;
		}
		// 表明连续抽检到4个1
		else if((KeyBuff[i] & 0x0F) == 0x0F)
		{
			KeyCur[i] = 1;
		}
	}
}

void KeyInit()
{
	TINT0_Init();
}

void TINT0_4ms() interrupt 1
{
	// 重装载——4ms
	TH0 = (65536 - 4000) / 256;
	TL0 = (65536 - 4000) % 256;
	KeyUpdate();
=======
#include "key.h"

u8 KeyCur[8]  = {1};		// 装载当前时刻按键状态值
u8 KeyPre[8]  = {1};		// 装载之前时刻按键状态值
u8 KeyBuff[8] = {0xFF};

void TINT0_Init()
{
	// 方式1
	TMOD |= 0x01;
	// 打开定时器0
	TR0   = 1;
	// 装载——4ms
	TH0   = (65536 - 4000) / 256;
	TL0   = (65536 - 4000) % 256;
	// 打开中断
	EA    = 1;
	ET0   = 1;
}

// 扫描哪个按键按下了
u8 KeyScan()
{
	u8 i, keyVal = 0;
	
	for(i = 0; i < 8; i++)
	{
		// 当前按键点位值和之前时刻点位值发生变化
		if(KeyCur[i] != KeyPre[i])
		{
			// 之前时刻的点位值为高
			if(KeyPre[i])
			{
				keyVal = i + 1;
			}
			// 之前时刻的点位值更新
			KeyPre[i] = KeyCur[i];
		}
	}
	
	return(keyVal);
}

// 按键检测，4次扫描状态一样才是置位
void KeyUpdate()
{
	u8 i;
	
	for(i = 0; i < 8; i++)
	{
		// 把KEYS的值装载到KeyBuff的最后一位
		KeyBuff[i] = (KeyBuff[i] << 1) | (KEYS >> i & 0x01);
	}
	
	for(i = 0; i < 8; i++)
	{
		// 表明连续抽检到4个0
		if((KeyBuff[i] & 0x0F) == 0x00)
		{
			KeyCur[i] = 0;
		}
		// 表明连续抽检到4个1
		else if((KeyBuff[i] & 0x0F) == 0x0F)
		{
			KeyCur[i] = 1;
		}
	}
}

void KeyInit()
{
	TINT0_Init();
}

void TINT0_4ms() interrupt 1
{
	// 重装载——4ms
	TH0 = (65536 - 4000) / 256;
	TL0 = (65536 - 4000) % 256;
	KeyUpdate();
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
}