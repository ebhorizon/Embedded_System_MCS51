#include "relay.h"

// �򿪣�1������ϣ�0���̵���
void Relay_Switch(u8 on_off)
{
	Relay = !on_off;
}