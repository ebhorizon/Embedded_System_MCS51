#include "uln2003.h"

// 开关函数，只使用u8的低4位，低到高分别为A到D
void ULN2003_DCBA_Switch(u8 DCBA)
{
	ULN2003_A_IN = (DCBA & 0x01) ? 1 : 0;
	DCBA >>= 1;
	ULN2003_B_IN = (DCBA & 0x01) ? 1 : 0;
	DCBA >>= 1;
	ULN2003_C_IN = (DCBA & 0x01) ? 1 : 0;
	DCBA >>= 1;
	ULN2003_D_IN = (DCBA & 0x01) ? 1 : 0;
}