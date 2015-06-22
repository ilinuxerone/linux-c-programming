#include "apue.h"
#include <stdarg.h>
#include <errno.h>

static void  err_doit(int, int, const char *, va_list);


/*
*Fatal error related to a system call.
*print a message and terminate.
*/
void err_sys(const char *fmt, ...)
{
	va_list     argp;
	
	va_start(argp, fmt);
	err_doit(1, errno, fmt, argp);
	va_end(argp);
	exit(1);
}

/*
*Print a message and return to caller.
*caller specifies "errnoflag"
*/

static void err_doit(int errnoFlag, int error, const char *fmt, va_list argp)
{
		char  buf[MAXLINE];
		
		vsnprintf(buf, MAXLINE, fmt, argp);
		if (errnoFlag){
			snprintf(buf + strlen(buf), MAXLINE - strlen(buf), ": %s", strerror(error));
		}
		strcat(buf, "\n");             	/*???necessary ???? why??*/
		fflush(stdout);  		/*in case stdout and stderr are the same*/
		fputs(buf, stderr);
		fflush(NULL);			/*flushed all stdio output streams*/
}