#include "4gpio_matrix_key.h"

void GPIOKeyDelay(u16 t)
{
	while(t--);
}

// 扫描哪个按键按下了
u8 GPIOKeyScan()
{
    u8 keyVal;
	
    GPIOKEYS |= 0x0F;
    keyVal    = GPIOKEYS & 0x0F;
    if(keyVal != 0x0F)
    {
        switch(keyVal)
        {
			case 0x0E: return(4);
			case 0x0D: return(8);
			case 0x0B: return(12);
			case 0x07: return(16);
			default:   return(0);
        }
    }
	GPIOKEYS &= 0xF0;		// 要记得清空！！
	
    GPIOKEYS |= 0x0E;
    keyVal    = GPIOKEYS & 0x0F;
    if(keyVal != 0x0E)
    {
        switch(keyVal)
        {
			case 0x0C: return(5);
			case 0x0A: return(9);
			case 0x06: return(13);
			default:   return(0);
        }
    }
	GPIOKEYS &= 0xF0;		// 要记得清空！！
	
    GPIOKEYS |= 0x0D;
    keyVal    = GPIOKEYS & 0x0F;
    if(keyVal != 0x0D)
    {
        switch(keyVal)
        {
			case 0x0c: return(1);
			case 0x09: return(10);
			case 0x05: return(14);
			default:   return(0);
        }
    }
	GPIOKEYS &= 0xF0;		// 要记得清空！！
	
    GPIOKEYS |= 0x0B;
    keyVal    = GPIOKEYS & 0x0F;
    if(keyVal != 0x0B)
    {
        switch(keyVal)
        {
			case 0x0A: return(2);
			case 0x09: return(6);
			case 0x03: return(15);
			default:   return(0);
        }
    }
	GPIOKEYS &= 0xF0;		// 要记得清空！！
	
    GPIOKEYS |= 0x07;
    keyVal    = GPIOKEYS & 0x0F;
    if(keyVal != 0x07)
    {
        switch(keyVal)
        {
			case 0x06: return(3);
			case 0x05: return(7);
			case 0x03: return(11);
			default:   return(0);
        }
    }
	
	// 没有键按下
    return(0);
}

// 加消抖的扫描
u8 GPIOKeyScanAgain()
{
    u8 keyVal;
	
    keyVal = GPIOKeyScan();
    if(keyVal) GPIOKeyDelay(1000);
    if(keyVal != GPIOKeyScan()) keyVal = 0;
    return(keyVal);
}