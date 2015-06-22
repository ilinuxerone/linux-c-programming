#include "unp.h"

//extern sig_chld(int signo);            /////shouldn't be neglected!!!
int 
main(int argc, char *argv[])
{
	struct sockaddr_in 	servaddr, cliaddr;
	int			connfd, listenfd;
	int 			pid;
	char			addrp[INET_ADDRSTRLEN];
	socklen_t		addrlen;
	
	void sig_chld(int signo);            /////shouldn't be neglected!!!
	
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));	
	
	Listen(listenfd, LISTENQ);
	
	Signal(SIGCHLD, sig_chld);
	
	printf("server begin listening\n");
	while (1){
		addrlen = sizeof(cliaddr);
		
		if ((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &addrlen)) < 0){
			if (errno == EINTR)
				continue;
				fprintf(stderr, "accept error %s\n", strerror(errno));
				exit(-1);			
		}//Notice that we call accept and not our wrapper function Accept, 
		  //since we must handle the failure of the function ourselves.
		printf("accepted a connection from %s: port %d\n", inet_ntop(AF_INET,
				 &cliaddr.sin_addr, addrp, INET_ADDRSTRLEN), ntohs(cliaddr.sin_port));
		if ((pid = fork()) < 0){
			fprintf(stderr, "fork error\n");
			exit(EXIT_FAILURE);	
		} else if (pid == 0) {
			Close(listenfd);	
			str_echo(connfd);
			exit(EXIT_SUCCESS);
		} 
		Close(connfd);
	}
}