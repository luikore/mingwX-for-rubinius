#ifndef	_SIGNAL_H_
#define	_SIGNAL_H_

#include <_mingw.h>
#include <sys/types.h>

/* Historic */
#define SIGHUP	1
#define SIGINT	2
#define SIGQUIT	3
#define SIGILL	4
#define SIGTRAP	5
#define SIGABRT	6
#define SIGEMT  7
#define SIGFPE	8
#define SIGKILL	9
#define SIGBUS	10
#define SIGSEGV	11
#define SIGSYS	12
#define SIGPIPE	13
#define SIGALRM	14
#define SIGTERM	15

/* Modern */
#define SIGUSR1	16
#define SIGUSR2	17
#define SIGCHLD	18
#define SIGIO	19
#define SIGWINCH 20
#define SIGURG	21
#define SIGPOLL	22
#define SIGSTOP	23
#define SIGTSTP	24
#define SIGCONT	25
#define SIGTTIN	26
#define SIGTTOU	27
#define SIGVTALRM 28
#define SIGPROF	29
#define SIGXCPU	30
#define SIGXFSZ	31
#define SIGCANCEL 32

/* sig count */
#define NSIG 32

#ifndef _SIG_ATOMIC_T_DEFINED
typedef int sig_atomic_t;
#define _SIG_ATOMIC_T_DEFINED
#endif

/*
 * Pointer to signal handler function.
 */
typedef	void (*__p_sig_fn_t)(int);

/*
 * These are special values of signal handler pointers which are
 * used to send a signal to the default handler (SIG_DFL), ignore
 * the signal (SIG_IGN), indicate an error return (SIG_ERR),
 * get an error (SIG_SGE), or acknowledge (SIG_ACK).
 */
#define	SIG_DFL	((__p_sig_fn_t) 0)
#define	SIG_IGN	((__p_sig_fn_t) 1)
#define	SIG_ERR ((__p_sig_fn_t) -1)
#define SIG_SGE ((__p_sig_fn_t) 3)
#define SIG_ACK ((__p_sig_fn_t) 4)

struct sigaction {
    __p_sig_fn_t sa_handler;
    sigset_t sa_mask;
    int sa_flags;
};

typedef struct {
    void * ss_sp;
    size_t ss_size;
    int    ss_flags;
} stack_t;

#ifdef __cplusplus
extern "C" {
#endif

extern int sigfillset(sigset_t *);
extern int sigaddset(sigset_t *, int);
extern int sigdelset(sigset_t *, int);
extern int sigemptyset(sigset_t *);
extern int sigismember(sigset_t *, int);

extern int sigaction(int, const struct sigaction *, struct sigaction *);

extern int kill(pid_t, int);

/* sigprocmask how */
#define SIG_BLOCK	1
#define SIG_SETMASK	2
#define SIG_UNBLOCK	3
extern int sigprocmask(int, const sigset_t *, sigset_t *);
#define pthread_sigmask sigprocmask

#define SIGNAL_NOT_DEPRECATED
#ifdef SIGNAL_NOT_DEPRECATED
/* signal() may be deprecated in POSIX 2008 */
extern __p_sig_fn_t __cdecl mingwx_signal(int, __p_sig_fn_t);
#define signal mingwx_signal
#endif

/* impl by msvcrt */
_CRTIMP int __cdecl __MINGW_NOTHROW	raise(int);

#ifdef __cplusplus
}
#endif

#endif	/* _SIGNAL_H_ */

