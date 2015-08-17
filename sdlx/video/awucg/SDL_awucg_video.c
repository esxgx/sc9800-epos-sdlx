//
// SDLX 0.01
// esxgx 2010.4.29
//

//
// ������־:
// 5.7 esxgx ���²��ִ��룬Ϊ���HWSURFACE��׼��
//

// ����EPOS�ܲ���׼��ͷ�ļ���λ��Ӱ��ܴ�= =~
#include "epdk.h"
#include "SDL_config.h"

#include "SDL_video.h"
#include "SDL_mouse.h"
#include "../SDL_sysvideo.h"
#include "../SDL_pixels_c.h"
#include "../../events/SDL_events_c.h"

#include "SDL_awucg_video.h"
#include "SDL_awucg_events_c.h"
#include "SDL_awucg_mouse_c.h"

#define AWUCGVID_DRIVER_NAME "awucg"

/* Initialization/Query functions */
static int AWUCG_VideoInit(_THIS, SDL_PixelFormat *vformat);
static SDL_Rect **AWUCG_ListModes(_THIS, SDL_PixelFormat *format, Uint32 flags);
static SDL_Surface *AWUCG_SetVideoMode(_THIS, SDL_Surface *current, int width, int height, int bpp, Uint32 flags);
static int AWUCG_SetColors(_THIS, int firstcolor, int ncolors, SDL_Color *colors);
static void AWUCG_VideoQuit(_THIS);

/* Hardware surface functions */
static int AWUCG_AllocHWSurface(_THIS, SDL_Surface *surface);
static int AWUCG_LockHWSurface(_THIS, SDL_Surface *surface);
static void AWUCG_UnlockHWSurface(_THIS, SDL_Surface *surface);
static void AWUCG_FreeHWSurface(_THIS, SDL_Surface *surface);

int LCD_WIDTH, LCD_HEIGHT;

/* etc. */
static void AWUCG_UpdateRects(_THIS, int numrects, SDL_Rect *rects);

/* AWUCG driver bootstrap functions */

static int AWUCG_Available(void)
{
	return(1);
}

static void AWUCG_DeleteDevice(SDL_VideoDevice *device)
{
	if (device->hidden != NULL) SDL_free(device->hidden);
	SDL_free(device);
}

static SDL_VideoDevice *AWUCG_CreateDevice(int devindex)
{ 
	SDL_VideoDevice *device;
	/* Initialize all variables that we clean on shutdown */
	device = (SDL_VideoDevice *)SDL_malloc(sizeof(SDL_VideoDevice));
	if (device != NULL) SDL_memset(device, 0, (sizeof *device));
	else {
		SDL_OutOfMemory();
		return(0);
	}

	/* Set the function pointers */
	device->VideoInit = AWUCG_VideoInit;
	device->ListModes = AWUCG_ListModes;
	device->SetVideoMode = AWUCG_SetVideoMode;
	device->CreateYUVOverlay = NULL;
	device->SetColors = AWUCG_SetColors;
	device->UpdateRects = AWUCG_UpdateRects;	// ע�⣬����¼���������
							// �������ַ���NULLָ�����.
	device->VideoQuit = AWUCG_VideoQuit;
	device->AllocHWSurface = AWUCG_AllocHWSurface;
	device->CheckHWBlit = NULL;
	device->FillHWRect = NULL;
	device->SetHWColorKey = NULL;
	device->SetHWAlpha = NULL;
	device->LockHWSurface = AWUCG_LockHWSurface;
	device->UnlockHWSurface = AWUCG_UnlockHWSurface;
	device->FlipHWSurface = NULL;
	device->FreeHWSurface = AWUCG_FreeHWSurface;
	device->SetCaption = NULL;
	device->SetIcon = NULL;
	device->IconifyWindow = NULL;
	device->GrabInput = NULL;
	device->GetWMInfo = NULL;
	device->InitOSKeymap = AWUCG_InitOSKeymap;
	device->PumpEvents = AWUCG_PumpEvents;

	device->free = AWUCG_DeleteDevice;

	return device;
}

VideoBootStrap AWUCG_bootstrap = {
	"AWUCG", "SDL awucg video driver",
	AWUCG_Available, AWUCG_CreateDevice
};

int SLCD_BRIGHT;			// ϵͳ���������


extern int SDLX_GetLCDBright(void);
extern int SDLX_SetLCDBright(int);

