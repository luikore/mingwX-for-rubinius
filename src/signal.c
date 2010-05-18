#include <signal.h>
#include <errno.h>

// -----------------------------------------------------------------------------
// easy things

#define	MASK(signo)	(1 << ((signo) - 1))
#define ereturn errno = EINVAL; return -1

int sigfillset(sigset_t *a) {
	*a = ~0;
	return 0;
}

int sigaddset(sigset_t *a, int signo) {
	if (!a || signo < 1 || signo > NSIG) {
		ereturn;
	}
	*a |= MASK(signo);
	return 0;
}

int sigdelset(sigset_t *a, int signo) {
	if (!a || signo < 1 || signo > NSIG) {
		ereturn;
	}
	*a &= ~MASK(signo);
	return 0;
}
		
int sigemptyset(sigset_t *a) {
	*a = 0;
	return 0;
}

int sigismember(sigset_t *a, int signo) {
	if (!a || signo < 1 || signo > NSIG) {
		ereturn;
	}
	return ((*a) & MASK(signo)) ? 1 : 0;
}


// -----------------------------------------------------------------------------
// wrap CRT signal and raise

/*
msvcrt implemented functions: sinal() and raise()
http://msdn.microsoft.com/en-us/library/xdkz3x12(VS.71).aspx 

signals that can be handled are:

SIGINT		2	 Interactive attention
SIGILL		4	 Illegal instruction
SIGFPE		8	 Floating point error
SIGSEGV		11	 Segmentation violation
SIGTERM		15	 Termination request
SIGBREAK	21	 Control-break, FIXME: seems not included ?
SIGABRT		22	 Abnormal termination (abort)

The SIGILL, SIGSEGV, and SIGTERM signals are not generated under Windows NT. 
They are included for ANSI compatibility.
Thus you can set signal handlers for these signals with signal(),
and you can also explicitly generate these signals by calling raise().

Signal settings are not preserved in spawned processes created by calls to _exec or _spawn functions.
The signal settings are reset to the default in the new process.
*/

#undef signal
_CRTIMP __p_sig_fn_t __cdecl __MINGW_NOTHROW signal(int, __p_sig_fn_t);

/* block mask */
static sigset_t current_mask = 0;

/* store handlers */
static __p_sig_fn_t handlers[NSIG+1];
static int handlers_inited = 0;
static void init_handlers() {
	int i;
	for (i = 0; i <= NSIG; ++i) {
		handlers[i] = SIG_DFL;
	}
	handlers_inited = 1;
}

/* wrapper layer for msvcrt signal */
__p_sig_fn_t mingwx_signal(int signo, __p_sig_fn_t handler) {
	if (signo < 1 || signo > NSIG) {
		// FIXME should I set errno = EINVAL ?
		return SIG_ERR;
	}
	if (! handlers_inited) init_handlers();

	__p_sig_fn_t ohandler = handlers[signo];
	if (current_mask & MASK(signo)) {
		// masked, don't set
	} else {
		signal(signo, handler);
	}
	return ohandler;
}

// minimal modification ^_^
#define signal mingwx_signal

// -----------------------------------------------------------------------------
// sigaction

int sigaction(int sig, const struct sigaction *act, struct sigaction *oact) {
	/* note that sigaction always fails for SIGKILL */
	if (oact) {
		oact->sa_flags = 0;
		oact->sa_handler = signal(sig, SIG_IGN);
		if (sigemptyset(&oact->sa_mask) != 0 || oact->sa_handler == SIG_ERR) {
			ereturn;
		}
		signal(sig, oact->sa_handler);
	}
	if (act) {
		if (signal(sig, act->sa_handler) == SIG_ERR) {
			ereturn;
		}
	}
	return 0;
}


// -----------------------------------------------------------------------------
// sigprocmask

int sigprocmask (int how, const sigset_t *set, sigset_t *oset) {
	int i;
	if (! handlers_inited) init_handlers();

	// update mask
	switch (how) {
		case SIG_BLOCK:
			current_mask |= (*set);
			break;
		case SIG_SETMASK:
			current_mask = (*set);
			break;
		case SIG_UNBLOCK:
			current_mask &= (~(*set));
			break;
		default:
			ereturn;
	}
	*oset = current_mask;

	// update signal
	for (i = 1; i <= NSIG; i++) {
		if (!(current_mask & MASK(i))) {
			signal(i, handlers[i]);
		}
	}
	return 0;
}


// -----------------------------------------------------------------------------
// kill

#include <windows.h>
int kill(pid_t pid, int sig) {
	HANDLE h = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
	if (! h) {
		errno = ESRCH;
		return -1;
	} else {
		if (! TerminatedProcess(h, 0)) {
			return -1;
		}
	}
	return 0;
}
