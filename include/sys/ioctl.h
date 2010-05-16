#ifndef _SYS_IOCTL_H
#define _SYS_IOCTL_H

#include <windows.h>
#include <winioctl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int __cdecl ioctl(int fd, int request, ...);

#ifdef __cplusplus
}
#endif

#endif

