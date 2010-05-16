/* Copyright (C) 1991,92,95,96,97,98,99,2001 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

/*
 *	POSIX Standard: 9.2.2 User Database Access	<pwd.h>
 */
#ifndef	_PWD_H
#define	_PWD_H	1

#include <stddef.h>

/* The passwd structure.  */
struct passwd {
  char *pw_name;		/* Username.  */
  char *pw_passwd;		/* Password.  */
  unsigned pw_uid;		/* User ID.  */ /* TODO 64bit extend? */
  unsigned pw_gid;		/* Group ID.  */ /* TODO 64bit extend? */
  char *pw_gecos;		/* Real name.  */
  char *pw_dir;			/* Home directory.  */
  char *pw_shell;		/* Shell program.  */
};

#ifdef __cplusplus
extern "C" {
#endif

extern void __cdecl endpwent(void);
extern struct passwd* __cdecl getpwnam(const char *name);
extern char* __cdecl getlogin();
extern struct passwd* __cdecl getpwuid(int user_id);

#ifdef __cplusplus
}
#endif

#endif /* pwd.h  */
