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
#include "SDL_config.h"

#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_joystick.h"
#include "../SDL_sysjoystick.h"
#include "../SDL_joystick_c.h"

/* Function to scan the system for joysticks.
 * This function should set SDL_numjoysticks to the number of available
 * joysticks.  Joystick 0 should be the system default joystick.
 * It should return 0, or -1 on an unrecoverable fatal error.
 */
int SDL_SYS_JoystickInit(void)
{
	SDL_numjoysticks = 1;			// 初始化joysticks
    //keysInit();
	return(1);
}

/* Function to get the device-dependent name of a joystick */
const char *SDL_SYS_JoystickName(int index)
{
	if(!index)
		return "AllWinner(Sochip) builtin joypad";
	SDL_SetError("No joystick available with that index");
	return (NULL);
}

/* Function to open a joystick for use.
   The joystick to open is specified by the index field of the joystick.
   This should fill the nbuttons and naxes fields of the joystick structure.
   It returns 0, or -1 if there is an error.
 */
int SDL_SYS_JoystickOpen(SDL_Joystick *joystick)
{
	joystick->nbuttons=6;		// 六个按钮
	joystick->nhats=0;
	joystick->nballs=0;
	joystick->naxes=2;			// 四个方向键
	return 0;
}


/* Function to update the state of a joystick - called as a device poll.
 * This function shouldn't update the joystick structure directly,
 * but instead should call SDL_PrivateJoystick*() to deliver events
 * and update joystick device state.
 */


// 链接Video键盘驱动
Uint8 SDLX_GetK(int x, int y);

int keys[10][2] = {
	{-10, 1},				// GUI_MSG_KEY_UP
	{10, 1},				// GUI_MSG_KEY_DOWN
	{0, 0},				// GUI_MSG_KEY_ENTER
	{10, 0},				// GUI_MSG_KEY_RIGHT
	{-10, 0},				// GUI_MSG_KEY_LEFT
	{0, 1},				// GUI_MSG_KEY_ESCAPE
	{0, 2},				// GUI_MSG_KEY_VADD
	{0, 3},				// GUI_MSG_KEY_VDEC
	{0, 4},				// GUI_MSG_KEY_RISE(虚拟按键, 表示松开)
	{0, 5}					// GUI_MSG_KEY_PLAY
};


void SDL_SYS_JoystickUpdate(SDL_Joystick *joystick)
{
	Uint32 i;
	for(i=0; i<10; ++i) {
		if (SDLX_GetK(0,i) ^ SDLX_GetK(1,i)) {
			if (SDLX_GetK(0,i)) {			// 按下
				if (!keys[i][0]) SDL_PrivateJoystickButton(joystick,keys[i][1],SDL_PRESSED);
				else  SDL_PrivateJoystickAxis(joystick,keys[i][1],keys[i][0]);
			} else {
				if (!keys[i][0]) SDL_PrivateJoystickButton(joystick,keys[i][1],SDL_RELEASED);
				else  SDL_PrivateJoystickAxis(joystick,keys[i][1],keys[i][0]);
			}
		}
	}
}

/* Function to close a joystick after use */
void SDL_SYS_JoystickClose(SDL_Joystick *joystick)
{
}

/* Function to perform any system-specific joystick related cleanup */
void SDL_SYS_JoystickQuit(void)
{
}

