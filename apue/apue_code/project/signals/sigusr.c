#include "apue.h"

static void sig_usr(int);

int main(int argc, char *argv[])
{
	if (SIG_ERR == (signal(SIGUSR1, sig_usr)))
		err_sys("can't catch SIGUSR1");
	if (SIG_ERR == (signal(SIGUSR2, sig_usr)))
		err_sys("can;t catch SIGUSR2");
	for (; ;)
		pause();
		
	return 0;
}

static void sig_usr(int signo)
{
	if (SIGUSR1 == signo)
		printf("received SIGUSR1\n");
	else if (SIGUSR2 == signo)
		printf("received SIGUSR2\n");
	else
		err_dump("received signal %d\n", signo);
}	
	