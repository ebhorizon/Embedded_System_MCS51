#ifndef _RELAY_H_
#define _RELAY_H_

#include <reg52.h>

// ���峣������
#ifndef u8
#define u8  unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

sbit Relay = P1^4;

// �򿪣�1������ϣ�0���̵���
void Relay_Switch(u8 on_off);

#endif