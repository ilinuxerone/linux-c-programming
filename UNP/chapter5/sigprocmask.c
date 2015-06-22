#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char **argv)
{
	sigset_t  set;
	sigset_t  oset;
	sigset_t  pset;
	
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_BLOCK, &set, &oset);
	printf("Old set was %8.8ld.\n", oset);
	
	sigpending(&pset);
	printf("Pending set is %8.8ld.\n", pset);
	
	kill(getpid(), SIGINT);
	
	sigpending(&pset);
	printf("Pending set is %8.8ld.\n", pset);
	
	sigprocmask(SIG_UNBLOCK, &set, &oset);
	
	return (EXIT_SUCCESS);
}