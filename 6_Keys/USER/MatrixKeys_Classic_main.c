// 实现一个简单的整数计算器
/* 7	8	9	+
   4	5	6	-
   1	2	3	*
   clr	0	=	/ */

#include <reg52.h>
#include "matrix_key_classic.h"
#include "74xx138.h"

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

// 数码管段选接口
#define LED_SEG P0
// 共阴数码管的段选，0 ~ 9
u8 code SegSel_CC[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
// 显示的8位数据
u8 DisplayCode[8]     = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F};

void Delay1ms()   			//误差 0us
{
    u8 a, b, c;
    for(c = 1; c > 0; c--)
        for(b = 2; b > 0; b--)
            for(a = 242; a > 0; a--);
}

// 数码管显示
void SegDisScan()
{
	u8 i;
	
    for(i = 0; i < 8; i++)
	{
		// 位选信号，控制哪一位数码管点亮，使用3-8译码器
		_74XX138_SetLow(i);
		// 段选信号，控制数码管亮什么
		LED_SEG = DisplayCode[i];
		Delay1ms();
		LED_SEG = 0x00;		//数码管消隐
	}
}

void DisplayCode_Update(long result)
{
	u8 i, k = 0;
	
	for(i = 0; i < 8; i++) DisplayCode[i] = 0x00;
		
	// 结果为0
	if(result == 0)
	{
		DisplayCode[7] = 0x3F;
	}
	// 结果大于0
	else if(result > 0)
	{
		while(result > 0)
		{
			DisplayCode[7 - k] = SegSel_CC[result % 10];
			result /= 10;
			k++;
		}
	}
	// 结果小于0
	else
	{
		// 显示绝对值
		result = -result;
		while(result > 0)
		{
			DisplayCode[7 - k] = SegSel_CC[result % 10];
			result /= 10;
			k++;
		}
		// 显示负号
		DisplayCode[7 - k] = 0x40;
	}
}

void MatrixKeyAction(u8 keyVal)
{
	static long result = 0;	// 装结果
	static long temp   = 0;	// 装中间操作数
	static u8 operation; 	// 操作符
	
	switch(keyVal)
	{
		// 数字1 ~ 9
		case 1:  case 2:  case 3:
		case 5:  case 6:  case 7:
		case 9:  case 10: case 11:
		{
			/* 键码：1	2	3
			   数字：7	8	9 */
			if(keyVal < 5) 		result = result * 10 + keyVal + 6;
			/* 键码：9	10	11
			   数字：1	2	3 */
			else if(keyVal > 7)	result = result * 10 + keyVal - 8;
			/* 键码：5	6	7
			   数字：4	5	6 */
			else				result = result * 10 + keyVal - 1;
			
			DisplayCode_Update(result);
		}
		break;
		// 数字0
		case 14: 
		{
			result *= 10;
			DisplayCode_Update(result);
		}
		break;
		// 清零
		case 13:
		{
			result = 0;
			temp   = 0;
			DisplayCode_Update(result);
		}
		break;
		// 操作符+-*/
		case 4: /* + */ case 8: /* - */ case 12: /* * */ case 16: /* / */
		{
			operation = keyVal;
			temp 	  = result;
			// 准备装下一个操作数
			result    = 0;
		}
		break;
		// 等号计算显示结果
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