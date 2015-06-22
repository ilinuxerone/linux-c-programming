#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define MAXLINE  1024


void str_echo(int sockfd)
{
	ssize_t  n;
	char buff[MAXLINE];
	
again:
	while ( (n = read(sockfd, buff, MAXLINE)) > 0) 
		write(sockfd, buff, n);
	
	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0) {
		perror("read error");
		exit(-1);
	}
}
