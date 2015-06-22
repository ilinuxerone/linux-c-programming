#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>


#ifndef MAXLINE
#define  MAXLINE   1024
#endif

#define  LISTENQ   5
#define  SERV_PORT  6000

int main(int argc, char **argv)
{
	int listenfd;
	int connfd;
	struct sockaddr_in  servaddr;
	struct sockaddr_in  cliaddr;
	socklen_t  len;
	char  buff[MAXLINE];
	pid_t childpid;
	void str_echo(int sockfd);
	
	
	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
		perror("socket error");
		exit(-1);
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	 
	if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		perror("bind error");
		exit(-1);
	}
	
	if (listen(listenfd, LISTENQ) < 0) {
		perror("listen error");
		exit(-1);
	}
	
	for ( ; ; ) {
		len = sizeof(cliaddr);
		if ( (connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len)) < 0 ) {
			perror("accept error");
			exit(-1);
		}
		
		if ( (childpid = fork()) < 0 ) {
			perror("fork error");
			exit(-1);
		} else if (childpid == 0) {
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		
		close(connfd);
	}
}		