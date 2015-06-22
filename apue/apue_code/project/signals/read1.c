/*drawback:
*1:在第一次调用alarm和read之间有一个竞争条件。导致read可能永远阻塞
*2：如果系统调用是自动重启的，则当从SIGALRM信号处理程序返回时，read并不被中断
*/

#include "apue.h"

static void sig_alrm(int);

int main(int argc, char *argv[])
{
	int  n = 0;
	char line[MAXLINE];
	
	if (SIG_ERR == signal(SIGALRM, sig_alrm))
		err_sys("signal error");
	alarm(60);
	if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
		err_sys("read error");
	alarm(0);
	
	write(STDOUT_FILENO, line, n);
	
	exit(0);
}

static void sig_alrm(int signo)
{
	/*nothing to do, just return to interrupt the read*/	
}

