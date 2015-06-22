#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void sig_chld(int signo)
{
	pid_t pid;
	int stat;
	
	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0 )
		printf("child %d terminated\n");
	return ;
}