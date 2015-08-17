//
// SDL & X ϵͳ(io.h)
// Sochip, AWMicro 2010.5.2
//
#ifndef __SDL_VIDEO_H
#define __SDL_VIDEO_H

typedef unsigned long	Uint32;

//
// ����X��Ƶ����
//

Uint32 SDLX_GetScreenWidth(void);				// �õ���Ļ��
Uint32 SDLX_GetScreenHeight(void);				// �õ���Ļ��

//
// bool ����
// ��������int����, <0��ʾʧ��
// ����Uint32����, 0 - ʧ�ܣ� 1 - �ɹ�
//
int SDLX_GetLCDBright(void);			// �õ�LCD������
int SDLX_SetLCDBright(int);				// �ı�LCD������(15������)
Uint32 SDLX_GetDefLCDBright(void);			// �õ�ϵͳĬ������(���ʼ��SDL��ʹ��)

int SDLX_GetLCDContrast(void);			// �õ�LCD�Աȶ�
int SDLX_SetLCDContrast(int);			// ����LCD�Աȶ�

Uint32 SDLX_LCDPowerOn(void);			// ��ĻPOWER ON
Uint32 SDLX_LCDPowerOff(void);			// ��ĻPOWER OFF

//Uint32 SDLX_TVOutOn(void);			// TV��� ON
//Uint32 SDLX_TVOutOff(void);			// TV��� OFF

// �Զ���������
// epos��desktop����ʱ�Զ����������º������Խ�ֹ/����
// �Զ�����
Uint32 SDLX_SwitchLCDAutooff();			// �л��Զ�����

#endif		//  !__SDL_VIDEO_H
