#ifndef __STDLIB_H
#define __STDLIB_H

typedef unsigned int size_t;

#ifdef __cplusplus
extern "C" {
#endif

void * malloc(size_t);
void free(void *);
void *realloc(void *mem, size_t size);

int rand(void);
int atexit(void (*/*func*/)(void));
void exit(int /*status*/);
void abort(void);

#ifdef __cplusplus
};
#endif

#endif
