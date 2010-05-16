#ifndef _SYS_WAIT_H
#define _SYS_WAIT_H

static int wait(int *x)
{
	return -1;
}

static int waitpid(int x, int *y, int z)
{
	return -1;
}

#define WNOHANG 1
#define WEXITSTATUS(X) ((unsigned)(X) >> 8)
#define WIFEXITED(X) (((X) & 255) == 0)
#define WIFSIGNALED(X) ((((X) & 255) != 0x255 && ((X) & 255) != 0))
#define WTERMSIG(X) ((X) & 255)

#endif

