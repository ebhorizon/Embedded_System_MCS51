#ifndef _UDN2916_H_
#define _UDN2916_H_

#include <reg52.h>

// 定义常用类型
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned int
#endif

sbit UDN2916_PH1 = P1^0;
sbit UDN2916_PH2 = P1^1;
sbit UDN2916_I01 = P1^2;
sbit UDN2916_I02 = P1^3;
sbit UDN2916_I11 = P1^4;
sbit UDN2916_I12 = P1^5;
/* OUT1A - A-
   OUT1B - A+
   OUT2A - B-
   OUT2B - B+ */

/* 真值表：(1/2)表示第一或第二组
   PH(1/2) I0(1/2) I1(1/2) | OUT(1/2)A OUT(1/2)B
      0       0       0    |     0        MAX
      0       0       1    |     0      1/3MAX
      0       1       0    |     0      2/3MAX
      0       1       1    |     0         0
      1       0       0    |    MAX        0
      1       0       1    |  1/3MAX       0
	  1       1       0    |  2/3MAX       0
	  1       1       1    |     0         0 */

// 低位到高位分别是：PH1 -> I01 -> I11 -> PH2 -> I02 -> I12 -> X -> X
void UDN2916_Setting(u8 dat);

#endif