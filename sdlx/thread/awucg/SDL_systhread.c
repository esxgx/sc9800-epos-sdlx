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


// 线程相关 esxgx awucg平台
#include <epdk.h>
#include "SDL_config.h"

#include "SDL_thread.h"
#include "../SDL_thread_c.h"

#define OS_STACK_SIZE 1024*8 	//8K     /* Stack size */
typedef struct {
	int (SDLCALL *func)(void *);
	void *data;
	SDL_Thread *info;
	SDL_sem *wait;
} thread_args;

// 线程处理过程
static void awucg_taskEntry(void *p_arg)
{
	SDL_RunThread(p_arg);
}


// 创建线程
int SDL_SYS_CreateThread(SDL_Thread *thread, void *args)
{
	thread->handle = esKRNL_TCreate(awucg_taskEntry, args, OS_STACK_SIZE, KRNL_priolevel3);
	if (!thread->handle) {
		SDL_SetError("SDL_SYS_CreateThread() failed");
		return -1;
	}
	thread->threadid = thread->handle;
	return 0;
}

void SDL_SYS_SetupThread(void)
{
}

// 得到当前的线程ID
Uint32 SDL_ThreadID(void)
{
	return esKRNL_GetTIDCur();
}

void SDL_SYS_WaitThread(SDL_Thread *thread)
{
	if(esKRNL_TDelReq(thread->handle) == OS_TASK_DEL_REQ)
    		esKRNL_TDel(thread->handle);
}

void SDL_SYS_KillThread(SDL_Thread *thread)
{ 
	if(esKRNL_TDelReq(thread->handle) == OS_TASK_DEL_REQ)
    		esKRNL_TDel(thread->handle);
}
