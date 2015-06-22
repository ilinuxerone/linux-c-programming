#include "apue.h"

static void sig_int(int);
volatile sig_atomic_t   quitflag;        /*set nonzero by signal handler*/

int main(int argc, char *argv[])
{
	sigset_t  newmask, oldmask, zeromask;
	
	if (SIG_ERR == signal(SIGINT, sig_int))
		err_sys("signal(SIGINT) error");
	if (SIG_ERR == signal(SIGQUIT, sig_int))
		err_sys("signal(SIGQUIT) error");
	
	sigemptyset(&newmask);
	sigemptyset(&zeromask);
	sigaddset(&newmask, SIGINT);

	/*
	*block SIGQUIT and save current signal mask
	*/
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("sigprocmask error");
		
	while (0 == quitflag)
		sigsuspend(&zeromask);
//	pause();
	
	/*
	*SIGQUIT has been caught and is now blocked,do whatever
	*/
	quitflag = 0;
	
	/*
	*reset signal mask which unblock SIGQUIT
	*/
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("sigprocmask error");
	
	exit(0);
}

static void sig_int(int signo)
{
	if (SIGINT == signo)
		pr_mask("\n in sig_int int: ");
	else if (SIGQUIT == signo){
		pr_mask("\n in sig_int quit: ");
		quitflag = 1;
	}
}
