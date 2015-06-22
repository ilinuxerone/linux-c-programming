#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
#include <errno.h>

#define  MAXLINE   1024
#define  LISTENQ   5

int main(int argc, char **argv)
{
	int listenfd;
	int connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;
	
	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0))  < 0) {
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
	
	for (; ;) {
		if ( (connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) < 0) {
			perror("accept error");
			exit(-1);
		}
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		if (write(connfd, buff, strlen(buff)) < 0) {
			perror("write error");
			exit(-1);
		}
		
		close(connfd);
	}			
}

















