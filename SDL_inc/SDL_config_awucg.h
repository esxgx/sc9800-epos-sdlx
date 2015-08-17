/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2009 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/

#ifndef _SDL_config_awucg_h
#define _SDL_config_awucg_h

/* This is a set of defines to configure the SDL features */



/* General platform specific identifiers */
#include "SDL_platform.h"

#include <stdarg.h>

/* This is the minimal configuration that can be used to build SDL */

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef unsigned int size_t;
typedef unsigned long uintptr_t;

#define __NDS__
#define __AWUCG__

#define __inline__
#define inline


#define HAVE_MALLOC		1
#define HAVE_FREE		1
#define HAVE_REALLOC		1
#define HAVE_CALLOC		1
//#define HAVE_STRDUP	1
#define HAVE_STDIO		1


#define HAVE_VSNPRINTF	1
#define HAVE_STRCMP		1
#define HAVE_ATOF		1
#define HAVE_ITOA		1

//#include "epdk.h"


#include "_stdio.h"
#include "_stdlib.h"


/* Enable the stub cdrom driver (src/cdrom/dummy/\*.c) */
#define SDL_CDROM_DISABLED	1

/* Enable the stub joystick driver (src/joystick/awucg/\*.c) */
#define SDL_JOYSTICK_DISABLED	0

/* Enable the stub shared object loader (src/loadso/dummy/\*.c) */
#define SDL_LOADSO_DISABLED	1

/* Enable the stub thread support  */
#define SDL_THREADS_DISABLED	0

/* Enable the stub timer support (src/timer/dummy/\*.c) */
#define SDL_TIMER_DISABLED		1
//#define SDL_TIMER_AWUCG	1

/* Enable the awucg video driver (src/video/awucg/\*.c) */
#define SDL_VIDEO_DRIVER_AWUCG	1
/* Enable the awucg audio driver (src/video/awucg/\*.c) */
//#define SDL_AUDIO_DRIVER_AWUCG	1
#define SDL_AUDIO_DRIVER_DUMMY	1


#endif /* _SDL_config_nds_h */
