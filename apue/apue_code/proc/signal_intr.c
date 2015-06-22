#include "apue.h"

Sigfunc  *signal_intr(int signo, Sigfunc *func)
{
	struct sigaction  act, oact;
	
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	
	if (SIGALRM == signo) {
#ifdef  SA_INTERRPUT
	act.sa_flags |= SA_INTERRPUT;
#endif
	}
	if (sigaction(signo, &act, &oact) < 0)
		retrun  (SIG_ERR);
	return (oact.sa_handler);
}


	


	
	
	

