//
// SDL & X ϵͳ(io.h)
// Sochip, AWMicro 2010.5.2
//
#ifndef __DIRECT_H
#define __DIRECT_H


//typedef unsigned long	__u32;
typedef unsigned int		__u32;
typedef unsigned char	__u8;
typedef unsigned __int64	__u64;

struct dirent {
	__u32		d_ino;
	__u8		d_off;
	__u64		d_reclen;
	char		d_name[1];
};

typedef	unsigned int		DIR;

#ifdef __cplusplus
extern "C" {
#endif

int mkdir(const char *);
int rmdir(const char *);
DIR *opendir(const char *);
int closedir(DIR *);
struct dirent * readdir(DIR *);
int rewinddir(DIR *);

#ifdef __cplusplus
};
#endif

#endif
