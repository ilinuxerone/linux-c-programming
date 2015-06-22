#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <pthread.h>

#define MAXLINE   1024

static void	err_doit(int, int, const char *, va_list);


/*
 * Fatal error unrelated to a system call.
 * Print a message and terminate.
 */
void
err_quit(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(0, 0, fmt, ap);
	va_end(ap);
	exit(1);
}

/*
 * Print a message and return to caller.
 * Caller specifies "errnoflag".
 */
static void
err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
	char	buf[MAXLINE];

	vsnprintf(buf, MAXLINE, fmt, ap);
	if (errnoflag)
		vsnprintf(buf+strlen(buf), MAXLINE-strlen(buf), ": %s",
		  strerror(error));
	strcat(buf, "\n");
	fflush(stdout);		/* in case stdout and stderr are the same */
	fputs(buf, stderr);
	fflush(NULL);		/* flushes all stdio output streams */
}

void cleanup(void *arg)
{
	printf("clean up: %s\n", (char *)arg);
}


void *
thr_fn1(void *arg)
{
	printf("thread 1 start\n");
	pthread_cleanup_push(cleanup, "thread 1 first handler");
	pthread_cleanup_push(cleanup, "thread 1 second handler");
	printf("thread 1 push complete\n");
	if (arg)
		return((void *)1);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return((void *)1);
}

void *
thr_fn2(void *arg)
{
	printf("thread 2 start\n");
	pthread_cleanup_push(cleanup, "thread 2 first handler");
	pthread_cleanup_push(cleanup, "thread 2 second handler");
	printf("thread 2 push complete\n");
	if (arg)
		pthread_exit((void *)2);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void *)2);
}

int
main(void)
{
	int			err;
	pthread_t	tid1, tid2;
	void		*tret;

	err = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
	if (err != 0)
		err_quit("can't create thread 1: %s\n", strerror(err));
	err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);
	if (err != 0)
		err_quit("can't create thread 2: %s\n", strerror(err));
	err = pthread_join(tid1, &tret);
	if (err != 0)
		err_quit("can't join with thread 1: %s\n", strerror(err));
	printf("thread 1 exit code %d\n", (int)tret);
	err = pthread_join(tid2, &tret);
	if (err != 0)
		err_quit("can't join with thread 2: %s\n", strerror(err));
	printf("thread 2 exit code %d\n", (int)tret);
	exit(0);
}
