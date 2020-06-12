#include "74xx595.h"

// ���ܺͷ������ݣ�num�������ĸ���
void _74XX595_SendByte(u8 num, u8 dat[])
{
	u8 i;
	u8 temp = num;
	
	// �洢����λ�Ĵ����øߵ�ƽ��ʼ��
	_74XX595_RCK = 1;
	_74XX595_SCK = 1;
	
	// ��������ѭ��
	while(temp--)
	{
		for(i = 0; i < 8; i++)
		{
			// �ȷ����������λ
			_74XX595_SER = dat[num - 1 - temp] >> 7;
			// �ٽ���������
			dat[num - 1 - temp] <<= 1;
			
			// ��������λ
			_74XX595_SCK = 0;
			_nop_(); _nop_();
			_74XX595_SCK = 1;
		}
	}
	
	// �������������
	_74XX595_RCK = 0;
	_nop_(); _nop_();
	_74XX595_RCK = 1;
}