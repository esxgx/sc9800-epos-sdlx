
#include "SDL_config.h"


#include "SDL_rwops.h"
#include "SDL_timer.h"
#include "SDL_audio.h"
#include "../SDL_audiomem.h"
#include "../SDL_audio_c.h"
#include "../SDL_audiodev_c.h"
#include "SDL_awucg_audio.h"

#define AWUCGAUD_DRIVER_NAME         "awucg"

static int AWUCGAUD_OpenAudio(_THIS, SDL_AudioSpec *spec);
static void AWUCGAUD_WaitAudio(_THIS);
static void AWUCGAUD_PlayAudio(_THIS);
static Uint8 *AWUCGAUD_GetAudioBuf(_THIS);
static void AWUCGAUD_CloseAudio(_THIS);

static int AWUCGAUD_Available(void)
{
	return(1);
}

static void AWUCGAUD_DeleteDevice(SDL_AudioDevice *device)
{
	SDL_free(device->hidden);
	SDL_free(device);
}

static SDL_AudioDevice *AWUCGAUD_CreateDevice(int devindex)
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
	this->OpenAudio = AWUCGAUD_OpenAudio;
	this->WaitAudio = AWUCGAUD_WaitAudio;
	this->PlayAudio = AWUCGAUD_PlayAudio;
	this->GetAudioBuf = AWUCGAUD_GetAudioBuf;
	this->CloseAudio = AWUCGAUD_CloseAudio;

	this->free = AWUCGAUD_DeleteDevice;

	return this;
}

AudioBootStrap AWUCGAUD_bootstrap = {
	AWUCGAUD_DRIVER_NAME, "SDL awucg audio driver",
	AWUCGAUD_Available, AWUCGAUD_CreateDevice
};

/* This function waits until it is possible to write a full sound buffer */
static void AWUCGAUD_WaitAudio(_THIS)
{
	/* Don't block on first calls to simulate initial fragment filling. */
	if (this->hidden->initial_calls)
		this->hidden->initial_calls--;
	else
		SDL_Delay(this->hidden->write_delay);
	//sys_sound_canwrite();
}

static void AWUCGAUD_PlayAudio(_THIS)
{	
	//sys_sound_write(this->hidden->mixbuf ,this->hidden->mixlen);
}

static Uint8 *AWUCGAUD_GetAudioBuf(_THIS)
{
	return(this->hidden->mixbuf);
}

static void AWUCGAUD_CloseAudio(_THIS)
{
	if ( this->hidden->mixbuf != NULL ) {
		SDL_FreeAudioMem(this->hidden->mixbuf);
		this->hidden->mixbuf = NULL;
	}
	//sys_sound_deinit();
}

static int AWUCGAUD_OpenAudio(_THIS, SDL_AudioSpec *spec)
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

	/*
	 * We try to make this request more audio at the correct rate for
	 *  a given audio spec, so timing stays fairly faithful.
	 * Also, we have it not block at all for the first two calls, so
	 *  it seems like we're filling two audio fragments right out of the
	 *  gate, like other SDL drivers tend to do.
	 */
	this->hidden->initial_calls = 2;
	this->hidden->write_delay =
	               (Uint32) ((((float) spec->size) / bytes_per_sec) * 1000.0f);

	/* We're ready to rock and roll. :-) */
	return(0);

}

