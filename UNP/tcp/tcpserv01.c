#include "unp.h"


int 
main(int argc, char *argv[])
{
	struct sockaddr_in 	servaddr, cliaddr;
	int			connfd, listenfd;
	int 			pid;
	char			addrp[INET_ADDRSTRLEN];
	socklen_t		addrlen;
	
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));	
	
	Listen(listenfd, LISTENQ);
	

	
	printf("server begin listening\n");
	while (1){
		addrlen = sizeof(cliaddr);
		
		connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &addrlen);
		
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