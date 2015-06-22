#include "apue.h"

static void sig_alrm(int signo)
{
	/*nothing to do, just returning wakes up sigsuspend()*/
}

unsigned int sleep(unsigned int nsecs)
{
	struct  sigaction	act, oact;
	sigset_t 		newmask, oldmask, suspmask;
	unsigned  int  		unslept;
	
	/*set our handler, save previous information*/
	act.sa_handler = sig_alrm;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGALRM, &act, &oact);
	
	/*block SIGALRM and save curreng signal mask*/
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGALRM);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);
	
	alarm(nsecs);
	
	suspmask = oldmask;
	sigdelset(&suspmask, SIGALRM);                  /*make sure SIGALRM isn't blocked*/
	sigsuspend(&suspmask);				/*wait for any signal to be caught*/
	
	/*some signal has been caughr, SIGALRM is now blocked*/
	
	unslept = alarm(0);
	sigaction(SIGALRM, &oact, NULL);  		/*reset previous action*/
	
	/*reset signal mask, which unblocks SIGALRM*/
	sigprocmask(SIG_SETMASK, &oldmask, NULL);
	
	return (unslept);
}
		