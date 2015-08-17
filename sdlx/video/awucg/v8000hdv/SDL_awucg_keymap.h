// SDLX键位配置文件

#define AWUCG_NUMKEYS	11
#define AWUCG_REALKEYS	10


//
// 由于V8000HDV的键位少很多，因此这里改一下
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
	{(SDLKey)0, (SDLKey)0, (SDLKey)0},			/* GUI_MSG_KEY_RISE(虚拟按键, 表示松开) */
	{SDLK_ESCAPE, (SDLKey)0, (SDLKey)0}		/* GUI_MSG_KEY_PLAY */
