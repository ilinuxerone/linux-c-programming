
#ifndef  __APUE_H
#define  __APUE_H

#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define MAXLINE  4096

/*defaule file access permission*/
#define FILE_MODE         (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define	DIR_MODE	  (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

typedef void  Sigfunc(int);      	/*for signal handler*/

#if defined(SIG_IGN) && !defined(SIG_ERR)
#define SIG_ERR ((Sigfunc *)-1)
#endif

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

void err_ret(const char *, ...);
void err_sys(const char *, ...);
void err_msg(const char *, ...);
void err_quit(const char *, ...);
void err_dump(const char *, ...);
void err_exit(int, const char *, ...);
void pr_exit(int);


void	TELL_WAIT(void);		/* parent/child from {Sec race_conditions} */
void	TELL_PARENT(pid_t);
void	TELL_CHILD(pid_t);
void	WAIT_PARENT(void);
void	WAIT_CHILD(void);


#endif /*__APUE_H*/