int AWUCG_VideoInit(_THIS, SDL_PixelFormat *vformat)
{
	ES_FILE *p_disp;
	__color_t  color;

	vformat->BitsPerPixel = 24;	// mode 3
	vformat->BytesPerPixel = 3;
	vformat->Rmask = 0x00ff0000;
	vformat->Gmask = 0x0000ff00;
	vformat->Bmask = 0x000000ff;

	GUI_LockExtMsg();
	// �õ���ߵ�����
	p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
	if(!p_disp) {
		__wrn("open display device fail!\n");
//		return EPDK_FAIL;
		return -1;
	}
	LCD_HEIGHT = eLIBs_fioctrl(p_disp,DISP_CMD_SCN_GET_HEIGHT,0,0);
	LCD_WIDTH = eLIBs_fioctrl(p_disp,DISP_CMD_SCN_GET_WIDTH,0,0);
	GUI_LyrSetSta(GUI_LyrGetBackLyr(), GUI_LYR_STA_SUSPEND);  	// �رձ���ͼ��
//	GUI_LyrAlphaOff(GUI_LyrGetBackLyr());
	// ���ñ�����ɫ(��ɫ, ��͸��)
	color.alpha = 0xFF;                 // don't care
	color.red   = 0;
	color.green = 0;
	color.blue  = 0;
	eLIBs_fioctrl( p_disp, DISP_CMD_SET_BKCOLOR, 0, &color);
	eLIBs_fclose(p_disp);
	
	SLCD_BRIGHT = SDLX_GetLCDBright();
//	SDLX_SetLCDBright((Uint32)DISP_LCD_BRIGHT_LEVEL15);		// �������������

	GUI_UnLockExtMsg();

	return(0); 
}

// �г�ģʽ�б�
SDL_Rect **AWUCG_ListModes(_THIS, SDL_PixelFormat *format, Uint32 flags)
{
	// Ŀǰֻ��һ��ģʽ
	static SDL_Rect r;
	static SDL_Rect *rs[2] = { &r, NULL };
	r.w = LCD_WIDTH;
	r.h = LCD_HEIGHT;
   	return rs;
}

#include "epdk.h"

extern void SDL_AWUCG_cbCallBack(__gui_msg_t * msg);

__pixel_rgbfmt_t pixe[] = {
	PIXEL_MONO_1BPP,		/* only used in normal framebuffer                              */
	PIXEL_MONO_2BPP,
	PIXEL_MONO_4BPP,
	PIXEL_MONO_8BPP,
	PIXEL_COLOR_RGB565,		/* 16bpp */
	PIXEL_COLOR_RGB0888,		/* 24bpp(used in normal framebuffer and scaler framebuffer) */
	PIXEL_COLOR_ARGB8888		/* 32bpp */
};

/* frame buffer para */
static FB  fb_sdl = 
{
    {0, 0},                                   		/* size      */
    {0, 0, 0},						/* buffer    */
    {FB_TYPE_RGB, {PIXEL_COLOR_ARGB8888, 0, 0}},	/* fmt       */
};

/* layer para */
static __disp_layer_para_t lstlyr = 
{
    DISP_LAYER_WORK_MODE_NORMAL,                    /* mode      */
    0,                                              /* ck_mode   */
    0,                                              /* alpha_en  */
    0,                                              /* alpha_val */
    1,                                              /* pipe      */
    0xff,                                           /* prio      */
    {0, 0, 0, 0},						/* screen    */
    {0, 0, 0, 0},						/* source    */
    DISP_LAYER_OUTPUT_CHN_DE_CH1,				/* channel   */
    &fb_sdl							/* fb        */
};

static __gui_lyrcreate_info_t lyrcreate_info =
{
    "sdllayer",
    &lstlyr,
    GUI_LYR_STA_ON
};

static __gui_wincreate_para_t  sdl_win = 
{
	NULL,				// name
	{0,0,0,0},			// rect
	NULL,				// h_lyr
	SDL_AWUCG_cbCallBack,		// cb
	NULL				// attr
};



//void *cur_buf;

struct private_hwdata {
	H_LYR hLyr;
	H_WIN hWnd;				// ����еĻ�
};

