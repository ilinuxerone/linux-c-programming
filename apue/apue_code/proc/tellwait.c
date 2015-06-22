#include "apue.h"

static volatile sig_atomic_t  		sigflag;               /*set nonzero by sig handler*/
static sigset_t  newmask,  oldmask, zeromask;

static void sig_usr(int signo)
{
	pr_mask("\n in sig_usr: ");
	sigflag = 1;
}

void TELLL_WAIT(void)
{
	if (SIG_ERR == signal(SIGUSR1, sig_usr))
		err_sys("signal(SIGUSR1) error");
	if (SIG_ERR == signal(SIGUSR2, sig_usr))
		err_sys("signal(SIGUSR2) error");
	sigemptyset(&newmask);
	sigemptyset(&zeromask);
	sigaddset(&newmask, SIGUSR1);
	sigaddset(&newmask, SIGUSR2);
	
	/*
	*block  SIGUSR1 and SIGUSR2 , and save current signal mask.
	*/
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("sigprocmask error");
}

void TELL_PARENT(pid_t pid)
{
	kill(pid, SIGUSR2);             /*tell parent we're done*/
}

void WAIT_PARENT(void)
{
	while (0 == sigflag)
		sigsuspend(&zeromask);           /*and wait for parent*/
	sigflag = 0;
	
	/*
	*reset signal mask to original value.
	*/
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("sigprocmask error");
}

void TELL_CHILD(pid_t pid)
{
	kill(pid, SIGUSR1);     /*tell child we are done*/
}

void WAIT_CHILD(void)
{
	while (0 == sigflag)
 		sigsuspend(&zeromask);      /*wait for child*/     
	sigflag = 0;
	
	/*
	*reset signal mask to original value.
	*/
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("sigprocmask error");
}

