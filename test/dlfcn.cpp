/*
 * dlfcn-win32
 * Copyright (c) 2007 Ramiro Polla
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdio.h>
#include "dlfcn.h"

/* This is what this test does:
 * - Open library with RTLD_GLOBAL
 * - Get global object
 * - Get symbol from library through library object <- works
 * - Run function if it worked
 * - Get symbol from library through global object  <- works
 * - Run function if it worked
 * - Close library
 * - Open library with RTLD_LOCAL
 * - Get symbol from library through library object <- works
 * - Run function if it worked
 * - Get symbol from library through global object  <- fails
 * - Run function if it worked
 * - Open library again (without closing it first) with RTLD_GLOBAL
 * - Get symbol from library through global object  <- works
 * - Close library
 * - Close global object
 */

typedef int (*Func)( void );

int main()
{
    void *global;
    void *library;
    char *error;
    int (*function)( void );
    int ret;

#define assert(a, msg) \
	if (!(a)) {\
		error = dlerror( );\
		printf(msg, error ? error : "");\
		return -1;\
	}

    library = dlopen( "dll.dll", RTLD_GLOBAL );
	assert (library, "Could not open library: %s\n");

    global = dlopen( 0, RTLD_GLOBAL );
	assert (global, "Could not open global handle: %s\n");

    function = (Func)dlsym( library, "function" );
	assert (function, "Could not get symbol from library handle: %s\n");
    function( );

    function = (Func)dlsym( global, "function" );
	assert (function, "Could not get symbol from global handle: %s\n");
    function( );

    ret = dlclose( library );
	assert (!ret, "Could not close library: %s\n");

    library = dlopen( "dll.dll", RTLD_LOCAL );
	assert (library, "Could not open library locallly: %s\n");

    function = (Func)dlsym( library, "function" );
	assert (function, "Could not get symbol from library handle: %s\n");
    function( );

    function = (Func)dlsym( global, "function" );
	if (function) {
		printf("Unexpected: got symbol from global handle: %p\n", function);
		return -1;
	}

    ret = dlclose( library );
	assert (!ret, "Could not close library: %s\n");

    ret = dlclose( global );
	assert (!ret, "Could not close global handle: %s\n");

	printf("dlfcn test succeeded.\n");
    return 0;
}
