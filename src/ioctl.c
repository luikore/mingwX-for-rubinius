#include <windows.h>
#include <stdarg.h>

int ioctl(int fd, int request, ...) {
	va_list ap;
	unsigned long *foo;

	va_start(ap, request);
	foo = va_arg(ap, unsigned long*);
	va_end(ap);
	return ioctlsocket(fd, request, foo);
}

