#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int sockfd_to_family(int sockfd)
{
	struct sockaddr_storage ss;
	socklen_t  len;
	
	len = sizeof(ss);
	if (getsockname(sockfd, (struct sockaddr *)&ss, &len) < 0) {
		perror("getsockname error");
		exit(-1);
	}
	
	return (ss.ss_family);
}