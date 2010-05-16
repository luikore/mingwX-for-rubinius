#include <time.h>
#include <windows.h>

int nanosleep (const struct timespec *requested_time, struct timespec *remaining) {
	DWORD milliseconds = (requested_time->tv_sec * 1000) + (requested_time->tv_nsec / 1000 / 1000);
	if ((requested_time->tv_nsec < 0) || (requested_time->tv_nsec > (1000 * 1000))) {
		// __set_errno (EINVAL);
		return -1;
	}
	Sleep (milliseconds);
	remaining->tv_sec = 0;
	remaining->tv_nsec = 0;
	return 0;
}
