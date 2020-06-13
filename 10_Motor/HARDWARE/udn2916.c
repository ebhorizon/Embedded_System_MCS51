#include "udn2916.h"

// 低位到高位分别是：PH1 -> I01 -> I11 -> PH2 -> I02 -> I12 -> X -> X
void UDN2916_Setting(u8 dat)
{
	UDN2916_PH1 = dat & 0x01;
	dat >>= 1;
	UDN2916_I01 = dat & 0x01;
	dat >>= 1;
	UDN2916_I11 = dat & 0x01;
	dat >>= 1;
	UDN2916_PH2 = dat & 0x01;
	dat >>= 1;
	UDN2916_I02 = dat & 0x01;
	dat >>= 1;
	UDN2916_I12 = dat & 0x01;
}