#include <stdio.h>
#include <stdlib.h>

#define  MAXLINE   1024

void  str_echo(int sockfd)
{
	char   line[MAXLINE];
	FILE  *fpin;
	FILE  *fpout;
	
	fpin = fdopen(sockfd, "r");
	fpout = fdopen(sockfd, "w");
	
	while (NULL != fgets(line, MAXLINE, fpin)) {
		fputs(line, fpout);
	}	
}

