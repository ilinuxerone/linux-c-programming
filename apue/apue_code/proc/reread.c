#include "apue.h"
#include <pthread.h>
#include <sys/log.h>

sigset_t	mask;

extern int already_running(void);

void reread(void)
{
	/*...*/
}

void thr_fn(void *arg)
{




}


int main(int argc, char *argv[])
{
	int 		err;
	pthread_t	tid;
	char		*cmd;
	struct 	sigaction act;

	if (NULL == (cmd = strrchr(argv[0], '/')))
		cmd = argv[0];
	else 
		cmd++;

	/*
	 *Become a daemon.
	*/
	daemonize(cmd);

	/*
 	*Make sure only one copy of the daemon is running.
 	*/
	if (already_running()){
		syslog(LOG_ERR, "daemon already running");
		exit(1);
	}
	
	/*
	* 
 	*/


