#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE   4096

void mycp(int to, int from)
{
	int  n;
	char buf[BUFFSIZE];
	
	while ((n = read(from, buf, BUFFSIZE)) > 0)
		if (n != write(to, buf, n))
			err_sys("write error");
	if (n < 0)
		err_sys("read error");
}

int main(int argc, char *argv[])
{
	int   fd;
	
	if (1 == argc)
		mycp(STDOUT_FILENO, STDIN_FILENO);
	else {
		while (--argc > 0){
			if ((fd = open(*++argv, O_RDONLY)) < 0)
				err_sys("open error");
			else {
				mycp(STDOUT_FILENO, fd);
				close(fd);
			}
		}
	}
	exit(0);
}
