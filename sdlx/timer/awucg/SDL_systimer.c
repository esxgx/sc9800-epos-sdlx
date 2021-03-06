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

#include "epdk.h"
#include "SDL_config.h"


#include "SDL_timer.h"
#include "../SDL_timer_c.h"

void SDL_StartTicks(void)
{
}

Uint32 SDL_GetTicks (void)
{	
//	return esKRNL_Time();
//	return sys_ticks();
//	在epos上，一个Tick10ms，因此Tick转成ms = *10
//	return esKRNL_TimeGet();
//	return esKRNL_TimeGet() * 10;		// lemon 用的这个
	return esKRNL_TimeGet() * ((Uint32)1000 / OS_TICKS_PER_SEC);
}

Uint32 SDL_GetTicksF(void)
{
	return esKRNL_TimeGet() << 4;		// lemon 用的这个
}

void SDL_Delay (Uint32 ms)
{
//	esKRNL_TimeDly(ms);
//	from lemon
	Uint32  ticks;
	ticks = (ms * OS_TICKS_PER_SEC)/1000;
	if (!ticks) ticks = 1;
	esKRNL_TimeDly((Uint16)ticks);
}

#include "SDL_thread.h"

/* Data to handle a single periodic alarm */
static int timer_alive = 0;
static SDL_Thread *timer = NULL;

static int RunTimer(void *unused)
{
	while ( timer_alive ) {
		if ( SDL_timer_running ) {
			SDL_ThreadedTimerCheck();
		}
		SDL_Delay(1);
	}
	return(0);
}

/* This is only called if the event thread is not running */
int SDL_SYS_TimerInit(void)
{
	timer_alive = 1;
	timer = SDL_CreateThread(RunTimer, NULL);
	if ( timer == NULL )
		return(-1);
	return(SDL_SetTimerThreaded(1));
}

void SDL_SYS_TimerQuit(void)
{
	timer_alive = 0;
	if ( timer ) {
		SDL_WaitThread(timer, NULL);
		timer = NULL;
	}
}

int SDL_SYS_StartTimer(void)
{
	SDL_SetError("Internal logic error: threaded timer in use");
	return(-1);
}

void SDL_SYS_StopTimer(void)
{
	return;
}

