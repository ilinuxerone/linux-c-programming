

#include "unp.h"

int
main(int argc, char *argv[])
{
	struct sockaddr_in  servaddr;
	int 	count;
	int 	sockfd[5];
	
	if (argc != 2){
		fprintf(stderr, " USAGE: %s <SERVER IP>\n", argv[0]);	
		exit(-1);
	}
	for (count = 1; count < 5; count++ ){
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	
	sockfd[count] = Socket(AF_INET, SOCK_STREAM, 0);
	
	connect(sockfd[count], (struct sockaddr *)&servaddr, sizeof(servaddr));
	printf("%d: connect to server\n", getpid());
	}
	str_cli(stdin, sockfd[1]);
	for (count = 1; count < 5; count++){
	Close(sockfd[count]);
	}
	exit(0);
}