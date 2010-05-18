#include <unistd.h>

char *ttyname(int fildes) {
	return "console";
}

int fork() {
	return -1;
}

int pipe(int filedes[]) {
	return -1;
}

