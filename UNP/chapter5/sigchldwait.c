#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void sig_chld(int signo)
{
	pid_t pid;
	int stat;
	
	pid = wait(&stat);
	printf("child %d terminated\n", pid);
	return;
}