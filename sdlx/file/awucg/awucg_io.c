#include "_stdio.h"
#include "epdk.h"

#undef ioctl

// 设备控制原型
int ioctl(FILE *stream, int request, int aux, void *pBuffer)
{
	return eLIBs_fioctrl((ES_FILE *)stream, request, aux, pBuffer);	
}

#include "direct.h"

int mkdir(const char *dp)
{
	return (int)eLIBs_mkdir(dp);
}

int rmdir(const char *dp)
{
	return (int)eLIBs_rmdir(dp);
}

DIR *opendir(const char *dirname)
{
	return (DIR *)eLIBs_opendir(dirname);
}

int closedir(DIR * p)
{
	return (int)eLIBs_closedir((ES_DIR *)p);
}

struct dirent * readdir(DIR * dirp)
{
	ES_DIRENT *t;
	t = eLIBs_readdir((ES_DIR *)dirp);
	// 转换, 目前不需要, 因为ESDIRECT结构为
	//typedef struct __ESDIRENT
	//{
	//  __u32     d_ino;              // to be POSIX conform
	//  __u8      fatdirattr;         // FAT only. Contains the "DIR_Attr" field of an entry.
	//  __u64     d_size;             // file size, if directory it will be 0
	//  __u8      d_name[260];
	// }ES_DIRENT;
	return (struct dirent *)t;
}

int rewinddir(DIR * dir)
{
	eLIBs_rewinddir((ES_DIR *)dir);
	return 0;
}
