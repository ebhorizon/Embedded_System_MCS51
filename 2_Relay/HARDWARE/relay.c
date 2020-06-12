#include "relay.h"

// 打开（1）或关上（0）继电器
void Relay_Switch(u8 on_off)
{
	Relay = !on_off;
}