SDL_Surface *AWUCG_SetVideoMode(_THIS, SDL_Surface *current,
				int width, int height, int bpp, Uint32 flags)
{
	H_LYR hLyr;
	H_WIN hWnd;
	GUI_LockExtMsg();

	this->FreeHWSurface(this, current);

	flags |= SDL_FULLSCREEN;

	fb_sdl.size.width = width;
	fb_sdl.size.height = height;
//	fb.fmt.type = 0;			// ��ʾRGBģʽ
	switch(bpp) {
		case 1:
			fb_sdl.fmt.fmt.rgb.pixelfmt = PIXEL_MONO_1BPP;
			lstlyr.mode = DISP_LAYER_WORK_MODE_PALETTE;
			SDL_ReallocFormat(current, bpp, 0, 0, 0, 0);
			flags |= SDL_HWPALETTE;
			break;
		case 2:
			fb_sdl.fmt.fmt.rgb.pixelfmt = PIXEL_MONO_2BPP;
			lstlyr.mode = DISP_LAYER_WORK_MODE_PALETTE;
			SDL_ReallocFormat(current, bpp, 0, 0, 0, 0);
			flags |= SDL_HWPALETTE;
			break;
		case 4:
			fb_sdl.fmt.fmt.rgb.pixelfmt = PIXEL_MONO_4BPP;
			lstlyr.mode = DISP_LAYER_WORK_MODE_PALETTE;
			SDL_ReallocFormat(current, bpp, 0, 0, 0, 0);
			flags |= SDL_HWPALETTE;
			break;
		case 8:
			fb_sdl.fmt.fmt.rgb.pixelfmt = PIXEL_MONO_8BPP;
			lstlyr.mode = DISP_LAYER_WORK_MODE_PALETTE;
			SDL_ReallocFormat(current, bpp, 0, 0, 0, 0);
			flags |= SDL_HWPALETTE;
			// ���õ�ɫ��
//			fb_sdl.fmt.fmt.rgb.palette.size = sizeof(colorpal);
//			fb_sdl.fmt.fmt.rgb.palette.size = 1024;
//			fb_sdl.fmt.fmt.rgb.palette.addr = colorpal;
			break;
		case 16:
			fb_sdl.fmt.fmt.rgb.pixelfmt = PIXEL_COLOR_RGB565;
			lstlyr.mode = DISP_LAYER_WORK_MODE_NORMAL;
			SDL_ReallocFormat(current, bpp, 0xF800, 0x7E0, 0x1F, 0);
			break;
		case 24:
			fb_sdl.fmt.fmt.rgb.pixelfmt = PIXEL_COLOR_RGB0888;
			lstlyr.mode = DISP_LAYER_WORK_MODE_NORMAL;
			SDL_ReallocFormat(current, bpp, 0xFF0000, 0xFF00, 0xFF, 0);
			break;
		case 32:
			fb_sdl.fmt.fmt.rgb.pixelfmt = PIXEL_COLOR_ARGB8888;
			lstlyr.mode = DISP_LAYER_WORK_MODE_NORMAL;
			SDL_ReallocFormat(current, bpp, 0xFF0000, 0xFF00, 0xFF, 0xFF000000);
			break;
	}
	//cur_buf = fb_sdl.addr[0] = (void *)SDL_malloc(width * height * (bpp>>3));	// �趨������
	//SDL_memset(cur_buf, 0, width * height * (bpp>>3));

	//fb.fmt.fmt.rgb.pixelfmt = pixe[bpp];
	//GUI_LyrSetFB(GUI_WinGetLyr(hWnd), &fb);	 // �趨��Ƶģʽ

	lstlyr.src_win.width = lstlyr.scn_win.width = width;
	lstlyr.src_win.height = lstlyr.scn_win.height = height;

	hLyr = GUI_LyrCreate(&lyrcreate_info);		// ����ͼ��
    
	sdl_win.rect.width  = width;
	sdl_win.rect.height = height;
	sdl_win.h_lyr = hLyr;
	hWnd = GUI_WinCreate(&sdl_win, GUI_WinGetFocus());
	GUI_WinSetFocus(hWnd);

	// layer�ö�
	GUI_LyrCacheOn();
	GUI_LyrSel(hLyr);
	GUI_LyrAlphaOff(hLyr);
	GUI_LyrSetSta(hLyr,GUI_LYR_STA_ON);		// �л���Ӳ��ʵ��
	GUI_LyrSetTop(hLyr);
	GUI_LyrCacheOff();

//	GUI_LyrGetFB(GUI_WinGetLyr(hWnd), &fb_sdl);

	GUI_LyrGetFB(hLyr, &fb_sdl);

	current->flags = flags | SDL_HWSURFACE;
	current->w = fb_sdl.size.width;
	current->h = fb_sdl.size.height;
	current->pitch = width  * (bpp>>3);
	if (fb_sdl.addr[0] == NULL)
		__wrn("framebuffer ptr == NULL.");
//	current->pixels = fb_sdl.addr[0];
	current->pixels = NULL;

	// Allocate the hardware data
	current->hwdata = (struct private_hwdata *)SDL_malloc(sizeof(struct private_hwdata));
	current->hwdata->hLyr = GUI_WinGetLyr(hWnd);
	current->hwdata->hWnd = hWnd;

	GUI_UnLockExtMsg();

	SDL_ShowCursor(0);				// �������
	return(current);
}

