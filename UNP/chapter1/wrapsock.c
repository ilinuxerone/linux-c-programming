#include "unp.h"

int Socket(int family, int type, int protocol)
{
	int sockfd;
	
	if ( (sockfd = socket(family, type, protocol)) < 0 )
		err_sys("socket error");
	return (sockfd);
}

