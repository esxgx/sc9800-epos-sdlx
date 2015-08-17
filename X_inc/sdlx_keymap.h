//
// SDL & X 系统(sdl_keymap.h)
// Sochip, AWMicro 2010.5.2
//
#ifndef __SDL_KEYMAP_H
#define __SDL_KEYMAP_H

#include "SDL.h"

//
// 硬键位，即SDLX_Set/GetKeyvalue的第一个参数
// 根据不同的机型有所增减
//   0		UP
//   1		DOWN
//   2		ENTER
//   3		RIGHT
//   4		LEFT
//   5		ESCAPE
//   6		VADD (音量键)
//   7		VDEC (音量键)
//   8		未定义
//   9		PLAY
//
Uint32 SDLX_SetKeyvalue(int, int, SDLKey);		// 修改某个键的映射
SDLKey SDLX_GetKeyvalue(int, int);				// 查询某个键的映射

#endif
