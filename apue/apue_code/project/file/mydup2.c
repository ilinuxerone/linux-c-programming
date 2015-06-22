#include "apue.h"
#include <fcntl.h>

int mydup2(int fd, int fd2);

int main(int argc, char *argv)
{
	int  fd, fd2;
	
	if ((fd = open("test", O_RDWR | O_CREAT, FILE_MODE)) < 0)
		err_sys("open error");
	
	fd2 = mydup2(fd, 1);
	
	write(fd2, "hello world!\n", 13);	
	
}

int mydup2(int fd, int fd2)
{
	int    tmpfd;
	int    fdarray[fd2];
	int    i;
	
	/*test if fd is valid*/
	if ((tmpfd = dup(fd)) < 0)
		return (-1);
	else 
		close(tmpfd);
		
	/**/
	if (fd == fd2)
		return  (fd2);
	else {
		for (i = 0; i < fd2 + 1; i++)  {
			fdarray[i] = 0;
			if ((tmpfd = dup(fd)) < 0)
				 return (-1);
			else if (tmpfd == fd2)
				break;
			else 
				fdarray[tmpfd] = 1;
		}
	}
}