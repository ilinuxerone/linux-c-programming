#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define  MAXLINE   1024

void  dg_cli(FILE *fp, int sockfd, (const struct sockaddr *)pservaddr, socklen_t  servlen)
{
	int  	n;
	char    sendline[MAXLINE];
	char    recvline[MAXLINE];
	
	while (NULL != fgets(sendline, MAXLINE, fp)) {
		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		
		if (0 ==Readable_timeo(sockfd, 5)) {
			fprintf(stderr, "socket timeout\n");
		} else {
			n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
			recvline[n] = 0;
			fputs(recvline, stdout);
		}
	}
}