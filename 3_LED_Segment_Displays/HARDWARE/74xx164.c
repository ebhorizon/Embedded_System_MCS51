<<<<<<< HEAD
#include "74xx164.h"

void _74XX164_Delay(u8 t)
{
	while(t--);
}

// 74XX164����һ���ֽ�
void _74XX164_SendByte(u8 dat)
{
    u8 i;
	
    for(i = 0; i < 8; i++)
    {
		_74XX164_Data = dat >> 7;	// ��λ����λ����
		dat 		<<= 1;			// ��������׼���´η���
        _74XX164_CLK  = 0;			// �ȴ�����
		// _nop_();
		// _nop_();
        _74XX164_CLK  = 1;			// �����ط�������
    }
}

// 74XX164����
void _74XX164_Enable()
{
	_74XX164_CLR = 1;
}

// 74XX164�ر�
void _74XX164_Disable()
{
	_74XX164_CLR = 0;
	_74XX164_Delay(500);
=======
#include "74xx164.h"

void _74XX164_Delay(u8 t)
{
	while(t--);
}

// 74XX164����һ���ֽ�
void _74XX164_SendByte(u8 dat)
{
    u8 i;
	
    for(i = 0; i < 8; i++)
    {
		_74XX164_Data = dat >> 7;	// ��λ����λ����
		dat 		<<= 1;			// ��������׼���´η���
        _74XX164_CLK  = 0;			// �ȴ�����
		// _nop_();
		// _nop_();
        _74XX164_CLK  = 1;			// �����ط�������
    }
}

// 74XX164����
void _74XX164_Enable()
{
	_74XX164_CLR = 1;
}

// 74XX164�ر�
void _74XX164_Disable()
{
	_74XX164_CLR = 0;
	_74XX164_Delay(500);
>>>>>>> 64c192fc79434a4be878e64dcbbf3fda3a7e4b5e
}