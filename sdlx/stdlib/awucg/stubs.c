// stubs
#include "epdk.h"
#include "SDL_config.h"
#include "SDL_stdinc.h"

void *malloc(size_t size)
{
	return (void *)esMEMS_Malloc(NULL,size);
}

void free(void *ptr)
{
	esMEMS_Mfree(NULL,ptr);
}

void *realloc(void *mem, size_t size)
{
	return (void *)esMEMS_Realloc(NULL,mem, size);
}

void * calloc(size_t nmemb, size_t size)
{
	return (void *)esMEMS_Calloc(NULL, nmemb, size);
}

/*
char * strdup(const char *string)
{
	return SDL_strdup(string);
}
*/

#include <stdlib.h>

#ifndef min
#define min(a,b) ((a)>(b)? (b):(a))
#endif

size_t strlcpy(char *dst, const char *src, size_t maxlen)
{
    size_t srclen = strlen(src);
    if (maxlen>0 ) {
        size_t len = min(srclen, maxlen-1);
        memcpy(dst, src, len);
        dst[len] = '\0';
    }
    return srclen;
}

char *strdup(const char *string)
{
	size_t len = strlen(string)+1;
	char *newstr = malloc(len);
	if (newstr != NULL)
		strlcpy(newstr, string, len);
	return newstr;
}


int errno;

/*
// 不知道为什么，引用这个就fault
void abort(void)
{
	exit(0);
}
*/

int rand(void)
{
	return esKSRV_Random(RAND_MAX);
}


void (*atexit_func[128])(void);
int atexit_ptr;

void _exitcs()
{
	int i;
	for(i=0; i<atexit_ptr; ++i)
		atexit_func[i]();
}

int atexit(void (*func)(void))
{
	atexit_func[atexit_ptr++] = func;
	return 0;
}

void _sys_exit(int return_code)
{
	esKRNL_TDel(OS_PRIO_SELF);			// 自杀
}

void exit(int status)
{
	_exitcs();
	_sys_exit(status);
}




