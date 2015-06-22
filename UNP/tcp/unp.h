
#ifndef 	unp_h
#define		unp_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <sys/resource.h>


#ifndef		LISTENQ
#define		LISTENQ  	1024
#endif

#ifndef		MAXLINE
#define 	MAXLINE		4096
#endif

#ifndef		INET_ADDRSTRLEN
#define		INET_ADDRSTRLEN		16
#endif

#ifndef		INET6_ADDRSTRLEN
#define		INET6_ADDRSTRLEN	46
#endif

#define		MAXSLEEP	128
#define		SERV_PORT	7000

typedef		void  	Sigfunc(int);

static	int	read_cnt;
static	char	*read_ptr;
static 	char	read_buf[MAXLINE];
static  ssize_t my_read(int fd, char *ptr);

ssize_t	readline(int fd, void *vptr, size_t maxlen);
ssize_t	readlinebuf(void **vptrptr);

int Socket(int family, int type, int protocol);
int Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
int Accept(int sockfd,struct sockaddr *cliaddr, socklen_t *addrlen);
int Connect_try(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
int Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Close(int fd);
ssize_t writen(int fd, const void *buff, size_t nbytes);
ssize_t readn(int fd, void *buff, size_t nbytes);
void str_echo(int sockfd);
void str_cli(FILE *fp, int sockfd);






#endif
