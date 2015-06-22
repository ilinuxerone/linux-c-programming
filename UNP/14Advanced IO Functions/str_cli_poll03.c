#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <poll.h>
#include <errno.h>
#include <sys/devpoll.h>

#define  MAXLINE   1024

void  str_cli(FILE *fp,  int sockfd)
{
	int 	stdineof;
	char    buf[MAXLINE];
	int	n;
	int	wfd;
	struct  pollfd  pollfd[2];
	struct  dvpoll  dopoll;
	int	i;
	int	result;
	
	wfd = open("/dev/poll", O_RDWR, 0);
	
	pollfd[0].fd = fileno(fp);
	pollfd[0].events = POLLIN;
	pollfd[0].revents = 0;
	
	pollfd[1].fd = sockfd;
	pollfd[1].events = POLLIN;
	pollfd[1].revents = 0;
	
	write(wfd, pollfd, sizeof(struct pollfd) * 2);
	
	stdineof = 0;
	for (; ; ) {
		dopoll.dp_timeout = -1;
		dopoll.dp_nfds = 2;
		dopoll.dp_fds = pollfd;
		result = ioctl(wfd, DP_POLL, &dopoll);
		
		for (i = 0; i < result; i++) {
			if (dopoll.dp_fds[i].fd == sockfd) {
				if (0 == (n = read(sockfd, buf, MAXLINE))) {
					if (1 == stdineof)
						return ;
					else {
						fprintf(stderr, "read error\n");
						exit(-1);
					}
				}
				write(fileno(stdout), buf, n);
			} else {
				if (0 == (n = read(fileno(fp), buf, MAXLINE)) ){
					stdineof = 1;
					shutdown(sockfd, SHUT_WR);
					continue;
				}
				
				write(sockfd, buf, n);
			}
		}
	}
}


