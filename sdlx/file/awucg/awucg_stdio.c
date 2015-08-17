// 2010.5.8 esxgx ���Ӷ��ڹ���Ŀ¼��֧��

#include "epdk.h"
#define __SDLX_NO_STDIO
#include "_stdio.h"

struct __FILE;
typedef struct __FILE FILE;

//char ptbuf[256];

char xfile[FSYS_DIRNAME_MAX];
int xdirp;

ES_FILE __stdout, __stdin, __stderr;

void _fcrt_name(char *ptbuf, const char *name)
{
	// epos �����е�б�ܱ任Ϊ��б��
	int i,j;
#if	0
	ES_FILE * edebug;
#endif

	i = j = 0;

	// ���������ǵ�ǰĿ¼���ͽ���һ���ļ���ת��
	if (name[0] == '.') {
		if (name[1] == '/' || name[1] == '\\') {
			while(j < xdirp) {
				ptbuf[j] = xfile[j];
				++j;
			}
			i = 1;		// BUG Fix 2010.5.8 esxgx
		}
	}
	while(name[i]) {
		if (name[i] == '/') ptbuf[j] = '\\';
		else ptbuf[j] = name[i];
		++i; ++j;
	}
	ptbuf[j] = '\0';		// ���ߣ��ҵĳ�����BUG! = =
#if	0
	edebug = eLIBs_fopen("e:\\fcrt_name.txt", "w+");
	eLIBs_fputs(ptbuf, edebug);
	eLIBs_fputc('\n', edebug);
	eLIBs_fclose(edebug);
#endif

}

FILE *fopen(const char *name, const char *mode)
{
	char ptbuf[FSYS_DIRNAME_MAX];
#if	0
	ES_FILE * edebug;
	edebug = eLIBs_fopen("e:\\fp_output.txt", "w+");
	eLIBs_fseek(edebug, 0, 2);
	eLIBs_fputs(name, edebug);
	eLIBs_fputc('\n', edebug);
	eLIBs_fclose(edebug);
#endif
	_fcrt_name(ptbuf, name);

	return (FILE *)eLIBs_fopen(ptbuf, mode);
}

int fclose(FILE *fp)
{
	if (fp == (FILE *)&__stdin || fp == (FILE *)&__stdout || fp == (FILE *)&__stderr)
		return 0;
	return eLIBs_fclose((ES_FILE *)fp);
}
#include <stdarg.h>

/*
int vsnprintf(char * s, size_t n, const char *format, va_list arg)
{
	return (int)SDL_vsnprintf(s,n,format,arg);		// ������������
}
*/

extern int vsnprintf(char *, size_t, const char *, va_list);

int fprintf(FILE *fp, const char * fmt, ...)
{
	char sbuf[2048];
	va_list ap;
	int retval;

	va_start(ap, fmt);
	retval = (int)vsnprintf(sbuf, 2048, fmt, ap);
	va_end(ap);

	if (fp == (FILE *)&__stdin || fp == (FILE *)&__stdout || fp == (FILE *)&__stderr)
		eLIBs_printf(sbuf);
	else eLIBs_fputs(sbuf, (ES_FILE *)fp);
	return retval;
}



int printf(const char *format,...)
{
	char sbuf[2048];
	va_list ap;
	int retval;

	va_start(ap, format);
	retval = (int)vsnprintf(sbuf, 2048, format, ap);
	va_end(ap);

	eLIBs_printf(sbuf);
	return retval;
}

// ��֪��Ϊʲô���������
int __0printf(const char *format,...)
{
	char sbuf[2048];
	va_list ap;
	int retval;

	va_start(ap, format);
	retval = (int)vsnprintf(sbuf, 2048, format, ap);
	va_end(ap);

	eLIBs_printf(sbuf);
	return retval;
}

/* �������� */
char *gets(char * s)
{
	esSIOS_gets(s);
	return s;
}

size_t fread(void *ptr,size_t size, size_t nmemb, FILE *fp)
{
#if	0
	ES_FILE * edebug;
	edebug = eLIBs_fopen("e:\\fp_fread_output.txt", "w+");
	eLIBs_fseek(edebug, 0, 2);
	fprintf(fp, "%x, %x, %x, %x, %x, %x, %x", ptr, size, nmemb, fp, &__stdin, &__stdout, &__stderr);
	eLIBs_fclose(edebug);
#endif
	if (fp == (FILE *)&__stdin || fp == (FILE *)&__stdout || fp == (FILE *)&__stderr)
		return size;				// ��ʵ��
	return eLIBs_fread(ptr,size,nmemb, (ES_FILE *)fp);
}

