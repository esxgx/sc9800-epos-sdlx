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

// 互斥锁相关 esxgx awucg平台
#include "SDL_config.h"

/* An implementation of mutexes using semaphores */

#include "SDL_thread.h"
#include "SDL_systhread_c.h"


struct SDL_mutex {
	volatile Uint8 state;
};

/* Create a mutex */
SDL_mutex *SDL_CreateMutex(void)
{
	SDL_mutex *mutex;

	mutex = (SDL_mutex *)SDL_malloc(sizeof(*mutex));
	if (mutex != NULL) mutex->state=0;
	else SDL_OutOfMemory();

	return mutex;
}

/* Free the mutex */
void SDL_DestroyMutex(SDL_mutex *mutex)
{
	if ( mutex )
		SDL_free(mutex);
}

/* Lock the semaphore */
int SDL_mutexP(SDL_mutex *mutex)
{
	while ((volatile Uint8)mutex->state)
		SDL_Delay(1);
	mutex->state=1;
	return 0;
}

/* Unlock the mutex */
int SDL_mutexV(SDL_mutex *mutex)
{
	mutex->state=0;
	SDL_Delay(20);
	return 0;
}
