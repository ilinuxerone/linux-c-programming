/*[zhihong@localhost project]$ ./signals/sigsetjmp_mask &
[1] 8854
[zhihong@localhost project]$ main start...
kill -USR1 8854
[zhihong@localhost project]$ in sig_usr:SIGUSR1 
in sig_alrm:SIGUSR1 SIGALRM 
finishing sig_usr1:SIGUSR1 
main ended...

[1]+  Done                    ./signals/sigsetjmp_mask
为什么不能直接退出呢？？？
*/

#include "apue.h"
#include <setjmp.h>
#include <time.h>

static sigjmp_buf   		jmpbuf;
static volatile sig_atomic_t 	canjump;
static 	void			sig_alrm(int), sig_usr1(int);

int main(int argc, char *argv[])
{
	
	if (SIG_ERR == signal(SIGUSR1, sig_usr1))
		err_sys("signal(SIGUSR1) error");
	if (SIG_ERR == signal(SIGALRM, sig_alrm))
		err_sys("signal(SIGALRM) error");
	
	printf("main start...\n");
	if (sigsetjmp(jmpbuf, 1)){
		pr_mask("main ended...");
		exit(0);	
	}
	
	canjump = 1;
	
//	for ( ; ; )
		pause();
		
//	exit(0);      /*won't execute here*/
}

static void sig_usr1(int signo)
{
	time_t   starttime;
	
	if (canjump == 0)
		return;
	pr_mask("in sig_usr: ");
	alarm(3);
	starttime = time(NULL);
	for (; ;)
		if (time(NULL) > starttime + 5)
			break;
		
	pr_mask("finishing sig_usr1:");
	canjump = 0;
	siglongjmp(jmpbuf, 1);	
}

static void sig_alrm(int signo)
{
	pr_mask("in sig_alrm:");
}
