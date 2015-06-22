#include "apue.h"
#include <limits.h>
#include <errno.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

#define OPEN_MAX_GUESS 256

long open_max(void)
{
	if (0 == openmax){
		errno = 0;
		if ((openmax = sysconf(_SC_OPEN_MAX)) < 0){
			if (0 == errno)
				openmax = OPEN_MAX_GUESS;
			else
				err_sys("sysconf error for _SC_OPEN_MAX");
		}
	}
	return (openmax);
}