static int AWUCG_AllocHWSurface(_THIS, SDL_Surface *surface)
{
	// Ŀǰ��δʵ��, ���Ѿ�����׼��
	return(-1);
}
static void AWUCG_FreeHWSurface(_THIS, SDL_Surface *surface)
{
	if (surface->hwdata != NULL) {
		if (surface->hwdata->hWnd != NULL) {
			GUI_LyrSetSta(((__gui_win_t *)surface->hwdata->hWnd)->h_layer,GUI_LYR_STA_SUSPEND);	// ��ж�����
			GUI_WinDelete(surface->hwdata->hWnd);
		}
		if (surface->hwdata->hLyr != NULL) {
			GUI_LyrSetSta(surface->hwdata->hLyr,GUI_LYR_STA_SUSPEND);
			GUI_LyrDelete(surface->hwdata->hLyr);
		}
		SDL_free(surface->hwdata);
		surface->hwdata = NULL;
	}
	return;
}

static Uint32 lcd_locksur;

/* We need to wait for vertical retrace on page flipped displays */
static int AWUCG_LockHWSurface(_THIS, SDL_Surface *surface)
{
	FB  fb;
	if (surface->hwdata != NULL && !lcd_locksur) {
		GUI_LyrGetFB(surface->hwdata->hLyr, &fb);
		surface->pixels = fb.addr[0];
	}
	return (surface->pixels != NULL) - 1;
}

static void AWUCG_UnlockHWSurface(_THIS, SDL_Surface *surface)
{
	if (surface->hwdata != NULL)
		surface->pixels = NULL;
	return;
}

/* ���¾��� */
static void AWUCG_UpdateRects(_THIS, int numrects, SDL_Rect *rects)
{
//	�˺���Ŀǰʵ��Ϊ�գ������뱣���˺�����

//	if (hWnd != NULL) {
//		GUI_LyrFlushFB(((__gui_win_t *)(hWnd))->h_layer);	// ˢ��FB
//	}
}

#define PALATTE_SIZE		1024

extern Uint32 SDLX_SwitchLCDAutooff();

int AWUCG_SetColors(_THIS, int firstcolor, int ncolors, SDL_Color *colors)
{
#if	0
	// do nothing of note.
	//return(1);
#else
	// ����ֵ�˜ʣ�
	// ��surface�K����һ���{ɫ�廯��ƽ�棬�t�˺���ʲ��Ҳ�������K����0��
	// �������ɫ���т��ͽoSDL_SetColors�O�úã��t������1���������е�
	// �ɫ�����_�ذ�Ҫ���O�����t������0���K���㑪ԓͨ�^�鿴ƽ���{ɫ
	// ���_�����H���{ɫ�塣  

	// ���µ�ɫ��
	//GUI_LyrGetFB(GUI_WinGetLyr(hWnd), &fb_sdl);

	// colorpal����Ҫʹ�ö�ջ����malloc�Ŀռ�(����cockoo��lylicԴ����ó��Ľ���)
	ES_FILE *p_disp;
	short r,g,b,a;
	int i,j;
	int ret;

	Uint32 colorpal[PALATTE_SIZE / sizeof(Uint32)];
	a = 0xFF;
//	a = 0;

	for(i=firstcolor, j=firstcolor+ncolors; i<j; ++i) {		// ����pal
		r = colors[i].r>>3;
		g = colors[i].g>>3;
		b = colors[i].b>>3;
// 		a = colors[i].a>>3;
		colorpal[i]=(Uint32)((a<<24) | (r<<16) | (g<<8) | b);
	}
	//
	// ��V8000xƽ̨�ϣ��Զ��������޸ĵ�ɫ���п��ܵ���ϵͳ����(Ns�Ժ�)��
	// ��Ŀǰ����֪��Ӧ����ν��������⣬������ʮ�ּ��֡�
	//
// BUG Fixing
	GUI_LockExtMsg();
	// ֱ���޸ĵ�ɫ��(��Ȼò�Ʋ�̫��׼, cockoo��lylicԴ����Ҳ����������)
	p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
	if(p_disp == NULL) {
		__wrn("open display device fail!\n");
		return 0;
	}
	ret = eLIBs_fioctrl(p_disp,DISP_CMD_SET_PALETTE_TBL, PALATTE_SIZE, colorpal);		// Ӳ�����µ�ɫ��
	eLIBs_fclose(p_disp);
	GUI_UnLockExtMsg();
// BUG Fixing

//	GUI_LyrSetFB(GUI_WinGetLyr(hWnd), &fb_sdl);
	return (ret == EPDK_OK);
#endif
}


