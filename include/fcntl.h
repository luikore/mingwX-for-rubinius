#ifndef _FCNTL_H_
#define _FCNTL_H_

#include <_mingw.h>
#include <io.h>

#define	O_RDONLY     0x0000
#define O_WRONLY     0x0001
#define O_RDWR       0x0002
#define O_ACCMODE    0x0003
#define	O_APPEND     0x0008
#define	O_RANDOM     0x0010
#define O_SEQUENTIAL 0x0020
#define	O_TEMPORARY  0x0040
#define O_NOINHERIT  0x0080
#define	O_CREAT      0x0100
#define	O_TRUNC      0x0200
#define	O_EXCL       0x0400
#define O_NONBLOCK   0x1000
#define	O_TEXT       0x4000
#define	O_BINARY     0x8000

#if (__MSVCRT_VERSION__ >= 0x0800)
#define O_WTEXT     0x10000
#define O_U16TEXT   0x20000
#define O_U8TEXT    0x40000
#endif

# define F_GETFL		3
# define F_SETFL		4

#ifdef __cplusplus
extern "C" {
#endif

/* Perform file control operations on FD.  */
extern int __cdecl fcntl (int fd, int cmd, ...);

#ifdef __cplusplus
}
#endif

#endif	/* _FCNTL_H_ */
