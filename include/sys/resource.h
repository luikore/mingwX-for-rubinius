#ifndef _SYS_RESOURCE_H
#define _SYS_RESOURCE_H

#include <sys/time.h>		/* for struct timeval */

#define RLIMIT_CPU	0	/* cpu time in milliseconds */
#define RLIMIT_FSIZE	1	/* maximum file size */
#define RLIMIT_DATA	2	/* data size */
#define RLIMIT_STACK	3	/* stack size */
#define RLIMIT_CORE	4	/* core file size */
#define RLIMIT_RSS	5	/* resident set size */
#define RLIMIT_MEMLOCK	6	/* locked-in-memory address space */
#define RLIMIT_NPROC	7	/* number of processes */
#define RLIMIT_NOFILE	8	/* number of open files */
#define RLIM_NLIMITS	9	/* number of resource limits */
#define RLIM_INFINITY	((long) ((1UL << 31) - 1UL))

struct rlimit {
	long  rlim_cur;
	long  rlim_max;
};
typedef struct rlimit  rlimit_t;

struct  rusage {
        struct timeval ru_utime;        /* user time used */
        struct timeval ru_stime;        /* system time used */
        long    ru_maxrss;
#define ru_first        ru_ixrss
        long    ru_ixrss;               /* XXX: shared memory size */
        long    ru_idrss;               /* XXX: unshared data */
        long    ru_isrss;               /* XXX: unshared stack */
        long    ru_minflt;              /* page faults not requiring I/O */
        long    ru_majflt;              /* page faults requiring I/O */
        long    ru_nswap;               /* swaps */
        long    ru_inblock;             /* block input operations */
        long    ru_oublock;             /* block output operations */
        long    ru_msgsnd;              /* messages sent */
        long    ru_msgrcv;              /* messages received */
        long    ru_nsignals;            /* signals received */
        long    ru_nvcsw;               /* voluntary context switches */
        long    ru_nivcsw;              /* involuntary " */
#define ru_last         ru_nivcsw
};

#define RUSAGE_SELF 	0
#define RUSAGE_CHILDREN	1

#ifdef __cplusplus
extern "C" {
#endif 

extern int __cdecl getrusage(int, struct rusage *);
extern int __cdecl getrlimit(int, struct rlimit *);
extern int __cdecl setrlimit(int, const struct rlimit *);

#ifdef __cplusplus
}
#endif 

#endif /* _SYS_RESOURCE_H */