void AWUCG_VideoQuit(_THIS)
{
	//GUI_LockExtMsg();
	// �ص�����
	if (this->screen->pixels != NULL)
		this->screen->pixels = NULL;
	this->FreeHWSurface(this, this->screen);
	SDLX_SetLCDBright(SLCD_BRIGHT);				// �ָ�ԭ��������
	GUI_LyrCacheOn();
	GUI_LyrSetSta(GUI_LyrGetBackLyr(), GUI_LYR_STA_ON);	// ��������ͼ��
	GUI_LyrCKOn(GUI_LyrGetBackLyr());
    	GUI_LyrCacheOff();
	//GUI_WinSetFocus(h_listMenu);
	//GUI_UnLockExtMsg();
}


/////////////////////////////////////////////////SDLX///////////////////////////////////////////

Uint32 SDLX_GetDefLCDBright()
{
	return SLCD_BRIGHT;
}

Uint32 SDLX_GetScreenWidth()
{
	return LCD_WIDTH;
}

Uint32 SDLX_GetScreenHeight()
{
	return LCD_HEIGHT;
}

int SDLX_GetLCDBright(void)
{
	int val;
	ES_FILE *p_disp;
	p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
	if(!p_disp) return -1;
	val = eLIBs_fioctrl(p_disp,DISP_CMD_LCD_GET_BRIGHTNESS,0,0);
	eLIBs_fclose(p_disp);
	return val;
}

int SDLX_GetLCDContrast(void)
{
	int val;
	ES_FILE *p_disp;
	p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
	if(!p_disp) return -1;
	val = eLIBs_fioctrl(p_disp,DISP_CMD_LCD_GET_CONTRAST,0,0);
	eLIBs_fclose(p_disp);
	return val;
}

int SDLX_SetLCDBright(int val)
{
	__s32 ret;
	ES_FILE *p_disp;
	p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
	if(!p_disp) return 0;
	ret = eLIBs_fioctrl(p_disp,DISP_CMD_LCD_SET_BRIGHTNESS,(__s32)val,0);
	eLIBs_fclose(p_disp);
	return ret == EPDK_OK;
}

int SDLX_SetLCDContrast(int val)
{
	__s32 ret;
	ES_FILE *p_disp;
	p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
	if(!p_disp) return 0;
	ret = eLIBs_fioctrl(p_disp,DISP_CMD_LCD_SET_CONTRAST,(__s32)val,0);
	eLIBs_fclose(p_disp);
	return ret == EPDK_OK;
}

void __SDLX_LCD_Changed(Uint32 b)
{
	if (!b) {
		lcd_locksur = 1;
		SDL_VideoSurface->pixels = NULL;
	} else lcd_locksur = 0;
}


Uint32 SDLX_LCDPowerOn(void)
{
	__s32 val;
	ES_FILE *p_disp;
	p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
	if(!p_disp) return 0;
	val = eLIBs_fioctrl(p_disp,DISP_CMD_LCD_ON,0,0);
	eLIBs_fclose(p_disp);
	if (val == EPDK_OK) {
		__SDLX_LCD_Changed(1);
		return 1;
	}
	return 0;
}

Uint32 SDLX_LCDPowerOff(void)
{
	__s32 val;
	ES_FILE *p_disp;
	p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
	if(!p_disp) return 0;
	val = eLIBs_fioctrl(p_disp,DISP_CMD_LCD_OFF,0,0);
	eLIBs_fclose(p_disp);
	if (val == EPDK_OK) {
		__SDLX_LCD_Changed(0);
		return 1;
	}
	return 0;
}

Uint32 SDLX_TVOutOn(void)
{
	__s32 val;
	ES_FILE *p_disp;
	p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
	if(!p_disp) return 0;
	val = eLIBs_fioctrl(p_disp,DISP_CMD_TV_ON,0,0);
	eLIBs_fclose(p_disp);
	return val == EPDK_OK;
}

Uint32 SDLX_TVOutOff(void)
{
	__s32 val;
	ES_FILE *p_disp;
	p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
	if(!p_disp) return 0;
	val = eLIBs_fioctrl(p_disp,DISP_CMD_TV_OFF,0,0);
	eLIBs_fclose(p_disp);
	return val == EPDK_OK;
}
