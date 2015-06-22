#include "apue.h"

#define  BUFFSIZE     4096

int main(int argc, char *argv[])
{
	char buf[BUFFSIZE];
	int  n;
	
	/*
	while (NULL != fgets(buf, BUFFSIZE, stdin))
		if (EOF == fputs(buf, stdout))
			err_quit("fputs error");
			
	if (ferror(stdin))
		err_quit("fgets error");
	
	exit(0);
	*/
	
	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (n != write(STDOUT_FILENO, buf, n))
			err_sys("write error");
			
	if (n < 0)
		err_sys("read error");
	exit(0);
	
}