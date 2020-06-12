#include <reg52.h>
#include "key.h"

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

// ��������Ҷ�Ӧλ�õ�LED
#define LEDS P0

void main()
{
	u8 keyVal = 0;
	
	KeyInit();
	LEDS = 0x00;
	while(1)
	{
		// ��ⰴ���Ƿ��������ض�Ӧ�ļ�ֵ
		keyVal = KeyScan();
		if(keyVal)
		{
			LEDS = 0x01 << (keyVal - 1);
		}
    } 
}