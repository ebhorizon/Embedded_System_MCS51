#ifndef _BUZZER_H_
#define _BUZZER_H_

#include <reg52.h>

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// �����ѡ12MHz��11.0592MHz
#define CRYSTAL 12

// ������4/4��1����3/4��2����2/4��3����
#define PAT     3

sbit Buzzer = P1^5;

// ��������ʼ��
void Buzzer_Init();
// ��������������
void Buzzer_Play(u8 index, u16 delay);

#endif