/*drawback:
*1:�ڵ�һ�ε���alarm��read֮����һ����������������read������Զ����
*2�����ϵͳ�������Զ������ģ��򵱴�SIGALRM�źŴ�����򷵻�ʱ��read�������ж�
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

