#include "epdk.h"

typedef enum desk_msg_t
{
	DESK_MSG_POWER_OFF = 0x200,
	DESK_MSG_LOW_POWER,
	DESK_MSG_PLUG_IN,
	DESK_MSG_PLUG_OUT,
	DESK_MSG_APP_EXIT,
	DESK_MSG_UPDATE_ORCHID,

	DESK_MSG_AUTO_OFF,
	DESK_MSG_AUTO_SLEEP,

	DESK_MSG_SCREEN_OP_GATE_ON,
	DESK_MSG_SCREEN_OPEN,
	DESK_MSG_SCREEN_CLOSE,
	DESK_MSG_SCREEN_OP_GATE_OFF,

	DESK_MSG_KEYTONE_GATE_ON,
	DESK_MSG_KEYTONE_GATE_OFF,

	DESK_MSG_VOICE_ADJUST_GATE_ON,
	DESK_MSG_VOICE_ADJUST_GATE_OFF,

	DESK_MSG_SLEEP_GATE_ON,
	DESK_MSG_SLEEP_GATE_OFF,

	DESK_MSG_TVDAC_PLUGIN,
	DESK_MSG_TVDAC_PLUGOUT,

	DESK_MSG_INSTALL_USBH,
	DESK_MSG_UNSTALL_USBH,

	DESK_MSG_HDMI_PLUGIN,
	DESK_MSG_HDMI_PLUGOUT,
	///////////James++ Ramos T6
	DESK_MSG_AVOUT_FAST,
	DESK_MSG_LOW_BATTERY,
	DESK_MSG_HIGH_BATTERY,
	DESK_MSG_DC_PLUGIN,
	DESK_MSG_CHG_KEYINT,
	DESK_MSG_DC_PLUGOUT,
	//////////////---------------
	DESK_MSG_KEY_LOCKED,
	DESK_MSG_KEY_UNLOCKED,
	
	DESK_MSG_LOCK_OP_GATE_ON,
	DESK_MSG_LOCK_OP_GATE_OFF,

	DESK_MSG_DISPLAY_BAR_ON,
	DESK_MSG_DISPLAY_BAR_OFF,

	DESK_MSG_CHARGE_ON,//开始充电命令；
	DESK_MSG_EXIT_TV_MODE,  //在主界面退出电视模式

	DESK_MSG_QUICK_QUIT,
	DESK_MSG_CUCKOO_PLAY,/*音乐界面下播放*/
	DESK_MSG_CUCKOO_BKG, /*音乐背景播放*/
	DESK_MSG_CLOSE_KEYTONE,
	DESK_MSG_OPEN_KEYTONE,
	DESK_MSG_PAUSE_KEYTONE,
	DESK_MSG_CONTINUE_KEYTONE,
	DESK_MSG_NULL,
}__desk_msg_t;

typedef unsigned int Uint32;

// 禁用自动关屏(这个取决于desktop)
Uint32 SDLX_DisableLCDAutooff()
{
	__gui_msg_t msg;
	msg.id       = DESK_MSG_SCREEN_OP_GATE_OFF;		// 关闭自动关屏
	msg.h_srcwin = NULL;
	msg.h_deswin = GUI_WinGetBackWin();
	GUI_SendMessage(&msg);
	return 1;
}

// 启用自动关屏(这个取决于desktop)
Uint32 SDLX_EnableLCDAutooff()
{
	__gui_msg_t msg;

	msg.id	= DESK_MSG_SCREEN_OP_GATE_ON;
	msg.h_srcwin = NULL;
	msg.h_deswin = GUI_WinGetBackWin();
	msg.p_arg    = NULL;
	GUI_SendMessage(&msg);
	return 1;
}

static int autooff = 1;

// 切换自动关屏(这个最保险)
Uint32 SDLX_SwitchLCDAutooff()
{
	autooff = 1 - autooff;

	if (autooff) return SDLX_EnableLCDAutooff();
	return SDLX_DisableLCDAutooff();
}
