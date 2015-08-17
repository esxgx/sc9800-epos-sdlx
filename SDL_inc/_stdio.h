#ifndef __STDIO_H
#define __STDIO_H


/*
struct __FILE;
typedef struct __FILE FILE;
*/
typedef unsigned int size_t;




#ifdef __cplusplus
extern "C" {
#endif

//FILE *fopen(const char * /*filename*/, const char * /*mode*/);
//int fclose(FILE * /*stream*/);
//size_t fread(void * /*ptr*/,size_t /*size*/, size_t /*nmemb*/, FILE * /*stream*/);
//size_t fwrite(const void * /*ptr*/,size_t /*size*/, size_t /*nmemb*/, FILE * /*stream*/);
//int fseek(FILE * fp, long offset, int whence);
//long int ftell(FILE * fp);
//int fgetc(FILE *fp);
//int fputc(int c, FILE *fp);
//char *fgets(char *s, int n, FILE *fp);
//int fputs(const char *s, FILE *fp);
//int fprintf(FILE * /*stream*/, const char * /*format*/, ...);
//int printf(const char * /*format*/, ...);

#ifdef __cplusplus
};
#endif

#ifndef __SDLX_NO_STDIO
#include <stdio.h>
#endif

#endif