size_t fwrite(const void *ptr,size_t size, size_t nmemb, FILE *fp)
{
	if (fp == (FILE *)&__stdin || fp == (FILE *)&__stdout || fp == (FILE *)&__stderr)
		return size;				// ��ʵ��
	return eLIBs_fwrite(ptr,size,nmemb, (ES_FILE *)fp);
}

int fseek(FILE * fp, long offset, int whence)
{
	if (fp == (FILE *)&__stdin || fp == (FILE *)&__stdout || fp == (FILE *)&__stderr)
		return 0;				// ��ʵ��
	return eLIBs_fseek((ES_FILE *)fp, offset, whence);
}

long int ftell(FILE * fp)
{
	if (fp == (FILE *)&__stdin || fp == (FILE *)&__stdout || fp == (FILE *)&__stderr)
		return 0;				// ��ʵ��
	return eLIBs_ftell((ES_FILE *)fp);
}

int fgetc(FILE *fp)
{
	if (fp == (FILE *)&__stdin || fp == (FILE *)&__stdout || fp == (FILE *)&__stderr)
		return 0;				// ��ʵ��
	return eLIBs_fgetc((ES_FILE *)fp);
}


int fputc(int c, FILE *fp)
{
	if (fp == (FILE *)&__stdin || fp == (FILE *)&__stdout || fp == (FILE *)&__stderr)
		return 0;				// ��ʵ��
	return eLIBs_fputc(c, (ES_FILE *)fp);
}

char *fgets(char *s, int n, FILE *fp)
{
	// �����������, ��ʾ��Ļ����
	if (fp == (FILE *)&__stdin || fp == (FILE *)&__stdout || fp == (FILE *)&__stderr) {
		gets(s);
		return 0;
	}
	return eLIBs_fgets(s, n, (ES_FILE *)fp);
}

int fputs(const char *s, FILE *fp)
{
	// ���������������ʾ��Ļ���
	if (fp == (FILE *)&__stdin || fp == (FILE *)&__stdout || fp == (FILE *)&__stderr) {
		printf(s);
		return 0;
	}
	return eLIBs_fputs(s, (ES_FILE *)fp);
}

int fflush(FILE *stream)
{
	// request that all data for the open file descriptor named by fildes is to
	// be transferred to the storage device associated with the file described
	// by fildes..
	// Returns: zero if the stream was succesfully synced, or nonzero if any
	//          errors were detected or if the stream was already closed.
	return eLIBs_fsync((ES_FILE *)stream);
}

__krnl_tcb_t	tcb;
#define max(a,b)	((a)>(b)?(a):(b))

#include <string.h>
#include <stdlib.h>

char *__sdlx_getenvr(void)
{
	__u8		err;
	__krnl_tcb_t	*tcb;
#if	0
	ES_FILE * edebug;
#endif

//	����EPDK�����krnl.h��δ���£���������ڴ治�ܰ���sizeof(__krnl_tcb_t)��
//	���У�����ᵼ�¶�ջ�����
	tcb = (__krnl_tcb_t *)malloc(max(sizeof(__krnl_tcb_t), 0x1000)); 

	err = esKRNL_TaskQuery(OS_PRIO_SELF, tcb);
	if(err == OS_NO_ERR) {	// OS_NO_ERR
		if (tcb->xcb != NULL) {
			strcpy(xfile, tcb->xcb->xfile);
			xdirp = strlen(xfile);
			while(xdirp>=0 && xfile[xdirp] != '\\' && xfile[xdirp] != '/') --xdirp;
	#if	0
			edebug = eLIBs_fopen("e:\\tcb_xcb.txt", "w+");
			eLIBs_fseek(edebug, 0, 2);
			fprintf((FILE *)edebug, "%s\n%d\n", xfile, xdirp);
			eLIBs_fclose(edebug);
	#endif

		}
	}
	free(tcb);
	return xfile;
}

