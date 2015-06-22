
#include "unp.h"

int
Socket(int family, int type, int protocol)
{
	int	err;
	int	n;
	
	if ((n = socket(family, type, protocol)) < 0){
		err = errno;
		fprintf(stderr, "socket error:%s\n" , strerror(err));
//		return (-1);
		exit(-1);	
	}
	return (n);                         //note:  return n.  not zero...!!!!///////////////
}

int
Bind(int sockfd, const struct sockaddr * myaddr, socklen_t addrlen)
{
	int	err;
	
	if (bind(sockfd, myaddr, addrlen) < 0){
		err = errno;
		fprintf(stderr, "bind failed:%s\n", strerror(err));
//		return (-1);
		exit(-1);	
	}
	return (0);
}


int
Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
	int	err;
	
	if (connect(sockfd, servaddr, addrlen) < 0){
		err = errno;
		fprintf(stderr, "connect error:%s\n", strerror(err));
//		return (-1);	
		exit(EXIT_FAILURE);
	}	
	return (0);
}

int
Connect_retry(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
	int	nsec;
	
	/*
     	* Try to connect with exponential backoff.
     	*/
     	for (nsec = 1; nsec <= MAXSLEEP; nsec <<= 1){
     		if (connect(sockfd, servaddr, addrlen) == 0){
     			/*
             		* Connection accepted.
             		*/
             		return (0);	
     		}	
     			/*
        	 	* Delay before trying again.
	         	*/
		if (nsec <= MAXSLEEP/2){
     			sleep(nsec);
     		}
     	}
    //    printf("connect time out!\n");
//	return (-1);
	exit(EXIT_FAILURE);
}
int

Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen )
{
	int	err;
	int	connfd;
	
	if ((connfd = accept(sockfd, cliaddr, addrlen)) < 0){
		err = errno;
		fprintf(stderr, "accepte error:%s\n", strerror(err));
//		return (-1);
		exit(EXIT_FAILURE);	
	}	
	return (connfd);             ///////////////////note return value////////////////////////
}

int
Listen(int sockfd, int backlog)
{
	int 	err;
	char 	*ptr;
	
	 /* can override 2nd argument with environment variable */
	if ((ptr = getenv("LISTENQ")) != NULL){
		backlog = atoi(ptr);	
	}	
	
	if (listen(sockfd, backlog) < 0){
		err = errno;
		fprintf(stderr, "listen error:%s\n", strerror(err));
//		return (-1);
	exit(EXIT_FAILURE);	
	}
	return (0);
}

int
Close(int fd)
{
	int 	err;
	if (close(fd) < 0){
		err = errno;
		fprintf(stderr, "close error %s\n", strerror(err));
		exit(EXIT_FAILURE);	
	}	
	return (0);
}

ssize_t
readn(int filedes, void *buff, size_t nbytes)
{
	size_t 		nleft;
	ssize_t		nread;
	char 		*ptr;
	
	ptr = buff;
	nleft = nbytes;
	while (nleft > 0){
		if ((nread = read(filedes, ptr, nleft)) < 0){
			if (errno == EINTR){
				nread = 0;	/* and call read() again */
			} else {
				return (-1);	
			}
		} else if (nread == 0){
			break;            /* EOF */
		}
		
		nleft -= nread;
		ptr  +=  nread;	
	}	
		return  (nbytes - nleft);			 /* return >= 0 */
}

 
ssize_t
writen(int filedes, const void *buff, size_t nbytes)
{
	size_t		nleft;
	ssize_t		nwritten;
	const   char	*ptr;
	
	nleft = nbytes;
	ptr = buff;
	while (nleft > 0){
		if ((nwritten = write(filedes, ptr, nleft)) <= 0){
			if (nwritten < 0 && errno == EINTR){
				nwritten = 0;	/* and call write() again */
			}else {
				return (-1);	/* error */	
			}	
		}	
	         nleft -= nwritten;
        	 ptr += nwritten;
	}
	return (nbytes);
}


void
str_echo(int sockfd)
{
	char 	        buf[MAXLINE];
	ssize_t 	nrecv;


again:
	while ((nrecv = read(sockfd, buf, MAXLINE)) > 0){
//		printf("recved ask\n");		
		writen(sockfd, buf, nrecv );	
	} 
	if (nrecv < 0 && errno == EINTR){
		goto  again;	
	}
	else if (nrecv < 0){
		fprintf(stderr, "read error: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);	
	}	
//	printf("echoed to client\n");	
}

/*
void
str_echo(int sockfd)
{
	char 	buf[MAXLINE];
	int	n;
	
	while ((n = read(sockfd, buf, MAXLINE)) > 0){
		printf("received %d bytes : %s\n", n, buf);
		write(sockfd, buf, n);	
		printf("echoed successfully\n");
	}		
	if (n < 0){
		fprintf(stderr, "read error : %s\n", strerror(errno));
		exit(-1);	
	}
}
*/

void
str_cli(FILE *fp, int sockfd)
{
	char	recvline[MAXLINE], sendline[MAXLINE];
	int	n;
	
	while (fgets(sendline, MAXLINE, fp) != NULL){
		writen(sockfd, sendline, strlen(sendline));	
		if ((n = readline(sockfd, recvline, MAXLINE)) == 0){
			fprintf(stderr, "server terminated prematurely\n");
			exit(EXIT_FAILURE);	
		}
//		recvline[n] = '\0';                 //if  use readline function, which include this step , you should do it again.
		fputs(recvline, stdout);
	}
}


ssize_t 
readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t	 n, rc;
	char	 c, *ptr;
	
	ptr = vptr;
	for (n = 1; n < maxlen; n++){
		if ((rc = my_read(fd, &c)) == 1){
			*ptr++ = c;
			if (c == '\n')
				break;	
		} else if (rc == 0){
			*ptr = 0;
			return (n - 1);	
		}  else 
			return (-1);
	}	
	
	*ptr = 0;
	return (n);
}
 

ssize_t 
readlinebuf(void **vptrptr)
{
	if (read_cnt){
		*vptrptr = read_ptr;	
	}	
	
	return (read_cnt);
}

static ssize_t
my_read(int fd, char *ptr)
{
	if (read_cnt <= 0){
	 again:
	 	if ((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0){
	 		if (errno == EINTR){
	 			goto 	again;	
	 		}	
	 		return 	(-1);
	 	} else if (read_cnt == 0){
	 		return (0);	
	 	} 
	 	read_ptr = read_buf;
	}	
	
	read_cnt--;
	*ptr = *read_ptr++;
	return (1);
}
/*
char 
*sock_ntop(const struct sockaddr *sockaddr, socklen_t addrlen)
{
	
}

*/

