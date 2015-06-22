#include "apue.h"

static void sig_int(int);

int main(int argc, char *argv[])
{
	sigset_t  newmask, oldmask, waitmask;
	
	pr_mask("main start...: ");
	
	if (SIG_ERR == signal(SIGINT, sig_int))
		err_sys("signal(SIGINT) error");
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);
	
	/*
	*block SIGINT and save current signal mask
	*/
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("sigprocmask error");
	
	/*critical region of codes*/
	pr_mask("in critical region: ");
	
	/*pause , allowing all signals except SIGUSR1*/
	if (sigsuspend(&waitmask) != -1)
		err_sys("sigsuspend error");
	
	pr_mask("after return from sigsuspend: ");
	
	/*reset signal mask which unblock SIGINT*/
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)	
		err_sys("sigprocmask error");
	
	/*and continue processing*/
	pr_mask("main exit...: ");
	
	exit(0);
}

static void sig_int(int signo)
{
	pr_mask("\nin sig_int: ");	
}
