#include "apue.h"
#include <limits.h>

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

#define PATH_MAX_GUESS  1024

#define SUSV3  200112L

static long posix_version = 0;

char *path_alloc(char *sizep)
{
	char *ptr;
	int  size;
	
	if (0 == posix_version)
		posix_version = sysconf(_SC_VERSION);
	if (0 == pathmax){
		errno = 0;
		if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0){
			if (0 == errno)
				pathmax = PATH_MAX_GUESS;
			else
				err_sys("pathconf error for _PC_PATH_MAX");
		}
	}
	else {
		pathmax++;
	}
	if (posix_version < SUSV3)
		size = pathmax + 1;
	else 
		size = pathmax;
	
	if (NULL == (ptr = malloc(size)))
		err_sys("malloc error for pathname");
	if (NULL != sizep)
		*sizep = size;
		
	return (ptr);
}