//
// SDL & X ϵͳ(sdl_keymap.h)
// Sochip, AWMicro 2010.5.2
//
#ifndef __SDL_KEYMAP_H
#define __SDL_KEYMAP_H

#include "SDL.h"

//
// Ӳ��λ����SDLX_Set/GetKeyvalue�ĵ�һ������
// ���ݲ�ͬ�Ļ�����������
//   0		UP
//   1		DOWN
//   2		ENTER
//   3		RIGHT
//   4		LEFT
//   5		ESCAPE
//   6		VADD (������)
//   7		VDEC (������)
//   8		δ����
//   9		PLAY
//
Uint32 SDLX_SetKeyvalue(int, int, SDLKey);		// �޸�ĳ������ӳ��
SDLKey SDLX_GetKeyvalue(int, int);				// ��ѯĳ������ӳ��

#endif
