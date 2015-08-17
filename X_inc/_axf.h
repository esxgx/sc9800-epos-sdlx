//
// SDL & X 系统(io.h)
// Sochip, AWMicro 2010.5.2
//
#ifndef __AXF_H
#define __AXF_H

//
// SDLX_SDK入口头文件
// 注意，只要一个文件包含了它就可以了。
// 超过一个文件包含会出错。
//

typedef unsigned int	__u32;
typedef unsigned char	__u8;
typedef signed int	__s32;

// 任务优先级设置
#define KRNL_priolevel0	0	// 系统保留(最高等级)
#define KRNL_priolevel1	1
#define KRNL_priolevel2	2
#define KRNL_priolevel3	3
#define KRNL_priolevel4	4
#define KRNL_priolevel5	5
#define KRNL_priolevel6	6
#define KRNL_priolevel7	7	// 系统保留(最低等级)

#ifndef EEXF_H
typedef struct __EXEC_MGSEC
{
	char	magic[8];			// "ePDK.exf"
	__u32	version;
	__u8	type;				// 0: reserved

	__u32	heapaddr;			//heap在32M空间内的位置，通常在最后1M(31*1024*1024)
						//若地址等于0，那么表示进程不需要局部堆，将共用系统堆
	__u32	heapsize;			//heap的初始大小
	
	__s32  (*main)(void * p_arg);	//pcb里第一个任务的首地址
	__u32	mtskstksize;			// stack size
	__u8	mtskprio;			// 任务优先级
} __exec_mgsec_t;
#endif



#ifndef __NO_S
#define __NO_S

#ifndef __SDLX_STACK_SIZE
// sdlpal 在0x40000上运行正常, 而0x4000就不行(可自定义) V6000HDV是这样的
#define __SDLX_STACK_SIZE	0x40000
#endif

extern __s32 __sdlx_init(void *p_arg);

#pragma arm section rodata="MAGIC"
const __exec_mgsec_t exfinfo =
{
	{'e','P','D','K','.','e','x','f'},	//.magic
	0x01000000,				//.version
	0,					//.type
	0x1F00000,				// 进程堆的地址，必须小于32M，并且保证堆的放置不会操作32M边界
	0x400,					// 进程堆大小(初值，后续随着需要会自动增加，但最大不能操作32M边界)
	__sdlx_init,				// 主任务入口地址
	__SDLX_STACK_SIZE,			// 主任务栈大小
    	KRNL_priolevel5			// 主任务优先级
};
#pragma arm section

#endif

#endif	// !__AXF_H
