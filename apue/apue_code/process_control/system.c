#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

int mysystem(const char *cmd)      /*version without signal handling*/
{
	pid_t   pid;
	int   status;
	
	if (NULL == cmd)
		return (1);
		
	if ( (pid = fork()) < 0 ){
		status = -1;
	} else if (0 == pid){
		execl("/bin/sh", "sh", "-c", cmd, (char *)0);
		_exit(127);
	}else {
		while (waitpid(pid, &status, 0) < 0){
			if (EINTR != errno){
				status = -1;
				break;
			}
		}
	}
	
	return (status);
}


	