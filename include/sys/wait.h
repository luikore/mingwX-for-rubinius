#ifndef _SYS_WAIT_H
#define _SYS_WAIT_H

#define WIFEXITED(w)	(((w) & 0xff) == 0)
#define WIFSIGNALED(w)	(((w) & 0x7f) > 0 && (((w) & 0x7f) < 0x7f))
#define WIFSTOPPED(w)	(((w) & 0xff) == 0x7f)
#define WEXITSTATUS(w)	(((w) >> 8) & 0xff)
#define WTERMSIG(w)	((w) & 0x7f)
#define WSTOPSIG	WEXITSTATUS
#define WIFCONTINUED(stat_val)	0
#define WNOHANG			1
#define WCONTINUED		0
#define WUNTRACED		0

#ifdef __cplusplus
extern "C" {
#endif

typedef int pid_t;

extern pid_t __cdecl wait(int *stat_loc);
extern pid_t __cdecl waitpid(pid_t pid, int *stat_loc, int options);
extern pid_t __cdecl wait3(int *, int, struct rusage *);

#ifdef __cplusplus
}
#endif

#endif

