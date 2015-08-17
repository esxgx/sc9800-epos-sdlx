
/* Include the SDL main definition header */
#include <epdk.h>
#include "SDL_main.h"

#pragma import(__use_no_semihosting_swi)

char *awargs[2];

extern void _exitcs(void);
extern void SDL_main(int, char *[]);

extern char *__sdlx_getenvr(void);
extern void SDL_Quit(void);

int __sdlx_init(void *arg)
{
	awargs[1] = (char *)arg;
	GUI_LockExtMsg();		// 锁住消息锁
	esKRNL_TimeDly(1);		// 进行调度
	GUI_UnLockExtMsg();		// 解开消息锁
//	GUI_Init();			// ucGUI初始化
	atexit(SDL_Quit);		// 勾住Quit

	awargs[0] = __sdlx_getenvr();	/* 得到工作目录 */

	SDL_main(2, awargs);		// 进入主循环
	_exitcs();			// atexit结束
	esKRNL_TimeDly(1);		// 进行调度
	return EPDK_OK;
}
