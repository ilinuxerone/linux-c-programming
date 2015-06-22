#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>

#define   LISTENQ  5
#define   MAXLINE  1024

int main(int argc, char **argv)
{
	int listenfd;
	int connfd;
	struct sockaddr_in  servaddr;
	struct sockaddr_in  cliaddr;
	char  buff[MAXLINE];
	time_t ticks;
	socklen_t len;
	
	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
		perror("socket error");
		exit(-1);
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
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
		
		if ( (connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len)) < 0) {
			perror("accept error");
			exit(-1);
		}
		printf("Connection from %s, port %d\n", inet_ntop(AF_INET, (struct sockaddr *)&cliaddr.sin_addr, buff, sizeof(buff)), 
			ntohs(cliaddr.sin_port));
		
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		write(connfd, buff, strlen(buff));
		
		close(connfd);
	}
	
}
