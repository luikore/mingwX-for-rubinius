#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_

#include <sys/types.h>

/* protection flags */
#define	PROT_NONE	0x00	/* no access allowed */
#define	PROT_READ	0x01	/* pages can be read */
#define	PROT_WRITE	0x02	/* pages can be written */
#define	PROT_EXEC	0x04	/* pages can be executed */

/*
 * memcntl() selection attributes.  These must share the same flagspace as
 * the protection flags, as memcntl() expects them to be or'ed together.
 */
#define PROC_TEXT	(PROT_READ|PROT_EXEC)	/* program text pages */
#define PROC_DATA	(PROT_READ|PROT_WRITE)	/* application data pages */
#define SHARED		0x10			/* pages mapped MAP_SHARED */
#define PRIVATE		0x20			/* pages mapped MAP_PRIVATE */

/* mmap failure value */
#define MAP_FAILED  ((void *) -1)

/*
 * Flags contain sharing type and options.
 * Sharing types; choose one.
 */
#define	MAP_SHARED	0x0001	/* share changes */
#define	MAP_PRIVATE	0x0002	/* changes are private */
#define	MAP_COPY	0x0004	/* "copy" region at mmap time */

/*
 * Other flags
 */
#define MAP_VARIABLE	 0x0000	/* map anywhere (antonym for MAP_FIXED) */
#define	MAP_FIXED	 0x0010	/* map addr must be exactly as requested */
#define	MAP_RENAME	 0x0020	/* Sun: rename private pages to file */
#define	MAP_NORESERVE	 0x0040	/* Sun: don't reserve needed swap area */
#define	MAP_INHERIT	 0x0080	/* region is retained after exec */
#define	MAP_NOEXTEND	 0x0100	/* for MAP_FILE, don't change file size */
#define	MAP_HASSEMAPHORE 0x0200	/* region may contain semaphores */

/*
 * Mapping type; default is map from file.
 */
#define	MAP_FILE	 0x0000	    /* map from file (antonym for MAP_ANON) */
#define	MAP_ANON	 0x1000	    /* allocated from memory, swap space */
#define MAP_ANONYMOUS	 MAP_ANON   /* a synonym for MAP_ANON */

#ifdef __cplusplus
extern "C" {
#endif

extern void* __cdecl mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset);
extern int __cdecl munmap(void *start, size_t len);

#ifdef __cplusplus
}
#endif

#endif  /* _SYS_MMAN_H_ */
