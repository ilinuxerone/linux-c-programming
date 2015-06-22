#include <stdarg.h>
#include "apue.h"

static void err_doit(int, int, const char *, va_list);

/*
*Fatal error related to a system call.
*print a message and terminate.
*/
void err_sys(char *fmt, ...)
{
	va_list   ap;
	
	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	exit(1);
}


static void err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
	char  buf[MAXLINE];	
	
	vsnprintf(buf, MAXLINE, fmt, ap);
	if (errnoflag) {
		vsnprintf(buf + strlen(buf), MAXLINE - strlen(buf), ": %s\n", strerror(errno));
	}
	//strcat(buf, "\n");
	fflush(stdout);
	fputs(buf, stderr);
	fflush(NULL);
}

	
