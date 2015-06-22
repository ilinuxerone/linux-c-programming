#include "apue.h"
#include <syslog.h>
#include <sys/resource.h>
#include <fcntl.h>

void daemonize(const char *cmd)
{
	pid_t 		pid;
	int		i, fd0, fd1, fd2;
	struct rlimit   rlim;
	struct sigaction act;	

	/*
 	*clear file creation mask.
 	*/
	umask(0);

	/*
 	*get the maximum number of file descriptors.
	*/
	if (getrlimit(RLIMIT_NOFILE, &rlim) < 0)
		err_quit("%s: can't get file limit", cmd);
	if ((pid = fork()) < 0)
		err_quit("%s: can't fork", cmd);
	else if (pid > 0)
		exit(0);
	setsid();
	
	/*
 	* Ensure future opens won't allocate controlling TTYs
 	*/
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGHUP, &act, NULL) < 0)
		err_quit("%s: can't ignore SIGHUP");
	if ((pid = fork()) < 0)
		err_quit("%s: can't fork", cmd);
	else if (pid > 0)
		exit(0);

	/*
 	*Change the current work directory to the root so 
	*we won't prevent file system from being unmounted.
	*/
	if (chdir("/") < 0)
		err_quit("%s: can't change directory to /");

	/*
 	*Close all open file descriptors.
 	* */
	if (rlim.rlim_max == RLIM_INFINITY)
		rlim.rlim_max = 1024;
	for (i = 0; i < rlim.rlim_max; i++)
		close(i);
	
	/*
 	*Attach file descriptor 0, 1 and 2 to /dev/null.
 	*/
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	/**
 	*Initialize the log file.
 	*/
	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if (0 != fd0 || 1 != fd1 || 2 != fd2){
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
		exit(1);
	}	
}






