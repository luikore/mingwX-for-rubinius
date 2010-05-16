#include <sys/time.h>

void timeradd(struct timeval*a, struct timeval *b, struct timeval *res) {
	res->tv_sec = a->tv_sec + b->tv_sec;
	res->tv_usec = a->tv_usec + b->tv_usec;
	if (res->tv_usec > (1000 * 1000)) {
		res->tv_sec += 1;
		res->tv_usec -= (1000 * 1000);
	}
}

void timersub(struct timeval*a, struct timeval *b, struct timeval *res) {
	/* FIXME res = 0 if b > a ? */
	if (a->tv_usec >= b->tv_usec) {
		res->tv_sec = a->tv_sec - b->tv_sec;
		res->tv_usec = a->tv_usec - b->tv_usec;
	} else {
		res->tv_sec = a->tv_sec - b->tv_sec - 1;
		res->tv_usec = (1000 * 1000) + a->tv_usec - b->tv_usec;
	}
}

