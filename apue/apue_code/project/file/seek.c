#include "apue.h"
#include <fcntl.h>


/*exercise1
*test if standard input can be set an offset
*/
/*
int main(int argc, char *argv[])
{
	if (-1 == lseek(STDIN_FILENO, 0, SEEK_CUR))
		printf("can't seek\n");
	else 
		printf("seek ok\n");
	exit(0);
		
}
*/

//exercise 2:
unsigned long ftellsize(const char *path)
{
	int 	fd;
	
	if ((fd = open(path, O_RDONLY)) < 0)
		err_sys("open error");
	
	return (lseek(fd, 0, SEEK_END));
}



int main(int argc, char *argv[])
{
	/*
	if (argc != 2) 
		err_quit("Usage: %s: filename", argv[0]);
		
	printf("length of %s is: %d\n", argv[1], ftellsize(argv[1]));
	exit(0);
	*/
	
	
	int  i;
	
	if (1 == argc)
		err_quit("Usage: %s: filename ...", argv[0]);
		
	for (i = 1; i < argc; i++){
		printf("Length of %s is: %d\n", argv[i], ftellsize(argv[i]));
	}
	exit(0);		
}



/*exercise 3:
*create a file with a hole.
*/
/*
char  buf1[] = "abcdefghij";
char  buf2[] = "ABCDEFGHIJ";

int main(int argc, char *argv[])
{
	int   fd;
	
	if (-1 == (fd = creat("file.hole", FILE_MODE)))
		err_sys("creat error");
	
	if (10 != write(fd, buf1, 10))
		err_sys("write error");
		
	if (-1 == lseek(fd, 16384, SEEK_SET))
		err_sys("lseek error");
	
	if (10 != write(fd, buf2, 10))
		err_sys("write error");
		
	printf("Length of file.hole is :%d\n", ftellsize("file.hole"));
}
*/