#include "apue.h"

void pr_mask(const char *str)
{
	int   errno_save;     
	sigset_t  sigset;
	
 	errno_save = errno;    /*we can be called by signal handlers*/
	if (sigprocmask(0, NULL, &sigset) < 0)
		err_sys("sigprocmask error");
	
	printf("%s", str);
	if (sigismember(&sigset, SIGINT)) 
		printf("SIGINT ");
	if (sigismember(&sigset, SIGQUIT))
		printf("SIGQUIT");
	if (sigismember(&sigset, SIGUSR1))
		printf("SIGUSR1 ");
	if (sigismember(&sigset, SIGALRM))
		printf("SIGALRM ");
	printf("\n");
	
	errno = errno_save;           /*why????*/
}