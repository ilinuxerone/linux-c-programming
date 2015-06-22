#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

typedef   void   Sigfunc(int);
#define   MAXLINE    1024

Sigfunc *Signal(int signo,  Sigfunc *func)
{
	struct sigaction  act;
	struct sigaction  oact;
	
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (SIGALRM == signo) {
#ifdef	 SA_INTERRUPT   
	act.sa_flags |= SA_INTERRUPT;
#endif 
	} else  {
#ifdef     SA_RESTART
	act.sa_flags |= SA_RESTART;
#endif 
	}
	if (sigaction(signo, &act, &oact) < 0)
		return (SIG_ERR);
		
	return (oact.sa_handler);
}
	

static  void sig_alrm(int signo);

void dg_cli(FILE  *fp, int sockfd,  const (struct sockaddr *)pservaddr, socklen_t  servlen)
{
	int 	n;
	char    sendline[MAXLINE];
	char    recvlien[MAXLINE + 1];
	
	Signal(SIGALRM, sig_alrm);
	
	while (fgets(sendline, MAXLINE, stdin) != NULL) {
		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		
		alarm(5);
		if ( (n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL))  < 0) {
			if (EINTR == errno)
				fprintf(stderr, "socket timeout\n");
			else {
				fprintf(stderr, "recvfrom error\n");
				exit(-1);
			}
		} else {
			alarm(0);
			recvline[n] = 0;
			fputs(recvline, stdout);
		}
	}
}

static   void  sig_alrm(int signo)
{
	return ;
}


 
			