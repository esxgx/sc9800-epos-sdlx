// SDLX��λ�����ļ�

#define AWUCG_NUMKEYS	11
#define AWUCG_REALKEYS	10


//
// ����V8000HDV�ļ�λ�ٺܶ࣬��������һ��
//

//
//    ESC    TAB/SPACE          LEFT RIGHT ENTER
//                                                UP
//                                                DOWN
//
//
	{SDLK_LEFT, (SDLKey)0, (SDLKey)0},			/* GUI_MSG_KEY_UP */
	{SDLK_RIGHT, (SDLKey)0, (SDLKey)0},		/* GUI_MSG_KEY_DOWN */
	{SDLK_RETURN, (SDLKey)0, (SDLKey)0},		/* GUI_MSG_KEY_ENTER */
	{SDLK_RIGHT, (SDLKey)0, (SDLKey)0},		/* GUI_MSG_KEY_RIGHT */
	{SDLK_LEFT, (SDLKey)0, (SDLKey)0},			/* GUI_MSG_KEY_LEFT */
	{SDLK_TAB, SDLK_SPACE, (SDLKey)0},			/* GUI_MSG_KEY_ESCAPE */
	{SDLK_UP, (SDLKey)0, (SDLKey)0},			/* GUI_MSG_KEY_VADD */
	{SDLK_DOWN, (SDLKey)0, (SDLKey)0},			/* GUI_MSG_KEY_VDEC */
	{(SDLKey)0, (SDLKey)0, (SDLKey)0},			/* GUI_MSG_KEY_RISE(���ⰴ��, ��ʾ�ɿ�) */
	{SDLK_ESCAPE, (SDLKey)0, (SDLKey)0}		/* GUI_MSG_KEY_PLAY */
