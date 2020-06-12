#include <reg52.h>
#include "led.h"

void main()
{
	while(1)
	{
		// LED0位操作点亮
		LED0_Light_Bit();
		// LED0字操作点亮
		LED0_Light_Word();
		// LED0闪烁
		LED0_Flash(5);
		// LED左移
		LED_ToLeft();
		// LED右移
		LED_ToRight();
		// LED循环左移
		LED_ROL(2);
		// LED循环右移
		LED_ROR(2);
		// PWM（脉宽调制）调节亮度
		LED_PWM(2);
	}
}