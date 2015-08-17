//
// SDL & X ϵͳ(io.h)
// Sochip, AWMicro 2010.5.2
//
#ifndef __AXF_H
#define __AXF_H

//
// SDLX_SDK���ͷ�ļ�
// ע�⣬ֻҪһ���ļ����������Ϳ����ˡ�
// ����һ���ļ����������
//

typedef unsigned int	__u32;
typedef unsigned char	__u8;
typedef signed int	__s32;

// �������ȼ�����
#define KRNL_priolevel0	0	// ϵͳ����(��ߵȼ�)
#define KRNL_priolevel1	1
#define KRNL_priolevel2	2
#define KRNL_priolevel3	3
#define KRNL_priolevel4	4
#define KRNL_priolevel5	5
#define KRNL_priolevel6	6
#define KRNL_priolevel7	7	// ϵͳ����(��͵ȼ�)

#ifndef EEXF_H
typedef struct __EXEC_MGSEC
{
	char	magic[8];			// "ePDK.exf"
	__u32	version;
	__u8	type;				// 0: reserved

	__u32	heapaddr;			//heap��32M�ռ��ڵ�λ�ã�ͨ�������1M(31*1024*1024)
						//����ַ����0����ô��ʾ���̲���Ҫ�ֲ��ѣ�������ϵͳ��
	__u32	heapsize;			//heap�ĳ�ʼ��С
	
	__s32  (*main)(void * p_arg);	//pcb���һ��������׵�ַ
	__u32	mtskstksize;			// stack size
	__u8	mtskprio;			// �������ȼ�
} __exec_mgsec_t;
#endif



#ifndef __NO_S
#define __NO_S

#ifndef __SDLX_STACK_SIZE
// sdlpal ��0x40000����������, ��0x4000�Ͳ���(���Զ���) V6000HDV��������
#define __SDLX_STACK_SIZE	0x40000
#endif

extern __s32 __sdlx_init(void *p_arg);

#pragma arm section rodata="MAGIC"
const __exec_mgsec_t exfinfo =
{
	{'e','P','D','K','.','e','x','f'},	//.magic
	0x01000000,				//.version
	0,					//.type
	0x1F00000,				// ���̶ѵĵ�ַ������С��32M�����ұ�֤�ѵķ��ò������32M�߽�
	0x400,					// ���̶Ѵ�С(��ֵ������������Ҫ���Զ����ӣ�������ܲ���32M�߽�)
	__sdlx_init,				// ��������ڵ�ַ
	__SDLX_STACK_SIZE,			// ������ջ��С
    	KRNL_priolevel5			// ���������ȼ�
};
#pragma arm section

#endif

#endif	// !__AXF_H
