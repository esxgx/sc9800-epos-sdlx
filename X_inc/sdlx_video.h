//
// SDL & X 系统(io.h)
// Sochip, AWMicro 2010.5.2
//
#ifndef __SDL_VIDEO_H
#define __SDL_VIDEO_H

typedef unsigned long	Uint32;

//
// 补充X视频函数
//

Uint32 SDLX_GetScreenWidth(void);				// 得到屏幕宽
Uint32 SDLX_GetScreenHeight(void);				// 得到屏幕高

//
// bool 声明
// 对于所有int返回, <0表示失败
// 所有Uint32返回, 0 - 失败， 1 - 成功
//
int SDLX_GetLCDBright(void);			// 得到LCD屏亮度
int SDLX_SetLCDBright(int);				// 改变LCD屏亮度(15级亮度)
Uint32 SDLX_GetDefLCDBright(void);			// 得到系统默认亮度(需初始化SDL后使用)

int SDLX_GetLCDContrast(void);			// 得到LCD对比度
int SDLX_SetLCDContrast(int);			// 设置LCD对比度

Uint32 SDLX_LCDPowerOn(void);			// 屏幕POWER ON
Uint32 SDLX_LCDPowerOff(void);			// 屏幕POWER OFF

//Uint32 SDLX_TVOutOn(void);			// TV输出 ON
//Uint32 SDLX_TVOutOff(void);			// TV输出 OFF

// 自动关屏控制
// epos的desktop负责定时自动关屏，以下函数可以禁止/启用
// 自动关屏
Uint32 SDLX_SwitchLCDAutooff();			// 切换自动关屏

#endif		//  !__SDL_VIDEO_H
