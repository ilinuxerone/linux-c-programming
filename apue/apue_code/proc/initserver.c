#include "apue.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen)
{
	int  	fd;
	int	err = 0;
	
	if ((fd = socket(addr->sa_family, type, 0)) < 0){
		return (-1);
	}
	if (bind(fd, addr, alen) < 0){
		err = errno;
		goto errout;
	}
	if (SOCK_STREAM == type || SOCK_SEQPACKET){
		if (listen(fd, qlen) < 0) {
			err = errno;
			goto errout;
		}
	}
		return (fd);
	
errout:
	close(fd);
	errno = err;
	return (-1);
}
