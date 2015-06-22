#include "apue.h"
#include <sys/wait.h>

static void sig_cld(int);

int main(int argc, char *argv[])
{
	pid_t  pid;
	
	if (SIG_ERR == signal(SIGCLD, sig_cld))
		perror("signal error");
	if ((pid = fork()) < 0) {
		perror("fork error");
	} else if (0 == pid){
		sleep(2);
		_exit(0);
	}
	pause();
	exit(0);
}

static void sig_cld(int signo)
{
	pid_t pid;
	int  status;
	
	printf("SIGCLD received\n");
	if (SIG_ERR == signal(SIGCLD, sig_cld))
		perror("signal error");
	if ((pid = wait(&status)) < 0)
		perror("wait error");
	printf("pid = %d\n", pid);
}