<<<<<<< HEAD
#ifndef _8SEG_CC_74XX138_H_
#define _8SEG_CC_74XX138_H_

#include <reg52.h>
#include "74xx138.h"

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// ����ܶ�ѡ�ӿ�
#define LED_SEG P1

// ˢ����
#define REFRESH 100

/* ��������������8λ����ʾ������Ĳ�����
   1. ��Ҫ��ʾ���ַ�����ռ8λ��0~F�Լ�����ʾ����ĸȫ��д
   2. 8Ҫ��ʾС�����״̬��ת��Ϊ16���ƣ��Ӹߵ���
   P.S. Ҫ��ʾ�����ַ���Ҫ�޸������ѡ�����飬Ȼ�󲹳�����if���� */
void LED_8Seg_Display(u8 disStr[8], u8 dp);

=======
#ifndef _8SEG_CC_74XX138_H_
#define _8SEG_CC_74XX138_H_

#include <reg52.h>
#include "74xx138.h"

// ���峣������
#ifndef u8
#define u8 unsigned char
#endif
#ifndef u16
#define u16  unsigned int
#endif

// ����ܶ�ѡ�ӿ�
#define LED_SEG P1

// ˢ����
#define REFRESH 100

/* ��������������8λ����ʾ������Ĳ�����
   1. ��Ҫ��ʾ���ַ�����ռ8λ��0~F�Լ�����ʾ����ĸȫ��д
   2. 8Ҫ��ʾС�����״̬��ת��Ϊ16���ƣ��Ӹߵ���
   P.S. Ҫ��ʾ�����ַ���Ҫ�޸������ѡ�����飬Ȼ�󲹳�����if���� */
void LED_8Seg_Display(u8 disStr[8], u8 dp);

>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
#endif