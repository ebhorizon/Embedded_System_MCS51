#include <reg52.h>
#include "led.h"

void main()
{
	while(1)
	{
		// LED0λ��������
		LED0_Light_Bit();
		// LED0�ֲ�������
		LED0_Light_Word();
		// LED0��˸
		LED0_Flash(5);
		// LED����
		LED_ToLeft();
		// LED����
		LED_ToRight();
		// LEDѭ������
		LED_ROL(2);
		// LEDѭ������
		LED_ROR(2);
		// PWM��������ƣ���������
		LED_PWM(2);
	}
}