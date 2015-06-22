/*����sigprocmask��������κ�δ���ģ������������źţ������䷵��ǰ
*���ٻὫ����һ���źŴ��ݸ��ý���
*/

#include "apue.h"

static sig_quit(int);

int main(int argc, char *argv[])
{
	sigset_t   newset, maskset, oldset;
	
	if (SIG_ERR == signal(SIGQUIT, sig_quit))
		err_sys("can't catch SIGQUIT");
	
	sigemptyset(&newset);
	sigaddset(&newset, SIGQUIT);
	if (sigprocmask(SIG_BLOCK, &newset, &oldset) < 0)
		err_sys("sigprocmask error");
	
	sleep(5);
	
	if (sigpending(&maskset) < 0)
		err_sys("sigpending error");
	if (sigismember(&maskset, SIGQUIT))
		printf("SIGQUIT pending\n");
		
	if (sigprocmask(SIG_SETMASK, &oldset, NULL) < 0)
		err_sys("sigprocmask error");
	printf("SIGQUIT unblocked\n");
	
	sleep(5);
	exit(0);
}

static sig_quit(int signo)
{
	printf("caught SIGQUIT\n");
	if (SIG_ERR == signal(SIGQUIT, SIG_DFL))
		err_sys("can't reset SIGQUIT");	
}