pid_t  pid;
int listenfd;
int connfd;

listenfd = socket();

bind(listenfd,...);

listen(listenfd, LISTENQ);

for ( ; ; ) {
	connfd = accept();  /*probably blocks*/
	
	if ( (pid = fork()) == 0) {
		close(listenfd);  /*child closes listening socket*/
 		doit(connfd);  /*process the request*/
 		close(connfd); /*done with this client*/
 		exit(0);  /*child terminates*/
 	}
 	
 	close(connfd);      /*parent closes connected socket*/
}