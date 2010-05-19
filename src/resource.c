#include <sys/resource.h>
#include <errno.h>
#include <windows.h>

int getrlimit (int rltype, struct rlimit *rlimitp) {
	if (rltype < 0 || rltype >= RLIM_NLIMITS || rlimitp == NULL) {
		errno = EINVAL;
		return -1;
	}

	if (rltype == RLIMIT_STACK) {
		// TODO is it right ?
		MEMORY_BASIC_INFORMATION mi;
		if (! VirtualQuery(&mi, &mi, sizeof(mi))) {
			errno = EINVAL;
			return -1;
		}
		rlimitp->rlim_cur = (char*)mi.BaseAddress - (char*)mi.AllocationBase;
		// TODO actual stack size
		rlimitp->rlim_max = (6L * 1000L);
		rlimitp->rlim_max *= (1000L * 1000L);
	} else if (rltype == RLIMIT_NOFILE) {
		// TODO actual file limit
		rlimitp->rlim_cur = 5;
		rlimitp->rlim_max = 10;
	} else {
		rlimitp->rlim_cur = RLIM_INFINITY;
		rlimitp->rlim_max = RLIM_INFINITY;
	}

	return 0;
}
