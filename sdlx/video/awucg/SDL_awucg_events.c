// ������־:
// 2010.5.7 esxgx ������رչ��ܣ���ӦSDL_QUIT��Ϣ
//
#include "SDL_config.h"

#include "epdk.h"
#include "SDL.h"
#include "../../events/SDL_sysevents.h"
#include "../../events/SDL_events_c.h"
#include "SDL_events.h"

#include "SDL_awucg_video.h"
#include "SDL_awucg_events_c.h"


/*
   GUI_MSG_KEY_UP,
   GUI_MSG_KEY_DOWN,
   GUI_MSG_KEY_ENTER,
   GUI_MSG_KEY_RIGHT,
   GUI_MSG_KEY_LEFT,
   GUI_MSG_KEY_ESCAPE,
   GUI_MSG_KEY_VADD,
   GUI_MSG_KEY_VDEC,
   GUI_MSG_KEY_RISE,
   GUI_MSG_KEY_PLAY,
*/

//
// SDL_awucg�������Ƽ�˵��
// ����lemon_gui������callback�ش����ƣ������ζ��callback
// ���뾡��Ľ���, ������ֱ�ӵ����û�����
// ��ʹ��bitmap��ԭ���ǣ�����QUIT����ϵͳ�ķ�Ӧ̫�죬�û������޷���⵽��
// ��˲���һ��FIFO���У�callbackѹ���β, Ȼ��AWUCG_PumpEvents�Ӷ�ͷȡ��
// ���ʵ�ָ�sdlpal���ٲ��٣����鲻Ҫ����������ơ�
//

//int keypass[20];						/* ÿһ������״̬ */
SDLKey sdl_keymap[][3] ={
	// ȱʡ�ļ�λ�����ļ����û������ڳ������Զ���
	#include "SDL_awucg_keymap.h"			/* ���ļ���X_inc�� */
};

/*
GUI_MSG_KEY_UP,
   GUI_MSG_KEY_DOWN,
   GUI_MSG_KEY_ENTER,
   GUI_MSG_KEY_RIGHT,
   GUI_MSG_KEY_LEFT,
   GUI_MSG_KEY_ESCAPE,
   GUI_MSG_KEY_VADD,
   GUI_MSG_KEY_VDEC,
   GUI_MSG_KEY_RISE,
   GUI_MSG_KEY_PLAY,
*/

Uint32 SDL_lastkey = 0xff;

Uint32 SDLX_SetKeyvalue(int i, int n, SDLKey key) {
	return (sdl_keymap[i][n] = key);
}

SDLKey SDLX_GetKeyvalue(int i, int n)
{
	return sdl_keymap[i][n];
}

// ���Ҫʵ��joystick, ��ʵ���������
Uint32 SDLX_GetK(int x,int y)
{
	return 0;
}

void __keyup(Uint32 i)
{
	SDL_keysym keysym;
	// �����ɿ�����
	keysym.mod=KMOD_NONE;
	keysym.scancode = i;
	keysym.sym = sdl_keymap[i][0];
	SDL_PrivateKeyboard(SDL_RELEASED,&keysym);		/* ���� */
	if (sdl_keymap[i][1]) {
		keysym.sym = sdl_keymap[i][1];
		SDL_PrivateKeyboard(SDL_RELEASED,&keysym);	/* ����(1) */
	}
	if (sdl_keymap[i][2]) {
		keysym.sym = sdl_keymap[i][2];
		SDL_PrivateKeyboard(SDL_RELEASED,&keysym);	/* ����(2) */
	}
}

void __keydown(Uint32 i)
{
	SDL_keysym keysym;
	// ���ڻ����İ�������, ��SDL�ṩ�İ����ܶ�, ���С����һ�����������൱�����3��SDL��
	keysym.mod=KMOD_NONE;
	keysym.scancode = i;
	keysym.sym = sdl_keymap[i][0];
	SDL_PrivateKeyboard(SDL_PRESSED,&keysym);		/* ���� */
	if (sdl_keymap[i][1]) {
		keysym.sym = sdl_keymap[i][1];
		SDL_PrivateKeyboard(SDL_PRESSED,&keysym);	/* ����(1) */
	}
	if (sdl_keymap[i][2]) {
		keysym.sym = sdl_keymap[i][2];
		SDL_PrivateKeyboard(SDL_PRESSED,&keysym);	/* ����(2) */
	}
}

Uint32 Kfifo[AWUCG_NUMKEYS<<4], __Kf, __Kl;

extern void __SDLX_LCD_Changed(Uint32 b);

void SDL_AWUCG_cbCallBack(__gui_msg_t * msg)
{
	//__gui_win_t *p_win = (__gui_win_t *)(msg->h_deswin);
	Uint32 keyint;
	switch(msg->id) {
		case GUI_MSG_INIT_WIN:
			break;
			
		case GUI_MSG_DELETE_WIN:		
			break;
            
		case GUI_MSG_NOTIFY_CHILD_DELETED:
			break;

		case GUI_MSG_ONPAIN:
			break;

		case GUI_MSG_LYR_ON:
			__SDLX_LCD_Changed(1);
			break;

		case GUI_MSG_LYR_OFF:
			__SDLX_LCD_Changed(0);
			break;

		case GUI_MSG_KEY:
			keyint = (((__gui_keyinfo_t*)(msg->p_arg))->key);

			if (keyint == '9') {		// 2010.5.7 esxgx ������رհ���
				Kfifo[__Kf] = AWUCG_REALKEYS;
				__Kf = (__Kf + 1) % (AWUCG_NUMKEYS<<4);
//			} else if (keyint != GUI_MSG_KEY_RISE && keyint != 0xffffffff) {
			} else if (keyint != GUI_MSG_KEY_RISE && keyint < AWUCG_REALKEYS) {
				Kfifo[__Kf] = keyint;
				__Kf = (__Kf + 1) % (AWUCG_NUMKEYS<<4);
				SDL_lastkey = keyint;
			} else {
				if (SDL_lastkey != 0xff) {
					Kfifo[__Kf] = SDL_lastkey + AWUCG_NUMKEYS;
					__Kf = (__Kf + 1) % (AWUCG_NUMKEYS<<4);
					SDL_lastkey = 0xff;
				}
			}
			break;
		case GUI_MSG_SET_FOCUS:
			SDL_PrivateAppActive(1, SDL_APPACTIVE|SDL_APPINPUTFOCUS);
			break;
		case GUI_MSG_SET_UNFOCUS:
			SDL_PrivateAppActive(0, SDL_APPACTIVE|SDL_APPINPUTFOCUS);
			break;
		default:
//			GUI_WinDefaultProc(msg); 
			break;
	}
	
}

void AWUCG_PumpEvents(_THIS)
{
	while( __Kf != __Kl ) {
		if (Kfifo[__Kl] == AWUCG_REALKEYS) {
			// ����رհ������º���SDL_QUIT��Ϣ
			// ��Ȼ�û��������ѡ����������Ϣ,
			// �Ͼ���ֻ��һ���������� 
			SDL_PrivateQuit();
		} else 
		if (Kfifo[__Kl] >= AWUCG_NUMKEYS) __keyup(Kfifo[__Kl] - AWUCG_NUMKEYS);
		else __keydown(Kfifo[__Kl]);
		__Kl = (__Kl + 1) % (AWUCG_NUMKEYS<<4);
	}
}


void AWUCG_InitOSKeymap(_THIS)
{
}

/* end of SDL_nullevents.c ... */

