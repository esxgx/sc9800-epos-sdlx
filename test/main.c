#include "SDL.h"
SDL_Surface *screen;


#pragma import(__use_no_semihosting_swi)


void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)

{

int bpp = surface->format->BytesPerPixel;


Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;


switch(bpp) {

case 1:

*p = pixel;

break;


case 2:

*(Uint16 *)p = pixel;

break;


case 3:

if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {

p[0] = (pixel >> 16) & 0xff;

p[1] = (pixel >> 8) & 0xff;

p[2] = pixel & 0xff;

} else {

p[0] = pixel & 0xff;

p[1] = (pixel >> 8) & 0xff;

p[2] = (pixel >> 16) & 0xff;

}

break;


case 4:

*(Uint32 *)p = pixel;

break;

}

}
/*
char *files[]= {
	"e:\\pal\\ABC.MKF",
	"e:\\pal\\BALL.MKF",
	"e:\\pal\\DATA.MKF",
	"e:\\pal\\desc.dat",
	"e:\\pal\\FPAL.MKF",
	"e:\\pal\\FBP.MKF",
	"e:\\pal\\FIRE.MKF",
	"e:\\pal\\GOP.MKF",
	"e:\\pal\\logo.bin",
	"e:\\pal\\MPAL.MSG",
	"e:\\pal\\MAP.MKF",
	"e:\\pal\\MGO.MKF",
	"e:\\pal\\MIDI.MKF",
	"e:\\pal\\MPU401.DRV",
	"e:\\pal\\MUS.MKF",
	"e:\\pal\\PAT.MKF",
	"e:\\pal\\RGM.MKF",
	"e:\\pal\\RNG.MKF",
	"e:\\pal\\SSS.MKF",
	"e:\\pal\\VOC.MKF",
	"e:\\pal\\wor16.asc",
	"e:\\pal\\wor16.fon",
	"e:\\pal\\WORD.DAT"
};
*/
extern int LCD_WIDTH, LCD_HEIGHT;

int main()
{
int x, y,quit;
Uint32 yellow;
SDL_Event event;
FILE *f;
char *a;
	int i,c,d;
	SDL_Init(SDL_INIT_VIDEO);
	GUI_UnLockExtMsg();
	//screen = SDL_SetVideoMode(LCD_WIDTH, LCD_HEIGHT, 24, SDL_SWSURFACE);


	screen = SDL_SetVideoMode(100, 100, 16, SDL_SWSURFACE | SDL_HWPALETTE);

	c = 0;

/*
	for(i=0; i<21; ++i) {
//		f = fopen(files[i], "r+");
		f = fopen("e:\\pal\\wor16.asc", "rb");
		if (f == NULL) {
			c++;
			d = i;
			continue;
		}
		fclose(f);
	}

	if (c) {
		if ( c < 5) {
				SDL_Quit();
				return 0;
		} else {
				SDL_Delay(c * 500);
				SDL_Quit();
				return 0;
		}
	}
*/
	a = (char *)malloc(2222);
	*a = 0x11111;
	free(a);

	yellow = SDL_MapRGB(screen->format, 0xff, 0xff, 0x00);

	//if (!screen->pixels) {

	//}


	x = screen->w / 2;
	y = screen->h / 2;
	SDL_LockSurface(screen);
	if (screen->pixels) {
		putpixel(screen, x, y, yellow);
		putpixel(screen, x+1, y, yellow);
		putpixel(screen, x, y+1, yellow);
		putpixel(screen, x+1, y+1, yellow);
	}
	SDL_UnlockSurface(screen);

	SDL_UpdateRect(screen, x, y, 2, 2);

//	SDL_Quit();
//	return 0;
//	SDL_Delay(1000);

	quit = 0;
while(!quit)
{
   while (SDL_PollEvent(&event))//轮询事件
   {
    switch (event.type)//事件类型
    {
    case SDL_KEYDOWN:
	//if   (   event.key.keysym.sym ==   SDLK_ESCAPE   ) {
		//quit = 1;
	//}
	printf("press: %s\n",SDL_GetKeyName(event.key.keysym.sym));
     break;
    case SDL_KEYUP:
	//if   (   event.key.keysym.sym ==   SDLK_ESCAPE   ) {
		quit = 1;
	//}
	printf("release: %s\n",SDL_GetKeyName(event.key.keysym.sym));
     break;
    case SDL_QUIT:
     quit = 1;
     break;
    case SDL_MOUSEBUTTONDOWN:
	printf("mouse down:(%d,%d)\n", event.button.x,event.button.y);
     break;
    case SDL_MOUSEMOTION:
	printf("mouse move:(%d,%d) to (%d,%d)\n",event.motion.xrel,event.motion.yrel,event.motion.x, event.motion.y);
     break;
    default:
     break;
    }
   }
}

	
	SDL_Quit();
	return 0;
}
