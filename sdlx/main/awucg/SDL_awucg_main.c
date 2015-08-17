
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
	GUI_LockExtMsg();		// ��ס��Ϣ��
	esKRNL_TimeDly(1);		// ���е���
	GUI_UnLockExtMsg();		// �⿪��Ϣ��
//	GUI_Init();			// ucGUI��ʼ��
	atexit(SDL_Quit);		// ��סQuit

	awargs[0] = __sdlx_getenvr();	/* �õ�����Ŀ¼ */

	SDL_main(2, awargs);		// ������ѭ��
	_exitcs();			// atexit����
	esKRNL_TimeDly(1);		// ���е���
	return EPDK_OK;
}
