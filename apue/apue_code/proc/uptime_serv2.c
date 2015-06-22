#include "apue.h"
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define QLEN  10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX  256
#endif

extern int initserver(int, struct sockaddr *, socklen_t, int);

void serve(int sockfd)
{
	int 	clfd, status;
	pid_t	pid;

	for (; ;){
		clfd = accept(sockfd, NULL, NULL);
		if (clfd < 0){
			syslog(LOG_ERR, "ruptime: accept error:%s", strerror(errno));
			exit(1);
		}
		if ((pid = fork()) < 0){
			syslog(LOG_ERR, "ruptimed: fork error:%s", strerror(errno));
			exit(1);
		}else if (0 == pid){            /*child*/
		/*
 		*The parent called daemonize ,so STDIN_FILENO STDOUT_FILENO, STDERR_FILENO are 
 		*already open to /dev/null. thus the call to close doesn't need to be protected by checks
 		*that clfd isn't already equal to one of these values.
 		*/ 
		if (dup2(clfd, STDOUT_FILENO) != STDOUT_FILENO ||
			dup2(clfd, STDERR_FILENO) != STDERR_FILENO){
				
		
	
