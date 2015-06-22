#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

typedef  void    Sigfunc(int);


Sigfunc * Signal(int signo, Sigfunc *func)
{
	struct sigaction act;
	struct sigaction oact;
	
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (signo == SIGALRM) {
#ifdef  SA_INTERRUPT
	act.sa_flags |= SA_INTERRUPT;
#endif
	} else {
#ifdef  SA_RESTART
	act.sa_flags |= SA_RESTART;
#endif
	}
	if (sigaction(signo, &act, &oact) < 0) {
		return (SIG_ERR);
	}
	return (oact.sa_handler);
}
