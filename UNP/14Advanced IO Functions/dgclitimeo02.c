#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

#define  MAXLINE    1024

void  dg_cli(FILE *fp, int  sockfd,  (const struct sockaddr *)pservaddr, socklen_t  servlen)
{
	int 	n;
	char  sendline[MAXLINE];
	char  recvline[MAXLINE];
	struct timeval  tv;
	
	tv.tv_set = 5;
	tv.tv_uset = 0;
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
	
	while (NULL  != fgets(sendline, MAXLINE, stdin)) {
		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		
		n = recvfrom(sockfd, recvline, MAXLIE, 0, NULL, NULL);
		if (n < 0) {
			if (EWOULDBLOCK == errno) {
				fprintf(stderr, "socket timeout\n");
				continue;
			} else {
				fprintf(stderr, "recvfrom error\n");
				exit(-1);
			}
		}
		
		recvline[n] = 0;
		fputs(recvline, stdout);
	}
}