// ��������ԭ�����Ǹ��ߵ͵�ƽ�����Լ��ӳ�ʹ�䷢��
#include <reg52.h>
#include "buzzer.h"

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

// ��ϲ���㡷
//u8 code music_score[] = 
//{/* 1   2   3   4   5   6   7   8   9   10  11  12 */ 
//	42, 42, 42, 44, 42, 40, 35, 40,
//	39, 37, 32,
//	42, 42, 42, 44, 42, 40, 35, 40,
//	39, 40, 39, 37, 37, 40,
//	44, 42, 42, 40, 42, 37, 40,
//	44, 42, 42, 40, 42,
//	42, 42, 42, 44, 42, 40, 35, 40,
//	39, 37, 32,
//	42, 42, 42, 44, 42, 40, 35, 40,
//	39, 40, 39, 37, 37, 40,
//	44, 42, 42, 40, 42, 37, 40,
//	44, 42, 42, 40, 42,
//	47, 44, 42, 40, 39, 40, 42, 44, 44, 44, 42, 40, 
//	40, 40, 42, 40, 39,
//	37, 40, 42, 40, 39,
//	37, 39, 40,
//	42, 44, 44, 42, 40,
//	40, 40, 42, 40, 39,
//	37, 40, 42, 40, 39,
//	37, 39, 40,
//	42, 40, 39,
//	40
//};
//// ���׸���ӳ�Ҫ����2.5
//u16 code music_delay[] = 
//{
//	325, 125, 250, 250, 250, 250, 250, 500,
//	500, 125, 875,
//	325, 125, 250, 250, 250, 250, 250, 500,
//	500, 125, 125, 500, 250, 250,
//	250, 250, 250, 125, 625, 250, 250,
//	250, 250, 250, 250, 1000,
//	325, 125, 250, 250, 250, 250, 250, 500,
//	500, 125, 875,
//	325, 125, 250, 250, 250, 250, 250, 500,
//	500, 125, 125, 500, 250, 250,
//	250, 250, 250, 125, 625, 250, 250,
//	250, 250, 250, 250, 1000,
//	125, 125, 125, 125, 125, 125, 125, 125, 500, 125, 125, 250,
//	1000, 250, 250, 250, 250, 
//	1000, 250, 250, 250, 250, 
//	1000, 500, 500,
//	1000, 500, 125, 125, 250,
//	1000, 250, 250, 250, 250, 
//	1000, 250, 250, 250, 250, 
//	1000, 500, 500,
//	1000, 500, 500, 
//	2000
//};

// ���ű߹��
u8 code music_score[] = 
{/* 1   2   3   4   5   6   7   8   9   10  11  12 */ 
	40, 44,
	47, 47, 44,
	42,
	47, 51, 47,
	44,
	40, 42, 44,
	47, 35,
	42, 40, 44,
	42,
	40,
	44, 47, 47, 40,
	47, 47, 47, 37,
	40, 37, 40, 47,
	44, 35,
	37, 40, 40, 40, 37,
	35, 40, 40, 37,
	40, 40, 37, 37, 44,
	42,
	44, 47, 47, 44, 44,
	42, 47, 47, 37,
	40, 37, 40, 47,
	44,
	37, 40, 40, 40, 40, 
	37, 35, 40,
	42, 42, 42, 56, 42, 40,
	40,
	49, 49, 49,
	47, 44,
	45, 47, 45,
	44,
	49, 49, 49,
	47, 44,
	45, 59, 39, 40
};
// ���׸��ӳ���Ҫ����3
u16 code music_delay[] = 
{
	250, 250,
	500, 250, 250,
	1000,
	500, 250, 250,
	1000,
	500, 250, 250,
	500, 500,
	500, 250, 250,
	1000,
	1000,
	250, 250, 375, 125,
	250, 250, 375, 125,
	250, 250, 250, 250,
	750, 250,
	250, 125, 125, 250, 250,
	250, 250, 375, 125,
	250, 125, 125, 250, 250,
	1000,
	250, 250, 250, 125, 125,
	250, 250, 375, 125,
	250, 250, 250, 250,
	1000,
	250, 250, 250, 125, 125,
	250, 250, 500,
	250, 125, 125, 125, 125, 250,
	1000,
	500, 250, 250,
	750, 250,
	500, 250, 250,
	1000,
	500, 250, 250,
	750, 250,
	500, 125, 125, 1250
};

void main()
{
	u8 i;
	
	Buzzer_Init();
	while(1)
	{	
		/* music_score�Ǽ��׶�Ӧ�����ټ����
		   music_delay���ӳٺ����� */ 
		for(i = 0; i < sizeof(music_score) / sizeof(music_score[0]); i++)
		{
			Buzzer_Play(music_score[i] + 12, music_delay[i] / 3);
		}
	}
}