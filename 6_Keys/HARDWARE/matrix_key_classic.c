<<<<<<< HEAD
#include "matrix_key_classic.h"

void MatrixKeyDelay(u16 t)
{
	while(t--);
}

// 扫描哪个按键按下了
u8 MatrixKeyScan()
{
	u8 k = 0, keyVal = 0;
	
	// 置0000 1111
	MATRIXKEYS = 0x0F;
	// 判断如果按下了
	if(MATRIXKEYS != 0x0F)
	{
		MatrixKeyDelay(1000);					// 消抖
		switch(MATRIXKEYS)
		{
			case 0x07: keyVal = 1; break;		// 0000 0111
			case 0x0B: keyVal = 2; break;		// 0000 1011
			case 0x0D: keyVal = 3; break;		// 0000 1101
			case 0x0E: keyVal = 4; break;		// 0000 1110
		}
		
		// 立马置1111 0000
		MATRIXKEYS = 0xF0;
		switch(MATRIXKEYS)
		{
			case 0x70: 				 break;		// 0111 0000
			case 0xB0: keyVal += 4;  break;		// 1011 0000
			case 0xD0: keyVal += 8;  break;		// 1101 0000
			case 0xE0: keyVal += 12; break;		// 1110 0000
		}
		
		// 等待释放的过程延迟500ms强制释放
		while((k++ < 50) && (MATRIXKEYS != 0xF0))	MatrixKeyDelay(1000);
	}
	
	return keyVal;
=======
#include "matrix_key_classic.h"

void MatrixKeyDelay(u16 t)
{
	while(t--);
}

// 扫描哪个按键按下了
u8 MatrixKeyScan()
{
	u8 k = 0, keyVal = 0;
	
	// 置0000 1111
	MATRIXKEYS = 0x0F;
	// 判断如果按下了
	if(MATRIXKEYS != 0x0F)
	{
		MatrixKeyDelay(1000);					// 消抖
		switch(MATRIXKEYS)
		{
			case 0x07: keyVal = 1; break;		// 0000 0111
			case 0x0B: keyVal = 2; break;		// 0000 1011
			case 0x0D: keyVal = 3; break;		// 0000 1101
			case 0x0E: keyVal = 4; break;		// 0000 1110
		}
		
		// 立马置1111 0000
		MATRIXKEYS = 0xF0;
		switch(MATRIXKEYS)
		{
			case 0x70: 				 break;		// 0111 0000
			case 0xB0: keyVal += 4;  break;		// 1011 0000
			case 0xD0: keyVal += 8;  break;		// 1101 0000
			case 0xE0: keyVal += 12; break;		// 1110 0000
		}
		
		// 等待释放的过程延迟500ms强制释放
		while((k++ < 50) && (MATRIXKEYS != 0xF0))	MatrixKeyDelay(1000);
	}
	
	return keyVal;
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
}