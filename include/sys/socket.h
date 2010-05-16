#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H

#include <winsock2.h>

#ifndef SOCKLEN_T_DEFINED
#define SOCKLEN_T_DEFINED
typedef int socklen_t;
#endif

static int fork()
{
	return -1;
}

static int pipe(int filedes[])
{
	return -1;
}

#define SHUT_RD SD_RECEIVE
#define SHUT_WR SD_SEND
#define SHUT_RDWR SD_BOTH

#endif

