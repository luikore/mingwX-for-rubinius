/*C+
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * 
 * This Software Source is the unpublished, valuable, confidential property
 * of Microsoft Corporation.  Use is authorised only under the terms and
 * conditions set out in the source code licence agreement protecting this
 * Software Source.  Any unauthorised use or disclosure of this Software 
 * Source is prohibited.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' BY MICROSOFT CORPORATION AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL MICROSOFT CORPORATION BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *C-
 */ 

/* RCSid = $Header: /E/interix/include/sys/resource.h,v 1.8 1999/05/07 21:02:27 mark Exp $
 */

#ifndef _SYS_RESOURCE_H
#define _SYS_RESOURCE_H

#ifdef __cplusplus
extern "C" {
#endif 

#include <sys/types.h>		/* for id_t */
#include <sys/time.h>		/* for struct timeval */

/* 
 * process priority constants (for setpriority() and getpriority())
 */
#define PRIO_PROCESS	0
#define PRIO_PGRP	1
#define PRIO_USER	2

#define PRIO_MIN	-2
#define PRIO_MAX	2

//extern int _CRTAPI1 getpriority(int which, id_t who);
//extern int _CRTAPI1 setpriority(int which, id_t who, int prio);

/*
 * process resource limits definitions
 */
typedef unsigned long long rlim_t;

struct rlimit {
	rlim_t  rlim_cur;
	rlim_t  rlim_max;
};

typedef struct rlimit  rlimit_t;

#define RLIM_INFINITY	((rlim_t)(-1))

#define RLIMIT_CPU	0   /* limit on CPU time per process */
#define RLIMIT_FSIZE	1   /* limit on file size */
#define RLIMIT_DATA	2   /* limit on data segment size */
#define RLIMIT_STACK	3   /* limit on process stack size */
#define RLIMIT_CORE	4   /* limit on size of core dump file */
#define RLIMIT_NOFILE	5   /* limit on number of open files */
#define RLIMIT_AS	6   /* limit on process total address space size */
#define RLIMIT_VMEM	RLIMIT_AS

#define RLIM_NLIMITS	7

//int _CRTAPI1 getrlimit(int, struct rlimit *);
//int _CRTAPI1 setrlimit(int, const struct rlimit *);


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

//int __cdecl getrusage(int, struct rusage *);

#ifdef __cplusplus
}
#endif 

#endif /* _SYS_RESOURCE_H */
