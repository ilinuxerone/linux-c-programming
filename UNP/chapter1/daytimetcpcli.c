#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

#define  MAXLINE      1024

int
main(int argc, char **argv)
{
	int sockfd;
	int n;
	int rval;
	char recvline[MAXLINE + 1];
	struct sockaddr_in   servaddr;
	
	if (argc != 2) {
		perror("usage: a.out <IPaddress>");
		exit(-1);
	}
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket error!");
		exit(-1);
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	if ((rval = inet_pton(AF_INET, argv[1], &servaddr.sin_addr)) == -1 ){
		perror("inet_pton error");
		exit(-1);
	} else if (rval == 0) {
		perror("invalid address!");
		exit(-1);
	}
	
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		perror("connect error");
		exit(-1);
	}
	
	while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;
		if (fputs(recvline, stdout) == EOF) {
			perror("fputs error");
			exit(-1);
		}
	}
	if (n < 0){
		perror("read error");
		exit(-1);
	}
	
	exit(0);
}















