#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

typedef  void Sigfunc(int);

Sigfunc *  Signal(int signo, Sigfunc  *func)
{
	struct  sigaction  act;
	struct  sigaction  oact;
	
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	
	if (SIGALRM == signo) {
#ifdef   SA_INTERRUPT
	act.sa_flags = |= SA_INTERRUPT;
#endif
} else {
#ifdef  SA_RESTART
	act.sa_flags |= SA_RESTART;
#endif 
	}
	if (sigaction(signo, &act, &oact) < 0) 
		return  (SIG_ERR);
	return (oact.sa_handler);
}


static  void  connect_alart(int);

int connect_timeo(int sockfd, const (struct sockaddr *)&saptr, socklen_t  salen, int  nsec)
{
	Sigfunc  *sigfunc;
	int	 n;
	
	sigfunc = Signal(SIGALRM, connect_alarm);
	if (alarm(nsec) != 0) {
		fprintf(stderr, "alarm was already set\n");
		exit(-1);
	}
	
	if ( (n = connect(sockfd, saptr, salen)) < 0 ) {
		close(sockfd);
		if (EINTR == errno)
			errno = ETIMEDOUT;
	}
	alarm(0);
	Signal(SIGALRM, sigfunc);
	
	return (n);
}

static  void  connect_alarm(int signo)
{
	return ;
}
	