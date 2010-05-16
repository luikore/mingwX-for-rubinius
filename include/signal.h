/* 
 * signal.h
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is a part of the mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within the package.
 *
 * A way to set handlers for exceptional conditions (also known as signals).
 *
 */

#ifndef	_SIGNAL_H_
#define	_SIGNAL_H_

/* All the headers include this file. */
#include <_mingw.h>
#include <sys/types.h>

/*
 * The actual signal values. Using other values with signal
 * produces a SIG_ERR return value.
 *
 * NOTE: SIGINT is produced when the user presses Ctrl-C.
 *       SIGILL has not been tested.
 *       SIGFPE doesn't seem to work?
 *       SIGSEGV does not catch writing to a NULL pointer (that shuts down
 *               your app; can you say "segmentation violation core dump"?).
 *       SIGTERM comes from what kind of termination request exactly?
 *       SIGBREAK is indeed produced by pressing Ctrl-Break.
 *       SIGABRT is produced by calling abort.
 * TODO: The above results may be related to not installing an appropriate
 *       structured exception handling frame. Results may be better if I ever
 *       manage to get the SEH stuff down.
 */

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

#ifndef _SIG_ATOMIC_T_DEFINED
typedef int sig_atomic_t;
#define _SIG_ATOMIC_T_DEFINED
#endif

/*
 * The prototypes (below) are the easy part. The hard part is figuring
 * out what signals are available and what numbers they are assigned
 * along with appropriate values of SIG_DFL and SIG_IGN.
 */

/*
 * A pointer to a signal handler function. A signal handler takes a
 * single int, which is the signal it handles.
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

/* sig count + 1 */
#define NSIG 33    
#define	MASK(signo)	(1 << ((signo) - 1))

static int sigfillset(sigset_t *a) {
	*a = ~0;
	return 0;
}
static int sigaddset(sigset_t *a, int signo) {
	if (signo > NSIG - 1) {
		return -1;
	}
	*a |= MASK(signo);
	return 0;
}
static int sigemptyset(sigset_t *a) {
	*a = 0;
	return 0;
}

/* stubs */
static int pthread_sigmask(int a, const sigset_t *b, sigset_t *c) {
	return -1;
}
static int sigaction(int a, const struct sigaction *b, struct sigaction *c) {
	return -1;
}
static int sigprocmask(int how, const sigset_t *b, sigset_t *c) {
	return -1;
}

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Call signal to set the signal handler for signal sig to the
 * function pointed to by handler. Returns a pointer to the
 * previous handler, or SIG_ERR if an error occurs. Initially
 * unhandled signals defined above will return SIG_DFL.
 */
_CRTIMP __p_sig_fn_t __cdecl __MINGW_NOTHROW signal(int, __p_sig_fn_t);

/*
 * Raise the signal indicated by sig. Returns non-zero on success.
 */
_CRTIMP int __cdecl __MINGW_NOTHROW	raise (int);

#ifdef	__cplusplus
}
#endif

#endif	/* Not _SIGNAL_H_ */

