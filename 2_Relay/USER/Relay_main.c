<<<<<<< HEAD
#include <reg52.h>
#include "relay.h"

// 定义常用类型
#ifndef u8
#define u8  unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

void Delay(u16 t)
{
	while(t--);
}

void main()
{
	while(1)
	{
		Relay_Switch(1);
		Delay(60000);
		Relay_Switch(0);
		Delay(60000);
	}
=======
#include <reg52.h>
#include "relay.h"

// 定义常用类型
#ifndef u8
#define u8  unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

void Delay(u16 t)
{
	while(t--);
}

void main()
{
	while(1)
	{
		Relay_Switch(1);
		Delay(60000);
		Relay_Switch(0);
		Delay(60000);
	}
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
}