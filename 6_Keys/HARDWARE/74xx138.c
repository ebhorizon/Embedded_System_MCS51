#include "74xx138.h"

// 输入使第几位为低电平
void _74XX138_SetLow(u8 dat)
{
	// 使用8421BCD的思想来编写译码器算法
	_74XX138_C = (dat >= 4 ? 1 : 0);
	if(dat >= 4) dat -= 4;
	_74XX138_B = (dat >= 2 ? 1 : 0);
	if(dat >= 2) dat -= 2;
	_74XX138_A = (dat >= 1 ? 1 : 0);
}

