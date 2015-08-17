// 更新日志:
// 2010.5.7 esxgx 增加软关闭功能，对应SDL_QUIT消息
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
// SDL_awucg按键机制简单说明
// 由于lemon_gui采用了callback回传机制，这就意味着callback
// 必须尽快的结束, 而不能直接调回用户程序。
// 不使用bitmap的原因是，对于QUIT按键系统的反应太快，用户程序无法检测到。
// 因此采用一个FIFO队列，callback压入队尾, 然后AWUCG_PumpEvents从队头取。
// 这个实现给sdlpal提速不少，建议不要更改这个机制。
//

//int keypass[20];						/* 每一个键的状态 */
SDLKey sdl_keymap[][3] ={
	// 缺省的键位配置文件，用户可以在程序中自定义
	#include "SDL_awucg_keymap.h"			/* 此文件在X_inc中 */
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

// 如果要实现joystick, 请实现这个函数
Uint32 SDLX_GetK(int x,int y)
{
	return 0;
}

void __keyup(Uint32 i)
{
	SDL_keysym keysym;
	// 机器松开按键
	keysym.mod=KMOD_NONE;
	keysym.scancode = i;
	keysym.sym = sdl_keymap[i][0];
	SDL_PrivateKeyboard(SDL_RELEASED,&keysym);		/* 按键 */
	if (sdl_keymap[i][1]) {
		keysym.sym = sdl_keymap[i][1];
		SDL_PrivateKeyboard(SDL_RELEASED,&keysym);	/* 按键(1) */
	}
	if (sdl_keymap[i][2]) {
		keysym.sym = sdl_keymap[i][2];
		SDL_PrivateKeyboard(SDL_RELEASED,&keysym);	/* 按键(2) */
	}
}

void __keydown(Uint32 i)
{
	SDL_keysym keysym;
	// 由于机器的按键很少, 而SDL提供的按键很多, 因此小机的一个按键可以相当于最多3个SDL键
	keysym.mod=KMOD_NONE;
	keysym.scancode = i;
	keysym.sym = sdl_keymap[i][0];
	SDL_PrivateKeyboard(SDL_PRESSED,&keysym);		/* 按键 */
	if (sdl_keymap[i][1]) {
		keysym.sym = sdl_keymap[i][1];
		SDL_PrivateKeyboard(SDL_PRESSED,&keysym);	/* 按键(1) */
	}
	if (sdl_keymap[i][2]) {
		keysym.sym = sdl_keymap[i][2];
		SDL_PrivateKeyboard(SDL_PRESSED,&keysym);	/* 按键(2) */
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

			if (keyint == '9') {		// 2010.5.7 esxgx 加入软关闭按键
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
			// 当软关闭按键按下后发送SDL_QUIT消息
			// 当然用户程序可以选择不理睬这个消息,
			// 毕竟这只是一个软按键而已 
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

