// ʵ��һ���򵥵�����������
/* 7	8	9	+
   4	5	6	-
   1	2	3	*
   clr	0	=	/ */

#include <reg52.h>
#include "matrix_key_classic.h"
#include "74xx138.h"

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

// ����ܶ�ѡ�ӿ�
#define LED_SEG P0
// ��������ܵĶ�ѡ��0 ~ 9
u8 code SegSel_CC[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
// ��ʾ��8λ����
u8 DisplayCode[8]     = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F};

void Delay1ms()   			//��� 0us
{
    u8 a, b, c;
    for(c = 1; c > 0; c--)
        for(b = 2; b > 0; b--)
            for(a = 242; a > 0; a--);
}

// �������ʾ
void SegDisScan()
{
	u8 i;
	
    for(i = 0; i < 8; i++)
	{
		// λѡ�źţ�������һλ����ܵ�����ʹ��3-8������
		_74XX138_SetLow(i);
		// ��ѡ�źţ������������ʲô
		LED_SEG = DisplayCode[i];
		Delay1ms();
		LED_SEG = 0x00;		//���������
	}
}

void DisplayCode_Update(long result)
{
	u8 i, k = 0;
	
	for(i = 0; i < 8; i++) DisplayCode[i] = 0x00;
		
	// ���Ϊ0
	if(result == 0)
	{
		DisplayCode[7] = 0x3F;
	}
	// �������0
	else if(result > 0)
	{
		while(result > 0)
		{
			DisplayCode[7 - k] = SegSel_CC[result % 10];
			result /= 10;
			k++;
		}
	}
	// ���С��0
	else
	{
		// ��ʾ����ֵ
		result = -result;
		while(result > 0)
		{
			DisplayCode[7 - k] = SegSel_CC[result % 10];
			result /= 10;
			k++;
		}
		// ��ʾ����
		DisplayCode[7 - k] = 0x40;
	}
}

void MatrixKeyAction(u8 keyVal)
{
	static long result = 0;	// װ���
	static long temp   = 0;	// װ�м������
	static u8 operation; 	// ������
	
	switch(keyVal)
	{
		// ����1 ~ 9
		case 1:  case 2:  case 3:
		case 5:  case 6:  case 7:
		case 9:  case 10: case 11:
		{
			/* ���룺1	2	3
			   ���֣�7	8	9 */
			if(keyVal < 5) 		result = result * 10 + keyVal + 6;
			/* ���룺9	10	11
			   ���֣�1	2	3 */
			else if(keyVal > 7)	result = result * 10 + keyVal - 8;
			/* ���룺5	6	7
			   ���֣�4	5	6 */
			else				result = result * 10 + keyVal - 1;
			
			DisplayCode_Update(result);
		}
		break;
		// ����0
		case 14: 
		{
			result *= 10;
			DisplayCode_Update(result);
		}
		break;
		// ����
		case 13:
		{
			result = 0;
			temp   = 0;
			DisplayCode_Update(result);
		}
		break;
		// ������+-*/
		case 4: /* + */ case 8: /* - */ case 12: /* * */ case 16: /* / */
		{
			operation = keyVal;
			temp 	  = result;
			// ׼��װ��һ��������
			result    = 0;
		}
		break;
		// �Ⱥż�����ʾ���
		case 15:
		{
			switch(operation)
			{
				case 4:  temp += result; break;
				case 8:  temp -= result; break;
				case 12: temp *= result; break;
				case 16: temp /= result; break;
				default: break;
			}
			result = temp;
			DisplayCode_Update(result);
		}
		break;
		default: break;
	}
}

void main()
{
	u8 keyVal;
	
	while(1)
	{
		SegDisScan();
		keyVal = MatrixKeyScan();
		MatrixKeyAction(keyVal);
	}
}