/* �ⲿ�ж�1�����½��ش��� */

#include <reg52.h>

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

#define LED P0				// ����LED����P0
sbit KEY = P3^2;			// ���崥���ⲿ�ж�0�İ���

// �ⲿ�ж�0��ʼ������
void EINT1_Init()
{
	// ������ʽ���½��ش���
	IT0 = 1;
	// �����ⲿ�ж�1
	EX1 = 1;
	// ����ȫ���ж�
	EA  = 1;
}

void Delay10ms()   			//��� 0us
{
    u8 a, b, c;
    for(c = 1; c > 0; c--)
        for(b = 38; b > 0; b--)
            for(a = 130; a > 0; a--);
}

void main()
{
	LED = 0x33;				// LED��ʾ��0011 0011
	EINT1_Init();
	while(1);
}

/* 1. �жϺ������Բ�д��������
   2. �жϺ������Լ�һ��using��ʾʹ�õļĴ����飨0 ~ 3�� */
void EINT1() interrupt 2
{
	// �����ж�ʱ��LED������״̬��ת
	
	// ----!!!!!!!!�˴��İ������򲻱�׼������Ϊ����ʹ��!!!!!!!!----
	if(!INT1)				// �������¾��ǽ�GND
	{
		Delay10ms();
		while(!INT1);		// �жϰ����Ƿ��ɿ�
		LED = ~LED;
	}
}