#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define  BUFSIZE	1024

void  filecopy(int to, int from)
{
	int n = 0;
	char buf[BUFSIZE];
	
	while ( (n = read(from, buf, BUFSIZE)) > 0)
		write(to, buf, n);
}

int main(int argc, char *argv[])
{
	int  fd;
	
	if (1 == argc){
		filecopy(1, 0);
	}else {
		while (--argc > 0){
			if ( (fd = open(*++argv, O_RDONLY)) < 0){
				fprintf(stderr, "open error\n");
				return 1;
			} else {
				filecopy(1,fd);
				close(fd);
			}
		}
	}
	
	return (0);
}
	
	