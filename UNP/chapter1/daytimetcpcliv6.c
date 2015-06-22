#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>


#define  MAXLINE   1024


int main(int argc, char **argv)
{
	int sockfd;
	int n;
	int rval;
	struct sockaddr_in6 servaddr;
	char recvline[MAXLINE + 1];
	
	if (argc != 2) {
		fprintf(stderr, "usage: a.out <IPaddress>");
		exit(-1);
	}
	
	if ( (sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0 ) {
		perror("socket error");
		exit(-1);
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_port = htons(13);
	if ( (rval = inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr)) == 0) {
		perror("invalid ipaddress");
		exit(-1);
	} else if (rval == -1) {
		perror("inet_pton error");
		exit(-1);
	}
	
	while ( (n = read(sockfd, recvline, MAXLINE)) >  0 ) {
		recvline[n] = 0;
		if (fputs(recvline, stdout) == EOF) {
			perror("fputs error");
			exit(-1);
		}
	}
	if (n < 0) {
		perror("read error");
		exit(1);
	}
	
	exit(0);
}










