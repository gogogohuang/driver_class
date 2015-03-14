#ifndef _CDATA_IOCTL_H_
#define _CDATA_IOCTL_H_

//#define IOCTL_INIT  _IO(0xD0, 1)
//#define IOCTL_SHUTDOWN  _IO(0xD0, 2)
#define IOCTL_WRITE _IOW(0xD0, 1, int)
#define IOCTL_SetName       _IOWR(0xD0, 2, int)
#define IOCTL_EmptyName     _IO(0xD0, 3)
#define IOCTL_SyncName      _IOR(0xD0, 4, int)
#define IOCTL_Init          _IO(0xD0, 5)
#define IOCTL_SetAll        _IOW(0xD0, 6, int)

#define KERNEL_DELAY_TIMER  300
#define LEN_OF_NAME 8
#define Cdata_Debug_Enable 1

#if  Cdata_Debug_Enable
#define CDATA_DEBUG_PRINT printf
#else
#define CDATA_DEBUG_PRINT(...)
#endif

#endif
