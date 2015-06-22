

#include "unp.h"

int
main(int argc, char *argv[])
{
	int 		 sockfd;
	struct sockaddr_in servaddr;
	
	if (argc != 2){
		fprintf(stderr, "USAGE: %s serveraddr\n", argv[0]);
		exit(-1);	
	}
	
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);                             //need modify
	Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	printf("connect to server\n");	           
	str_cli(stdin, sockfd);
	Close(sockfd);
	exit(EXIT_SUCCESS);
}