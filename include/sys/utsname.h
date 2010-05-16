#ifndef _SYS_UTSNAME_H
#define _SYS_UTSNAME_H

struct utsname
{
  char sysname[20];
  char nodename[20];
  char release[20];
  char version[20];
  char machine[20];
};

static int uname (struct utsname * a) { return -1; }

#endif
