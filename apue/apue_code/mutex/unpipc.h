#ifndef	__UNPIPC_H
#define	__UNPIPC_H

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <pthread.h>

#define MAXLINE		4096

#ifndef PATH_MAX
#define PATH_MAX	1024
#endif

#define MAX_PATH	1024

#define BUFFSIZE	4096

#define FILE_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define DIR_MODE  (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)


typedef void  Sigfunc(int);

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b)  ((a) > (b) ? (a) : (b))

void err_dump(const char *, ...);
void err_sys(const char *, ...);
void err_ret(const char *, ...);
void err_msg(const char *, ...);
void err_quit(const char *, ...);
void err_exit(int, const char *, ...);




#endif  /*UNPIPC_H*/


