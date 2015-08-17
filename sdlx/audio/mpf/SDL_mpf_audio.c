
#include "SDL_config.h"


#include "SDL_rwops.h"
#include "SDL_timer.h"
#include "SDL_audio.h"
#include "../SDL_audiomem.h"
#include "../SDL_audio_c.h"
#include "../SDL_audiodev_c.h"
#include "SDL_mpf_audio.h"

#define MPFAUD_DRIVER_NAME         "mpf"

static int MPFAUD_OpenAudio(_THIS, SDL_AudioSpec *spec);
static void MPFAUD_WaitAudio(_THIS);
static void MPFAUD_PlayAudio(_THIS);
static Uint8 *MPFAUD_GetAudioBuf(_THIS);
static void MPFAUD_CloseAudio(_THIS);

static int MPFAUD_Available(void)
{
	return(1);
}

static void MPFAUD_DeleteDevice(SDL_AudioDevice *device)
{
	SDL_free(device->hidden);
	SDL_free(device);
}

static SDL_AudioDevice *MPFAUD_CreateDevice(int devindex)
{
	SDL_AudioDevice *this;

	/* Initialize all variables that we clean on shutdown */
	this = (SDL_AudioDevice *)SDL_malloc(sizeof(SDL_AudioDevice));
	if ( this ) {
		SDL_memset(this, 0, (sizeof *this));
		this->hidden = (struct SDL_PrivateAudioData *)
				SDL_malloc((sizeof *this->hidden));
	}

	if ( (this == NULL) || (this->hidden == NULL) ) {
		SDL_OutOfMemory();
		if ( this ) {
			SDL_free(this);
		}
		return(0);
	}
	SDL_memset(this->hidden, 0, (sizeof *this->hidden));

	/* Set the function pointers */
	this->OpenAudio = MPFAUD_OpenAudio;
	this->WaitAudio = MPFAUD_WaitAudio;
	this->PlayAudio = MPFAUD_PlayAudio;
	this->GetAudioBuf = MPFAUD_GetAudioBuf;
	this->CloseAudio = MPFAUD_CloseAudio;

	this->free = MPFAUD_DeleteDevice;

	return this;
}

AudioBootStrap MPFAUD_bootstrap = {
	MPFAUD_DRIVER_NAME, "SDL mpf audio driver",
	MPFAUD_Available, MPFAUD_CreateDevice
};

/* This function waits until it is possible to write a full sound buffer */
static void MPFAUD_WaitAudio(_THIS)
{
	 sys_sound_canwrite();
}

static void MPFAUD_PlayAudio(_THIS)
{	
	sys_sound_write(this->hidden->mixbuf ,this->hidden->mixlen);
}

static Uint8 *MPFAUD_GetAudioBuf(_THIS)
{
	return(this->hidden->mixbuf);
}

static void MPFAUD_CloseAudio(_THIS)
{
	if ( this->hidden->mixbuf != NULL ) {
		SDL_FreeAudioMem(this->hidden->mixbuf);
		this->hidden->mixbuf = NULL;
	}
	sys_sound_deinit();
}

static int MPFAUD_OpenAudio(_THIS, SDL_AudioSpec *spec)
{
	float bytes_per_sec = 0.0f;

	/* Allocate mixing buffer */
	this->hidden->mixlen = spec->size;
	this->hidden->mixbuf = (Uint8 *) SDL_AllocAudioMem(this->hidden->mixlen);
	if ( this->hidden->mixbuf == NULL ) {
		return(-1);
	}
	SDL_memset(this->hidden->mixbuf, spec->silence, spec->size);

	bytes_per_sec = (float) (((spec->format & 0xFF) / 8) *
	                   spec->channels * spec->freq);

	int format;
	switch (spec->format & 0xff) {
		case 8:format=8;break;
		case 16:format=16;break;
		default:
			SDL_SetError("Unsupported audio format");
			return -1;
	}
	sys_sound_init(spec->freq,format,spec->channels);

	/* We're ready to rock and roll. :-) */
	return(0);
}

