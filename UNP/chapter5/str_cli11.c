#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

#define MAXLINE  1024

void str_cli(FILE *fp, int sockfd)
{
	char  sendline[MAXLINE];
	char  recvline[MAXLINE];
	
	while (fgets(sendline, MAXLINE, fp) != NULL) {
		write(sockfd, sendline, 1);
		sleep(1);
		write(sockfd, sendline + 1, strlen(sendline) - 1);
		
		if (read(sockfd, recvline, MAXLINE) == 0) {
			perror("server terminated prematured");
			exit(-1);
		}
		fputs(recvline, stdout);
	}
}
	