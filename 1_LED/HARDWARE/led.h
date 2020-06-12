#ifndef _LED_H_
#define _LED_H_

#include <reg52.h>
#include <intrins.h>

// ���峣������
#ifndef	u16
#define	u16	unsigned int
#endif
#ifndef	u8
#define	u8	unsigned char
#endif

// ����LED * 8��P0��
#define LED	P0
sbit LED0 = P0^0;			// ʹ��P0.0����LED0

// ����LEDһ�˽�GND����VCC
#define LED_DEFAULT 0x00	// Ĭ�Ͻӵصĳ�ʼ��

// LED0λ��������
void LED0_Light_Bit();
// LED0�ֲ�������
void LED0_Light_Word();
// LED0��˸
void LED0_Flash(u8 flashCount);
// LED����
void LED_ToLeft();
// LED����
void LED_ToRight();
// LEDѭ������
void LED_ROL(u8 ROLCount);
// LEDѭ������
void LED_ROR(u8 RORCount);
// PWM��������ƣ���������
void LED_PWM(u8 PWMCount);

#endif
