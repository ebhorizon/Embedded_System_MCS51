<<<<<<< HEAD
#include "74xx138.h"

// ����ʹ�ڼ�λΪ�͵�ƽ
void _74XX138_SetLow(u8 dat)
{
	// ʹ��8421BCD��˼������д�������㷨
	_74XX138_C = (dat >= 4 ? 1 : 0);
	if(dat >= 4) dat -= 4;
	_74XX138_B = (dat >= 2 ? 1 : 0);
	if(dat >= 2) dat -= 2;
	_74XX138_A = (dat >= 1 ? 1 : 0);
}

=======
#include "74xx138.h"

// ����ʹ�ڼ�λΪ�͵�ƽ
void _74XX138_SetLow(u8 dat)
{
	// ʹ��8421BCD��˼������д�������㷨
	_74XX138_C = (dat >= 4 ? 1 : 0);
	if(dat >= 4) dat -= 4;
	_74XX138_B = (dat >= 2 ? 1 : 0);
	if(dat >= 2) dat -= 2;
	_74XX138_A = (dat >= 1 ? 1 : 0);
}

>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
