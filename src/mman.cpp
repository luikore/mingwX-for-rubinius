#include <sys/mman.h>
#include <sys/stat.h>
#include <io.h>
#include <windows.h>
#include <memory.h>

#include <map>

typedef unsigned long long uint64_t;
typedef unsigned long uint32_t;

typedef std::map<void*, int> MallocMap;
static MallocMap malloc_map;

#ifdef DEBUG
#define die(x) printf(x);return MAP_FAILED
#else
#define die(x)  
#endif

extern "C" {

void* __cdecl mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset) {
	HANDLE hmap;
	void *temp;
	size_t len = 0;
	struct stat st;
	uint64_t o = offset;
	uint32_t l = o & 0xFFFFFFFF;
	uint32_t h = (o >> 32) & 0xFFFFFFFF;
	int win_prot = 0;

	// determine protection mode
#	define CASE break;case 
#	define wp(p) win_prot = PAGE_##p 
	switch (prot) {
		case PROT_READ:
			wp(READONLY);
		CASE PROT_READ | PROT_WRITE:
			wp(READWRITE);
		CASE PROT_READ | PROT_EXEC:
			wp(EXECUTE_READ);
		CASE PROT_READ | PROT_WRITE | PROT_EXEC:
			wp(EXECUTE_READWRITE);
		CASE PROT_EXEC:
			wp(EXECUTE);
		CASE PROT_NONE:
			wp(NOACCESS);
	}
	if (! win_prot) {
		die("mmap: flag not supported\n");
	}
#	undef CASE
#	undef wp

	// TODO flags

	// pure memory allocation
	// use VirtualAlloc for vista/win7 execution ability
	if (fd == -1) {
		void* ptr = VirtualAlloc(NULL, length, MEM_COMMIT, win_prot);
		if (ptr) {
			malloc_map.insert(MallocMap::value_type(ptr, 1));
			return ptr;
		} else {
			die("mmap: failed in virtual alloc");
		}
	}

	if (!fstat(fd, &st)) {
		len = st.st_size;
	} else {
		die("mmap: failed to get fstat\n");
	}

	if ((length + offset) > len) {
		length = (size_t)(len - offset);
	}


	hmap = CreateFileMapping((void*)_get_osfhandle(fd), 0, win_prot, 0, 0, 0);
	if (!hmap) {
		die("mmap: can not get file handle\n");
	}

	temp = MapViewOfFileEx(hmap, FILE_MAP_COPY, h, l, length, start);

	if (!CloseHandle(hmap)) {
		die("unable to close file mapping handle\n");
	}
	return temp ? temp : MAP_FAILED;
}

int __cdecl munmap(void *start, size_t len) {
	if (malloc_map.erase(start)) {
		return VirtualFree(start, len, MEM_RELEASE) ? 0 : -1;
	} else {
		return UnmapViewOfFile(start) ? 0 : -1;
	}
}

}
