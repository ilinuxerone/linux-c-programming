#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define  MAXLINE	1024

 void sig_int(int signo)
	{
		printf("interrupt\n%%");
	}

int main(int argc, char **argv)
{
	char buf[MAXLINE];
	pid_t	pid;
	int 	status;
	
	if (signal(SIGINT, sig_int) == SIG_ERR) {
		perror("signal error");
		exit(-1);
	}
	
	printf("%%");
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;
			
			if ((pid = fork()) < 0) {
				perror("fork error");
				exit(-1);
			} else if (pid == 0) {
				execlp(buf, buf, NULL);
				exit(127);
			}
			
			if ((pid = waitpid(pid, &status, 0)) < 0) {
				perror("waitpid error");
				exit(-1);
			}
			printf("%%");
		}
	exit(0);
}	 
		                      
		                      
		                      
		                      
		                      
		                      
		                      
		                      
		                      
		                      
		                      
		                      
		                      
		                      
		                      
		                      
		                      
		                      
		                      
		                      
		                      
		                       
		 
		 
		 
		 
		 
		 
		 
		
