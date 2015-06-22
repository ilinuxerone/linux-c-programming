#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	extern  void handler();
	struct sigaction act;
	sigset_t  set;
	
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	
	/*
	*Define a handler for SIGUSR1 such than when 
	*entered both SIGUSR1 and SIGUSR2 are masked.
	*/
	
	act.sa_flags = 0;
	act.sa_mask = set;
	act.sa_handler = &handler;
	sigaction(SIGUSR1, &act, NULL);
	
	kill(getpid(), SIGUSR1);
	/**program will terminate with a sigusr2**/
	return EXIT_SUCCESS;
}

void handler(int signo)
{
	static  int first = 1;
	
	if (first) {
		first = 0;
		kill(getpid(), SIGUSR1);
		kill(getpid(), SIGUSR2);
	}
}