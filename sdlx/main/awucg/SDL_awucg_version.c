#include "sdlx_sys.h"
#include "epdk.h"

typedef unsigned short	Uint16;

Uint32 SDLX_RTXVer(void)
{
	// �������°汾ʱ��Ҫ�޸�
	// �����ñ�����ԭ������Ϊ�����������̫����
	return __SDLX_VERSION;			// 100 0000 �汾
}


Uint16 SDLX_GetKernelVersion(void)
{
	return esKRNL_Version();
}
