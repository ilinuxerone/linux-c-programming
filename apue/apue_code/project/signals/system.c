#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

int system(const char *cmd)
{
	pid_t 			pid;
	int			status;
	struct sigaction	ignore, saveint, savequit;
	sigset_t		chldmask, savemask;
	
	if (NULL == cmd)
		return (1);              /*always a command processor with unix*/
	
	ignore.sa_handler = SIG_IGN;             /*ignore SIGQUIT and SIGINT*/
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	if (sigaction(SIGINT, &ignore, &saveint) < 0)
		return (-1);
	if (sigaction(SIGQUIT, &ignore, &savequit) < 0)
		return (-1);
	sigemptyset(&chldmask);                /*now block child*/
	sigaddset(&chldmask, SIGCHLD);
	if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0)
		return (-1);
	
	if ((pid = fork()) < 0){
		status = -1; 			/*probably out of processed*/
	} else if (0 == pid){
		/*restore previous signal actions and reset signal mask*/
		sigaction(SIGINT, &saveint, NULL);
		sigaction(SIGQUIT, &savequit, NULL);
		sigprocmask(SIG_SETMASK, &savemask, NULL);
		
		execl("/bin/sh", "sh", "-c", cmd, (char *)0);
		_exit(127);          /*exec error*/
	}else {
		while (waitpid(pid, &status, 0) < 0)
			if (errno != EINTR){
				status = -1;
				break;
			}
	}
	
	/*restore previous signal actions and reset signal mask*/
	if (sigaction(SIGINT, &saveint, NULL) < 0)
		return (-1);
	if (sigaction(SIGQUIT, &savequit, NULL) < 0)
		return (-1);
	if (sigprocmask(SIG_SETMASK, &savemask, NULL) < 0)
		return (-1);
	
	return (status);
}
