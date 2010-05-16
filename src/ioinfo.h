/* adapted from perl/win32/win32.h & win32.c, which is GPL */

#ifndef _IOINFO_H
#define _IOINFO_H

#include <windows.h>
#include <io.h>

/* Control structure for lowio file handles */
typedef struct {
        intptr_t osfhnd;    /* underlying OS file HANDLE */
        char osfile;        /* attributes of file (e.g., open in text mode?) */
        char pipech;        /* one char buffer for handles opened on pipes */
        int lockinitflag;
        CRITICAL_SECTION lock;
    }   ioinfo;

/* Special, static ioinfo structure used only for more graceful handling
 * of a C file handle value of -1 (results from common errors at the stdio
 * level). */
__MINGW_IMPORT ioinfo __badioinfo;
/* Array of arrays of control structures for lowio files. */
__MINGW_IMPORT ioinfo * __pioinfo[];

/* Definition of IOINFO_L2E, the log base 2 of the number of elements in each
 * array of ioinfo structs. */
#define IOINFO_L2E          5
/* Definition of IOINFO_ARRAY_ELTS, the number of elements in ioinfo array */
#define IOINFO_ARRAY_ELTS   (1 << IOINFO_L2E)
/* Definition of IOINFO_ARRAYS, maximum number of supported ioinfo arrays. */
#define IOINFO_ARRAYS       64
#define MAX_DESCRIPTOR_COUNT        (IOINFO_ARRAYS * IOINFO_ARRAY_ELTS)
/* Access macros for getting at an ioinfo struct and its fields from a file handle */
#define _pioinfo(i) ( __pioinfo[(i) >> IOINFO_L2E] + ((i) & (IOINFO_ARRAY_ELTS - 1)) )
#define _osfhnd(i)  ( _pioinfo(i)->osfhnd )
#define _osfile(i)  ( _pioinfo(i)->osfile )
#define _pipech(i)  ( _pioinfo(i)->pipech )

#endif /* _IOINFO_H */
