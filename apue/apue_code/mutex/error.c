#include "unpipc.h"
#include <stdarg.h>
#include <syslog.h>

int daemon_proc;  

static void err_doit(int, int, const char *, va_list);

/*
 *Nonfatal error related to a system call.
 * Print a message and return.
 */
void err_ret(const char *fmt, ...)
{
	va_list		ap;
	
	va_start(ap, fmt);
	err_doit(1, LOG_INFO, fmt, ap);
	va_end(ap);
	return;
}

/*
 * Fatal error related to a system call.
 *Print a message and terminate.
 * */
void err_sys(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(1);
}

/*
 *Fatal error related to a system call.
 *Print a message, dump core, and terminate.
 * */
void err_dump(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, LOG_ERR, fmt, ap);
	va_end(ap);
	abort();
	exit(1);            /*shouldn't get here*/
}

void err_msg(const char *fmt, ...)
{
	va_list		ap;
	
	va_start(ap, fmt);
	err_doit(0, LOG_INFO, fmt, ap);
	va_end(ap);
	return;
}

void err_quit(const char *fmt, ...)
{
	va_list		ap;
	
	va_start(ap, fmt);
	err_doit(0, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(1);
}

static void err_doit(int errnoflag, int level, const char *fmt, va_list ap)
{
	int	errno_save, n;
	char	buf[MAXLINE];
	
	errno_save = errno;
#ifdef HAVE_VSNPRINTF
	vsnprintf(buf, sizeof(buf), fmt, ap);
#else
	vsprintf(buf, fmt, ap);
#endif
	n = strlen(buf);
	if (errnoflag)
		snprintf(buf + n, sizeof(buf) - n, ": %s", strerror(errno_save));
	strcat(buf, "\n");
	if (daemon_proc) {
		syslog(level, buf);
	} else {
		fflush(stdout);
		fputs(buf, stderr);
		fflush(stderr);
	}
	return;
}

	











