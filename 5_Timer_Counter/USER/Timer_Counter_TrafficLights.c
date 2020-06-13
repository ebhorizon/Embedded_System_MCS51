#include <reg52.h>
#include "74xx138.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

#define GPIO_DIG     P0
#define GPIO_TRAFFIC P1

sbit RED10    = P1^0;
sbit GREEN10  = P1^1;
sbit RED11    = P1^2;
sbit YELLOW11 = P1^3;
sbit GREEN11  = P1^4;
sbit RED00    = P3^0;
sbit GREEN00  = P3^1;
sbit RED01    = P1^5;
sbit YELLOW01 = P1^6;
sbit GREEN01  = P1^7;

/** 0 ~ F, common cathode, point: 0x80, none: 0x00 */
u8 code segDis_cat[16] = {0x3f, 0x06, 0x5b, 0x4f,0x66, 0x6d, 0x7d, 0x07,
                          0x7f, 0x6f, 0x77, 0x7c,0x39, 0x5e, 0x79, 0x71};

u8 DisplayData[8];
u8 Second = 1;

void delay(u16 i)
{
    // Dynamic display
    while(i--);
}

void Timer0Init()
{
    TMOD |= 0x01;
    TH0   = 64536 / 256;
    TL0   = 64536 % 256;
    ET0   = 1;
    EA    = 1;
    TR0   = 1;
}

void DigDisplay()
{
    u8 i = 0;
    for(i = 0; i < 8; i++)
    {
        _74XX138_SetLow(i);
        GPIO_DIG = DisplayData[i];
        delay(100);
        GPIO_DIG = 0x00;
    }
}

void main()
{
    Timer0Init();
    while(1)
    {
		DisplayData[0] = 0x00;
        DisplayData[1] = 0x00;
		DisplayData[4] = 0x00;
        DisplayData[5] = 0x00;
		
        if(Second == 71) Second = 1;
		
        if(Second <= 30)
        {
            DisplayData[2] = segDis_cat[(31 - Second) % 100 / 10];
            DisplayData[3] = segDis_cat[(31 - Second) % 10];
            DisplayData[6] = DisplayData[2];
            DisplayData[7] = DisplayData[3];

            DigDisplay();
			
			// Turn off all
			GPIO_TRAFFIC = 0xff;
			RED00        = 1;
			GREEN00      = 1;

            GREEN11 = 0;
            GREEN10 = 0;

            RED01   = 0;
            RED00   = 0;
        }
        else if(Second <= 35)
        {
            DisplayData[2] = segDis_cat[(36 - Second) % 100 / 10];
            DisplayData[3] = segDis_cat[(36 - Second) % 10];
            DisplayData[6] = DisplayData[2];
            DisplayData[7] = DisplayData[3];

            DigDisplay();
			
			// Turn off all
			GPIO_TRAFFIC = 0xff;
			RED00        = 1;
			GREEN00      = 1;

            YELLOW11 = 0;
            RED10    = 0;

            RED01    = 0;
            RED00    = 0;
        }
        else if(Second <= 65)
        {
            DisplayData[2] = segDis_cat[(66 - Second) % 100 / 10];
            DisplayData[3] = segDis_cat[(66 - Second) % 10];
            DisplayData[6] = DisplayData[2];
            DisplayData[7] = DisplayData[3];

            DigDisplay();
			
			// Turn off all
			GPIO_TRAFFIC = 0xff;
			RED00        = 1;
			GREEN00      = 1;

            RED11   = 0;
            RED10   = 0;

            GREEN01 = 0;
            GREEN00 = 0;
        }
        else
        {
            DisplayData[2] = segDis_cat[(71 - Second) % 100 / 10];
            DisplayData[3] = segDis_cat[(71 - Second) % 10];
            DisplayData[6] = DisplayData[2];
            DisplayData[7] = DisplayData[3];

            DigDisplay();
			
			// Turn off all
			GPIO_TRAFFIC = 0xff;
			RED00        = 1;
			GREEN00      = 1;

            RED11    = 0;
            RED10    = 0;

            YELLOW01 = 0;
            RED00    = 0;
        }
    }
}

void TINT0_1ms() interrupt 1
{
    // 1s
    static u16 i = 0;

    TH0 = 64536 / 256;
    TL0 = 64536 % 256;

    if(++i == 1000)
    {
        i = 0;
        Second++;
    }
}