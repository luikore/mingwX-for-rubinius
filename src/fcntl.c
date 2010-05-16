#include <_mingw.h>
#include <fcntl.h>
#include <ioinfo.h>

/* __osfile flag values for DOS file handles */
#define FOPEN           0x01    /* file handle open */
#define FEOFLAG         0x02    /* end of file has been encountered */
#define FCRLF           0x04    /* CR-LF across read buffer (in text mode) */
#define FPIPE           0x08    /* file handle refers to a pipe */
#define FNOINHERIT      0x10    /* file handle opened _O_NOINHERIT */
#define FAPPEND         0x20    /* file handle opened O_APPEND */
#define FDEV            0x40    /* file handle refers to device */
#define FTEXT           0x80    /* file handle is in text mode */

#define LF          10   /* line feed */
#define CR          13   /* carriage return */
#define CTRLZ       26      /* ctrl-z means eof for text */

static int
osflags2mode (int osflags) {
	int fmode = 0;
	if (osflags & FOPEN)
		fmode |= O_RDWR;
	else if (osflags & FAPPEND)
		fmode |= O_APPEND;
	else if (osflags & FNOINHERIT)
		fmode |= O_NOINHERIT;
	else if (osflags & FTEXT)
		fmode |= O_TEXT;		 
	return fmode;
}

static int
mode2osflags (int fmode) {
	int osflags = 0;
	if (fmode & O_APPEND)
		osflags |= FAPPEND;
	else if (fmode & O_TEXT)
		osflags |= FTEXT;
	return osflags;
}

static int
do_fcntl (int fd, int cmd, void *arg) {
  switch (cmd) {
	case F_GETFL: 		/* Get file status flags and file access modes */
		return osflags2mode (_osfile (fd));
	case F_SETFL: 		/* Set file status flags */
		_osfile (fd) = mode2osflags ( (int) arg);
		return 0;
	default:
      return -1;
	}
}

/* Perform file control operations on FD.  */
int fcntl (int fd, int cmd, ...) {
  va_list ap;
  void *arg;

  va_start (ap, cmd);
  arg = va_arg (ap, void *);
  va_end (ap);

  if (fd < 0) {
      return -1;
  }
  return do_fcntl (fd, cmd, arg);
}

