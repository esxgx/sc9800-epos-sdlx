//
// SDL & X ϵͳ(io.h)
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

Uint16 SDLX_GetKernelVersion(void);		// �õ�EPOS�ں˰汾
Uint32 SDLX_RTXVer(void);				// �õ�ʵ�ʵ�SDLX�汾

#ifdef __cplusplus
};
#endif

#endif
