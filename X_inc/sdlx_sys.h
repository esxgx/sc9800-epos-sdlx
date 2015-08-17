//
// SDL & X 系统(io.h)
// Sochip, AWMicro 2010.5.2
//
#ifndef __SDLX_SYS_H
#define __SDLX_SYS_H

typedef unsigned int		Uint32;
typedef unsigned short	Uint16;

#define __SDLX_VERSION	0x01000000

#ifdef __cplusplus
extern "C" {
#endif

Uint16 SDLX_GetKernelVersion(void);		// 得到EPOS内核版本
Uint32 SDLX_RTXVer(void);				// 得到实际的SDLX版本

#ifdef __cplusplus
};
#endif

#endif
