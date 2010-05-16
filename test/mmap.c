#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
	int fd = open("mmap.c", O_RDONLY);
	void* data;

	data = mmap(0, 1000, PROT_READ, MAP_PRIVATE, fd, 0);
	if (data == MAP_FAILED) {
		printf("map failed\n");
		return -1;
	} else {
		char* str = (char*) data;
		if (str[0] != '#' || str[3] != 'c') {
			printf("map not correct\n");
			return -1;
		}
	}
	munmap(data, 1000);

	printf("mmap test succeeded\n");
	return 0;
}
