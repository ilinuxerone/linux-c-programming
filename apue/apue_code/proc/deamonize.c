#include "apue.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

void daemonize(const char *cmd)
{
	pid_t   pid;
	struct  rlimit  rlim;
	int	i, fd0, fd1, fd2;
	struct sigaction  act;
	
	/*
	*clear file creation mask
	*/
	umask(0);

	/*fork()*/
	if ((pid = fork()) < 0){
		err_quit("%s:fork error", cmd);
	}else if (1 == pid){
		exit(0);
	}
	
	/Becoming a session leader to lose controlling tty/
	setsid();

	/*
	*Ensure future opens won't allocate controlling ttys
	*/
	act.sa_handler = SIG_IGN;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGHUP, &act, NULL) < 0)
		err_quit("%s can't ignore SIGHUP", cmd);	
	if ((pid = fork()) < 0){
		err_quit("%s can't fork ", cmd);	
	} else if (pid > 0){
		exit(0);
	}	

	
	/*Changing the current work directory to the root so we won't prevent
	*file system from being unmounted.
	*/
	if (chdir("/") < 0)
		err_quit("%s: can't change directory to /", cmd);

	/*
	*close all open file descriptor
	*/
	if (getrlimit(RLIMIT_NOFILE, &rlim) < 0)	
		err_quit("%s: getrlimit error", cmd);
	for (i = 0; i < rlim.rlim_max)
		close(i);
	
	/*
	*attach file descriptor 0, 1,2 to /dev/null
	*/
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	/*
	*Initialize the log file
	*/
	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if (0 != fd0 || 1 != fd1 || 2 != fd2){
		syslog(LOG_ERR, "unexpected file descriptor %d %d %d", 
			fd0, fd1, fd2);
	exit(1);
}	
