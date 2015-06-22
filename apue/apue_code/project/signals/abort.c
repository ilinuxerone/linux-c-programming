#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void abort(void)
{
	struct sigaction   act;
	sigset_t            mask;
	
	/*
	*caller can't ignore SIGABRT, if so reset to default.
	*/
	if (sigaction(SIGABRT, NULL, &act) < 0)
		err_sys("sigaction error");
	if (SIG_IGN == act.sa_handler){
		act.sa_handler = SIG_DFL;
		sigaction(SIGABRT, &act, NULL);
	}
	if (SIG_DFL == act.sa_handler)
		fflush(NULL);
		
	/*
	*caller can't block SIGABRT, make sure it's unblocked.
	*/
	sigfillset(&mask);
	sigdelset(&mask, SIGABRT);
	if (sigprocmask(SIG_SETMASK, &mask, NULL) < 0)
		err_sys("sigprocmask error");
	kill(getpid(), SIGABRT);
	
	/*
	*if we are here, process caught SIGABRT and returned.
	*/
	ffush(NULL);
	act.sa_handler = SIG_DFL;
	if (sigaction(SIGABRT, &act, NULL) < 0)
		err_sys("sigaction error");
	if (sigprocmask(SIG_SETMASK, &mask, NULL) < 0)
		err_sys("sigprocmask error");
	kill(getpid(), SIGABRT);
	exit(1);    			/*this should never be executed...*/
}