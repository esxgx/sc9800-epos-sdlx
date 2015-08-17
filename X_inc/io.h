//
// SDL & X 系统(io.h)
// Sochip, AWMicro 2010.5.2
//
#ifndef __IO_H
#define __IO_H

struct __FILE;
typedef struct __FILE FILE;

// X(EPOS)系统io控制
int ioctl(FILE *stream, int request, int aux, void *pBuffer);

#endif
