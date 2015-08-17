#include "sdlx_sys.h"
#include "epdk.h"

typedef unsigned short	Uint16;

Uint32 SDLX_RTXVer(void)
{
	// 当发布新版本时需要修改
	// 不采用变量的原因是因为变量符号输出太死板
	return __SDLX_VERSION;			// 100 0000 版本
}


Uint16 SDLX_GetKernelVersion(void)
{
	return esKRNL_Version();
}
