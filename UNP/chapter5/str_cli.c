#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define MAXLINE  1024

void str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE];
	char recvline[MAXLINE];
	
	while (fgets(sendline, MAXLINE, fp) != NULL) {
		write(sockfd, sendline, strlen(sendline));
	
		if (read(sockfd, recvline, MAXLINE) == 0) {
			perror("str_cli server terminated prematurely");
			exit(-1);
		}
		
		fputs(recvline, stdout);
	}
}