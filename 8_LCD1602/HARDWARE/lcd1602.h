<<<<<<< HEAD
#ifndef _LCD1602_H_
#define _LCD1602_H_

#include <reg52.h>

#ifndef u8
#define u8 unsigned char
#endif

#ifndef u16
#define u16 unsigned int
#endif

#define LCD1602_DATAPINS P0		// LCD1602��������
sbit LCD1602_E  = P2^7;			// LCD1602ʹ���ź�
sbit LCD1602_RW = P2^5;			// LCD1602��/дѡ��H/L��
sbit LCD1602_RS = P2^6;			// LCD1602����/����ѡ��H/L��

// LCD1602д���ݡ���8λ������
void LCD1602_WriteDat(u8 dat);
// ��ʼ�������������޸�Ϊ�Լ�ϲ����ģʽ
void LCD1602_Init();
// ����Ϊ��һ�л��ǵڶ��У�1Ϊ��һ�У�2Ϊ�ڶ���
void LCD1602_SetLine(u8 line);

=======
#ifndef _LCD1602_H_
#define _LCD1602_H_

#include <reg52.h>

#ifndef u8
#define u8 unsigned char
#endif

#ifndef u16
#define u16 unsigned int
#endif

#define LCD1602_DATAPINS P0		// LCD1602��������
sbit LCD1602_E  = P2^7;			// LCD1602ʹ���ź�
sbit LCD1602_RW = P2^5;			// LCD1602��/дѡ��H/L��
sbit LCD1602_RS = P2^6;			// LCD1602����/����ѡ��H/L��

// LCD1602д���ݡ���8λ������
void LCD1602_WriteDat(u8 dat);
// ��ʼ�������������޸�Ϊ�Լ�ϲ����ģʽ
void LCD1602_Init();
// ����Ϊ��һ�л��ǵڶ��У�1Ϊ��һ�У�2Ϊ�ڶ���
void LCD1602_SetLine(u8 line);

>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
#endif