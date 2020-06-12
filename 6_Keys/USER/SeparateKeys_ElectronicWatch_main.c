<<<<<<< HEAD
#include <reg52.h>
#include "74xx138.h"

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif
#ifndef u32
#define u32 unsigned long
#endif

#define SEG_SEL P0					// ��ѡ����
sbit LED = P1^0;					// LEDʹ������
// �˴������Ĵ������ڽ��������ͣ�ˣ�����û��д��ȥ��key.h����
sbit K1  = P3^0;					// ����ʱ��İ���
sbit K2  = P3^1;					// ���� + 1
sbit K3  = P3^2;					// Сʱ + 1
sbit K4  = P3^3;					// ����LED�����壩�İ���

// ��������ܶ�ѡ����0��9
u8 code segCC_SegSel[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
// �������ʾ���ݣ���ʼ��00-00-00
u8 DisplayCode[8]        = {0x3f, 0x3f, 0x40, 0x3f, 0x3f, 0x40, 0x3f, 0x3f};

u32 timestamp      = 0;				// �洢��ʾʱ����ı���
/* ԭ������ʹ��u16��������������ʱ�����������ʡ�ڴ�
   ���ǿ��ǵ�DisplayCode_Update()���޸ķ������ʲ��Ż��˴� */
u32 alarmTimestamp = 43200;			// �洢����ʱ����ı�����Ϊ��ֹһ��ʼ���ӣ�����Ϊ12-00-00
/* ����ȫ��ʼ��ֻ��дһ��Ԫ�ؼ��� */
u8  KeyCur[4]      = {1};			// װ�ص�ǰʱ�̰���״ֵ̬
u8  KeyPre[4]      = {1};			// װ��֮ǰʱ�̰���״ֵ̬
u8  KeyBuff[4]     = {0xFF};		// װ�ذ���״̬����ı���
u8  KeyEnable[4]   = {1, 0, 0, 1};	// �ĸ������Ƿ�ɰ���״̬����

// ��ʱ1ms����
void Delay1ms()
{
    u8 i;
	
	for(i = 0; i < 125; i++);
}

// �������ʾ����
void SegDisplay()
{	  
	u8 i;
	
	for(i = 0; i < 8; i++)
	{
		_74XX138_SetLow(i);				// �����λѡ
		SEG_SEL = DisplayCode[i];		// ����ܶ�ѡ
		Delay1ms();
		
		SEG_SEL = 0x00;					// ���������
	}
}

// ��ʾʱ�����
void DisplayCode_Update(u32 disTimestamp)
{
	u8 disHour   = disTimestamp / 60 / 60;		// Сʱ00 ~ 23��24 == 00��
	u8 disMinute = disTimestamp / 60 % 60;		// ����00 ~ 59��60 == 00��
	u8 disSecond = disTimestamp % 60;			// ��  00 ~ 59��60 == 00��
	
	DisplayCode[0] = segCC_SegSel[disHour   / 10];
	DisplayCode[1] = segCC_SegSel[disHour   % 10];
	DisplayCode[3] = segCC_SegSel[disMinute / 10];
	DisplayCode[4] = segCC_SegSel[disMinute % 10];
	DisplayCode[6] = segCC_SegSel[disSecond / 10];
	DisplayCode[7] = segCC_SegSel[disSecond % 10];
}

// ɨ���ĸ�����������
u8 KeyScan()
{
	u8 i, keyVal = 0;
	
	for(i = 0; i < 4; i++)				// �ĸ�������ɨ��
	{
		if(KeyCur[i] != KeyPre[i])		// ��ǰ������λֵ��֮ǰʱ�̵�λֵ�����仯
		{
			if(KeyPre[i])				// ֮ǰʱ�̵ĵ�λֵΪ��
			{
				keyVal = i + 1;
			}
			KeyPre[i] = KeyCur[i];		// ֮ǰʱ�̵ĵ�λֵ����
		}
	}
	
	return(keyVal);
}

// ������⣬4��ɨ��״̬һ��������λ
void KeyUpdate()
{
	u8 i;
	
	// ��KEYS��ֵװ�ص�KeyBuff�����һλ
	KeyBuff[0] = (KeyBuff[0] << 1) | K1;
	KeyBuff[1] = (KeyBuff[1] << 1) | K2;
	KeyBuff[2] = (KeyBuff[2] << 1) | K3;
	KeyBuff[3] = (KeyBuff[3] << 1) | K4;
	
	for(i = 0; i < 4; i++)
	{
		if((KeyBuff[i] & 0x0F) == 0x00)			// ����������쵽4��0
		{
			KeyCur[i] = 0;
		}
		else if((KeyBuff[i] & 0x0F) == 0x0F)	// ����������쵽4��1
		{
			KeyCur[i] = 1;
		}
	}
}

void KeyAction(u8 keyVal)
{
	switch(keyVal)
	{
		case 1:
			if(KeyEnable[0])	// ��������ܰ���
			{
				// �򿪻�رն�ʱ
				TR0 = !TR0;
				if(!TR0)	// ��ʱ�����ر��ˡ������Ե���ʱ���ˣ�����������������
				{
					KeyEnable[1] = 1;
					KeyEnable[2] = 1;
					KeyEnable[3] = 0;
				}
				else		// ��ʱ�������ˡ��������Ե���ʱ���ˣ���������������
				{
					KeyEnable[1] = 0;
					KeyEnable[2] = 0;
					KeyEnable[3] = 1;
				}
			}
			break;
		case 2:
			if(KeyEnable[1])	// ��������ܰ���
			{
				// �ж���ʱ�����������������
				if(KeyEnable[0])	// ʱ�����
				{
					timestamp += 60;
					if(timestamp == 86400) timestamp = 0;
				}
				else				// ��������
				{
					alarmTimestamp += 60;
					if(alarmTimestamp == 86400) alarmTimestamp = 0;
				}
			}
			break;
		case 3:
			if(KeyEnable[2])	// ��������ܰ���
			{
				// �ж���ʱ�����������������
				if(KeyEnable[0])	// ʱ�����
				{
					timestamp += 3600;
					if(timestamp >= 86400) timestamp = 0;
				}
				else				// ��������
				{
					alarmTimestamp += 3600;
					if(alarmTimestamp >= 86400) alarmTimestamp = 0;
				}
			}
			break;
		case 4:
			if(KeyEnable[3])	// ��������ܰ���
			{
				KeyEnable[0] = !KeyEnable[0];	// ��ʱ���Ƿ��������Ϊ�����Ƿ�������õı�׼
				if(!KeyEnable[0])				// ʱ�䲻�ɵ������������ÿ�ʼ
				{
					KeyEnable[1] = 1;
					KeyEnable[2] = 1;
				}
				else							// ʱ����Ե������������ý���
				{
					KeyEnable[1] = 0;
					KeyEnable[2] = 0;
				}
			}
			break;
		default: break;
	}
}

// ������ʱ�����ö�ʱ��
void Timer0Init()
{
	/* ��ʱ��0��������ʽ1���������ֹ��ֲ��ʱ��Ӱ��������ʱ��
	   ��ʽ1��16λ��1������ */
	TMOD |= 0x01;
	
	TR0 = 1;	// �򿪶�ʱ��0
	
	// ��ʱ50ms
	TH0 = 15536 / 256;
	TL0 = 15536 % 256;
	
	// ��ʱ��0�жϺ����жϿ��ش�
	ET0 = 1;
	EA  = 1;
}

// �������õĶ�ʱ��
void Timer1Init()
{
	/* ��ʱ��1��������ʽ1���������ֹ��ֲ��ʱ��Ӱ��������ʱ��
	   ��ʽ1��16λ��1������ */
	TMOD |= 0x10;
	
	TR1 = 1;	// �򿪶�ʱ��1
	
	// ��ʱ4ms
	TH1 = 61536 / 256;
	TL1 = 61536 % 256;
	
	// ��ʱ��0�жϺ����жϿ��ش�
	ET1 = 1;
	// EA  = 1;	// ���ж��Ѵ�
}

void main()
{
	u8 keyVal;
	
	Timer0Init();		// ʱ�����ö�ʱ�����ж����ȼ��Ƚϴ�
	Timer1Init();		// �������ö�ʱ�����ж����ȼ��Ƚ�С
	LED = 1;			// ��ʼ������״̬Ϊ�ر�״̬
	
	while(1)
	{
		// ����ɨ�����
		keyVal = KeyScan();
		KeyAction(keyVal);
		
		// �������������
		if(timestamp == alarmTimestamp)  LED = 0;
		
		/* ��������״̬�򿪵�ʱ���и��ص㣺
           �����������ð�ť���԰��£�����ʱ��������ť���ж�����һ�����ɣ����԰��� */
		if(KeyEnable[3] && KeyEnable[1]) DisplayCode_Update(alarmTimestamp);
		else 			  			     DisplayCode_Update(timestamp);
		SegDisplay();	// ����ܿ�ʼ��ʾ���¸��µ���ʾ����
    }
}

void Timer0_50ms() interrupt 1
{
	static u8 tCount = 0;			// ��ʾʱ��ʱ���ü���
	
	// ��ʱ��0�ߵ�λ�ĸ�ֵ
	TH0 = 15536 / 256;
	TL0 = 15536 % 256;
	
	if(++tCount == 20)				// 1s��Ҫ��¼20��50ms
	{
		// �ۼӲ��жϣ�ʱ��Ϊ24-00-00 = 86400ʱ����
		if(++timestamp >= 86400) timestamp = 0;
		tCount = 0;					// ����̬������0
	}
}

void Timer1_4ms() interrupt 3
{
	static u16 LED_tCount = 0;		// �ر�LEDʱ���ü���
	
	// ��װ�ء���4ms
	TH1 = 61536 / 256;
	TL1 = 61536 % 256;
	
	// ���ӵĹرղ����ʹ��T0��Ϊ����ʱ���ʱ��T0��ͣ��
	if(!LED)						// ������Ӵ򿪣�10s��ر�����
	{
		if(++LED_tCount == 2500)	// 10s��Ҫ��¼2500��4ms
		{
			LED = 1;
			LED_tCount = 0;			// ����̬������0
		}
	}
	
	KeyUpdate();					// ��ⰴ��״̬
=======
#include <reg52.h>
#include "74xx138.h"

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif
#ifndef u32
#define u32 unsigned long
#endif

#define SEG_SEL P0					// ��ѡ����
sbit LED = P1^0;					// LEDʹ������
// �˴������Ĵ������ڽ��������ͣ�ˣ�����û��д��ȥ��key.h����
sbit K1  = P3^0;					// ����ʱ��İ���
sbit K2  = P3^1;					// ���� + 1
sbit K3  = P3^2;					// Сʱ + 1
sbit K4  = P3^3;					// ����LED�����壩�İ���

// ��������ܶ�ѡ����0��9
u8 code segCC_SegSel[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
// �������ʾ���ݣ���ʼ��00-00-00
u8 DisplayCode[8]        = {0x3f, 0x3f, 0x40, 0x3f, 0x3f, 0x40, 0x3f, 0x3f};

u32 timestamp      = 0;				// �洢��ʾʱ����ı���
/* ԭ������ʹ��u16��������������ʱ�����������ʡ�ڴ�
   ���ǿ��ǵ�DisplayCode_Update()���޸ķ������ʲ��Ż��˴� */
u32 alarmTimestamp = 43200;			// �洢����ʱ����ı�����Ϊ��ֹһ��ʼ���ӣ�����Ϊ12-00-00
/* ����ȫ��ʼ��ֻ��дһ��Ԫ�ؼ��� */
u8  KeyCur[4]      = {1};			// װ�ص�ǰʱ�̰���״ֵ̬
u8  KeyPre[4]      = {1};			// װ��֮ǰʱ�̰���״ֵ̬
u8  KeyBuff[4]     = {0xFF};		// װ�ذ���״̬����ı���
u8  KeyEnable[4]   = {1, 0, 0, 1};	// �ĸ������Ƿ�ɰ���״̬����

// ��ʱ1ms����
void Delay1ms()
{
    u8 i;
	
	for(i = 0; i < 125; i++);
}

// �������ʾ����
void SegDisplay()
{	  
	u8 i;
	
	for(i = 0; i < 8; i++)
	{
		_74XX138_SetLow(i);				// �����λѡ
		SEG_SEL = DisplayCode[i];		// ����ܶ�ѡ
		Delay1ms();
		
		SEG_SEL = 0x00;					// ���������
	}
}

// ��ʾʱ�����
void DisplayCode_Update(u32 disTimestamp)
{
	u8 disHour   = disTimestamp / 60 / 60;		// Сʱ00 ~ 23��24 == 00��
	u8 disMinute = disTimestamp / 60 % 60;		// ����00 ~ 59��60 == 00��
	u8 disSecond = disTimestamp % 60;			// ��  00 ~ 59��60 == 00��
	
	DisplayCode[0] = segCC_SegSel[disHour   / 10];
	DisplayCode[1] = segCC_SegSel[disHour   % 10];
	DisplayCode[3] = segCC_SegSel[disMinute / 10];
	DisplayCode[4] = segCC_SegSel[disMinute % 10];
	DisplayCode[6] = segCC_SegSel[disSecond / 10];
	DisplayCode[7] = segCC_SegSel[disSecond % 10];
}

// ɨ���ĸ�����������
u8 KeyScan()
{
	u8 i, keyVal = 0;
	
	for(i = 0; i < 4; i++)				// �ĸ�������ɨ��
	{
		if(KeyCur[i] != KeyPre[i])		// ��ǰ������λֵ��֮ǰʱ�̵�λֵ�����仯
		{
			if(KeyPre[i])				// ֮ǰʱ�̵ĵ�λֵΪ��
			{
				keyVal = i + 1;
			}
			KeyPre[i] = KeyCur[i];		// ֮ǰʱ�̵ĵ�λֵ����
		}
	}
	
	return(keyVal);
}

// ������⣬4��ɨ��״̬һ��������λ
void KeyUpdate()
{
	u8 i;
	
	// ��KEYS��ֵװ�ص�KeyBuff�����һλ
	KeyBuff[0] = (KeyBuff[0] << 1) | K1;
	KeyBuff[1] = (KeyBuff[1] << 1) | K2;
	KeyBuff[2] = (KeyBuff[2] << 1) | K3;
	KeyBuff[3] = (KeyBuff[3] << 1) | K4;
	
	for(i = 0; i < 4; i++)
	{
		if((KeyBuff[i] & 0x0F) == 0x00)			// ����������쵽4��0
		{
			KeyCur[i] = 0;
		}
		else if((KeyBuff[i] & 0x0F) == 0x0F)	// ����������쵽4��1
		{
			KeyCur[i] = 1;
		}
	}
}

void KeyAction(u8 keyVal)
{
	switch(keyVal)
	{
		case 1:
			if(KeyEnable[0])	// ��������ܰ���
			{
				// �򿪻�رն�ʱ
				TR0 = !TR0;
				if(!TR0)	// ��ʱ�����ر��ˡ������Ե���ʱ���ˣ�����������������
				{
					KeyEnable[1] = 1;
					KeyEnable[2] = 1;
					KeyEnable[3] = 0;
				}
				else		// ��ʱ�������ˡ��������Ե���ʱ���ˣ���������������
				{
					KeyEnable[1] = 0;
					KeyEnable[2] = 0;
					KeyEnable[3] = 1;
				}
			}
			break;
		case 2:
			if(KeyEnable[1])	// ��������ܰ���
			{
				// �ж���ʱ�����������������
				if(KeyEnable[0])	// ʱ�����
				{
					timestamp += 60;
					if(timestamp == 86400) timestamp = 0;
				}
				else				// ��������
				{
					alarmTimestamp += 60;
					if(alarmTimestamp == 86400) alarmTimestamp = 0;
				}
			}
			break;
		case 3:
			if(KeyEnable[2])	// ��������ܰ���
			{
				// �ж���ʱ�����������������
				if(KeyEnable[0])	// ʱ�����
				{
					timestamp += 3600;
					if(timestamp >= 86400) timestamp = 0;
				}
				else				// ��������
				{
					alarmTimestamp += 3600;
					if(alarmTimestamp >= 86400) alarmTimestamp = 0;
				}
			}
			break;
		case 4:
			if(KeyEnable[3])	// ��������ܰ���
			{
				KeyEnable[0] = !KeyEnable[0];	// ��ʱ���Ƿ��������Ϊ�����Ƿ�������õı�׼
				if(!KeyEnable[0])				// ʱ�䲻�ɵ������������ÿ�ʼ
				{
					KeyEnable[1] = 1;
					KeyEnable[2] = 1;
				}
				else							// ʱ����Ե������������ý���
				{
					KeyEnable[1] = 0;
					KeyEnable[2] = 0;
				}
			}
			break;
		default: break;
	}
}

// ������ʱ�����ö�ʱ��
void Timer0Init()
{
	/* ��ʱ��0��������ʽ1���������ֹ��ֲ��ʱ��Ӱ��������ʱ��
	   ��ʽ1��16λ��1������ */
	TMOD |= 0x01;
	
	TR0 = 1;	// �򿪶�ʱ��0
	
	// ��ʱ50ms
	TH0 = 15536 / 256;
	TL0 = 15536 % 256;
	
	// ��ʱ��0�жϺ����жϿ��ش�
	ET0 = 1;
	EA  = 1;
}

// �������õĶ�ʱ��
void Timer1Init()
{
	/* ��ʱ��1��������ʽ1���������ֹ��ֲ��ʱ��Ӱ��������ʱ��
	   ��ʽ1��16λ��1������ */
	TMOD |= 0x10;
	
	TR1 = 1;	// �򿪶�ʱ��1
	
	// ��ʱ4ms
	TH1 = 61536 / 256;
	TL1 = 61536 % 256;
	
	// ��ʱ��0�жϺ����жϿ��ش�
	ET1 = 1;
	// EA  = 1;	// ���ж��Ѵ�
}

void main()
{
	u8 keyVal;
	
	Timer0Init();		// ʱ�����ö�ʱ�����ж����ȼ��Ƚϴ�
	Timer1Init();		// �������ö�ʱ�����ж����ȼ��Ƚ�С
	LED = 1;			// ��ʼ������״̬Ϊ�ر�״̬
	
	while(1)
	{
		// ����ɨ�����
		keyVal = KeyScan();
		KeyAction(keyVal);
		
		// �������������
		if(timestamp == alarmTimestamp)  LED = 0;
		
		/* ��������״̬�򿪵�ʱ���и��ص㣺
           �����������ð�ť���԰��£�����ʱ��������ť���ж�����һ�����ɣ����԰��� */
		if(KeyEnable[3] && KeyEnable[1]) DisplayCode_Update(alarmTimestamp);
		else 			  			     DisplayCode_Update(timestamp);
		SegDisplay();	// ����ܿ�ʼ��ʾ���¸��µ���ʾ����
    }
}

void Timer0_50ms() interrupt 1
{
	static u8 tCount = 0;			// ��ʾʱ��ʱ���ü���
	
	// ��ʱ��0�ߵ�λ�ĸ�ֵ
	TH0 = 15536 / 256;
	TL0 = 15536 % 256;
	
	if(++tCount == 20)				// 1s��Ҫ��¼20��50ms
	{
		// �ۼӲ��жϣ�ʱ��Ϊ24-00-00 = 86400ʱ����
		if(++timestamp >= 86400) timestamp = 0;
		tCount = 0;					// ����̬������0
	}
}

void Timer1_4ms() interrupt 3
{
	static u16 LED_tCount = 0;		// �ر�LEDʱ���ü���
	
	// ��װ�ء���4ms
	TH1 = 61536 / 256;
	TL1 = 61536 % 256;
	
	// ���ӵĹرղ����ʹ��T0��Ϊ����ʱ���ʱ��T0��ͣ��
	if(!LED)						// ������Ӵ򿪣�10s��ر�����
	{
		if(++LED_tCount == 2500)	// 10s��Ҫ��¼2500��4ms
		{
			LED = 1;
			LED_tCount = 0;			// ����̬������0
		}
	}
	
	KeyUpdate();					// ��ⰴ��״̬
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
}