#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define  MAXLINE   1024
#define  SERV_PORT 6000

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	int rval;
	void str_cli(FILE *fp, int sockfd);
	
	if (argc != 2) {
		fprintf(stderr, "<usage:>%s  IPaddress\n", argv[0]);
		exit(-1);
	}
	
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket error");
		exit(-1);
	}
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	rval = inet_pton(AF_INET, argv[1], (struct sockaddr *)&servaddr.sin_addr);
	if (rval < 0) {
		perror("inet_pton error");
		exit(-1);
	} else if (rval == 0) {
		perror("Invalid Ip address");
		exit(-1);
	}
	
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		perror("connect error");
		exit(-1);
	}
	
	str_cli(stdin, sockfd);
	exit(0);
}