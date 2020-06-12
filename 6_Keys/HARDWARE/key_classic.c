<<<<<<< HEAD
#include "key_classic.h"

void KeyDelay_Classic(u16 t)
{
	while(t--);
}

// 普通的按键程序——效果其实也不错
u8 KeyScan_Classic()
{
	u8 i, keyVal = 0;
	
	for(i = 0; i < 8; i++)
	{
		if((KEYS >> i & 0x01) == 0)
		{
			KeyDelay_Classic(1000);
			if((KEYS >> i & 0x01) == 0) keyVal = i + 1;
			while((KEYS >> i & 0x01) == 0);
		}
	}
	
	return keyVal;
=======
#include "key_classic.h"

void KeyDelay_Classic(u16 t)
{
	while(t--);
}

// 普通的按键程序——效果其实也不错
u8 KeyScan_Classic()
{
	u8 i, keyVal = 0;
	
	for(i = 0; i < 8; i++)
	{
		if((KEYS >> i & 0x01) == 0)
		{
			KeyDelay_Classic(1000);
			if((KEYS >> i & 0x01) == 0) keyVal = i + 1;
			while((KEYS >> i & 0x01) == 0);
		}
	}
	
	return keyVal;
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
}