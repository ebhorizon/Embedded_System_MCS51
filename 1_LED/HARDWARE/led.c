#include "led.h"

void LED_Delay(u16 t)
{
	while(t--);
}

// ��ʼ��ȫ��
void LED_Init()
{
	LED	= LED_DEFAULT;
	LED_Delay(50000);
	LED_Delay(50000);
}

// LED0λ��������
void LED0_Light_Bit()
{
	LED_Init();
	LED0 = (~LED_DEFAULT) & 0x01;	// ȡ�������λ
	LED_Delay(50000);
}

// LED0�ֲ�������
void LED0_Light_Word()
{
	LED_Init();
	// �˴��޸Ŀ��Ե�����λ
	LED0 |= ~LED_DEFAULT;
	LED_Delay(50000);
}

// LED0��˸
void LED0_Flash(u8 flashCount)
{
	LED_Init();
	for(; flashCount > 0; flashCount--)
	{
		// �ı��ӳ�ʱ����Ըı���˸Ƶ��
		LED0 = (~LED_DEFAULT) & 0x01;	// ȡ�������λ
		LED_Delay(20000);
		LED0 = LED_DEFAULT    & 0x01;	// ȡ�������λ
		LED_Delay(20000);
	}
}

// LED����
void LED_ToLeft()
{
	u8 i, ledStat;
	
	LED_Init();
	ledStat = 0x01;
	// �˴��õ���ȡ��˼��Ҫ��ס
	(LED_DEFAULT == 0x00) ? (LED = ledStat) : (LED = ~ledStat);
	for(i = 0; i < 8; i++)
	{
		LED_Delay(10000);
		ledStat = ledStat << 1;
		(LED_DEFAULT == 0x00) ? (LED = ledStat) : (LED = ~ledStat);
	}	
	LED_Delay(10000);
}

// LED����
void LED_ToRight()
{
	u8 i, ledStat;
	
	LED_Init();
	ledStat = 0x80;
	(LED_DEFAULT == 0x00) ? (LED = ledStat) : (LED = ~ledStat);
	for(i = 0; i < 8; i++)
	{
		LED_Delay(10000);
		ledStat = ledStat >> 1;
		(LED_DEFAULT == 0x00) ? (LED = ledStat) : (LED = ~ledStat);
	}	
	LED_Delay(10000);
}

// LEDѭ������
// ���Բο������ȡ��˼�룬Ҳ����ֱ�ӵ��ÿ⺯�����ȽϷ���ı�׼������
void LED_ROL(u8 ROLCount)
{
	u8 i;
	
	LED_Init();
	for(; ROLCount > 0; ROLCount--)
	{
		(LED_DEFAULT == 0x00) ? (LED = 0x01) : (LED = 0xFE);
		for(i = 0; i < 7; i++)
		{
			LED_Delay(10000);
			LED = _crol_(LED, 1);
		}
		LED_Delay(10000);
	}
}

// LEDѭ������
void LED_ROR(u8 RORCount)
{
	u8 i;
	
	LED_Init();
	for(; RORCount > 0; RORCount--)
	{
		(LED_DEFAULT == 0x00) ? (LED = 0x80) : (LED = 0x7F);
		for(i = 0; i < 7; i++)
		{
			LED_Delay(10000);
			LED = _cror_(LED, 1);
		}
		LED_Delay(10000);
	}
}

// ��������������ɷ����ˣ�����׸��

// PWM��������ƣ���������
// ԭ��ܼ򵥣��ı�ߵ�ƽ������˵�����ĵ�ƽ����ռ��ʱ�䡪��ռ�ձȼ���
void LED_PWM(u8 PWMCount)
{
	u16  T    = 500;
	u16  Toff = 0;
	
	LED_Init();
	for(; PWMCount > 0; PWMCount--)
	{
		for(Toff = 1; Toff < T; Toff++)
		{
			(LED_DEFAULT == 0x00) ? (LED = 0xFF) : (LED = 0x00);
			LED_Delay(Toff);
			
			(LED_DEFAULT == 0x00) ? (LED = 0x00) : (LED = 0xFF);
			LED_Delay(T - Toff);
		}
		
		for(Toff = T - 1; Toff > 0 ; Toff--)
		{
			(LED_DEFAULT == 0x00) ? (LED = 0xFF) : (LED = 0x00);
			LED_Delay(Toff);
			
			(LED_DEFAULT == 0x00) ? (LED = 0x00) : (LED = 0xFF);
			LED_Delay(T - Toff);
		}
	}
}
