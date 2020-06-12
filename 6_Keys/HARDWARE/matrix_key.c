#include "matrix_key.h"

// 装载当前时刻按键状态值
u8 MatrixKeyCur[4][4]  = {1};
// 装载之前时刻按键状态值
u8 MatrixKeyPre[4][4]  = {1};
// 四次按键扫描缓冲
u8 MatrixKeyBuff[4][4] = {0xFF};
u8 code Col_Sel[4] = {0xEF, 0xDF, 0xBF, 0x7F};

void TINT0_Init()
{
	// 方式1
	TMOD |= 0x01;
	// 打开定时器0
	TR0   = 1;
	// 装载——4ms = 4000us
	TH0   = (65536 - 4000) / 256;
	TL0   = (65536 - 4000) % 256;
	// 打开两个中断开关
	EA    = 1;
	ET0   = 1;
}

// 扫描哪个按键按下了
u8 MatrixKeyScan()
{
	u8 i, j, keyVal = 0;
	
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			// 当前按键点位值和之前时刻点位值发生变化
			if(MatrixKeyCur[i][j] != MatrixKeyPre[i][j])
			{
				// 之前时刻的点位值为高
				if(MatrixKeyPre[i][j])
				{
					/* 1	2	3	4
                       5	6	7	8
					   9	10	11	12
					   13	14	15	16 */
					keyVal = 4 * j + i + 1;
				}
				// 之前时刻的点位值更新
				MatrixKeyPre[i][j] = MatrixKeyCur[i][j];
			}
		}
	}
	
	return(keyVal);
}

// 按键检测，4次扫描状态一样才是置位
void MatrixKeyUpdate()
{
	u8 i, j;
	
	for(i = 0; i < 4; i++)
	{
		// 1110 1111, 1101 1111, 1011 1111, 0111 1111
		MATRIXKEYS = Col_Sel[i];
		
		for(j = 0; j < 4; j++)
		{
			// 把KEYS的值装载到KeyBuff的最后一位
			MatrixKeyBuff[i][j] = (MatrixKeyBuff[i][j] << 1) | (MATRIXKEYS >> j & 0x01);
		}
		
		for(j = 0; j < 4; j++)
		{			
			// 表明连续抽检到4个0
			if((MatrixKeyBuff[i][j] & 0x0F) == 0x00)
			{
				MatrixKeyCur[i][j] = 0;
			}
			// 表明连续抽检到4个1
			else if((MatrixKeyBuff[i][j] & 0x0F) == 0x0F)
			{
				MatrixKeyCur[i][j] = 1;
			}
		}
	}
}

void MatrixKeyInit()
{
	TINT0_Init();
}

void TINT0_4ms() interrupt 1
{
	// 重装载——4ms
	TH0 = (65536 - 4000) / 256;
	TL0 = (65536 - 4000) % 256;
	MatrixKeyUpdate();
}