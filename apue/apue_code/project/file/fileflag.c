#include "apue.h"
#include <fcntl.h>

/*exercise 1
*对于指定的文件描述符打印文件标志
*/

int main(int argc, char *argv[])
{
	int   flag;
	
	if (2 != argc)
		err_quit("Usage: %s <descriptor#>", argv[0]);
	if ((flag = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
		err_quit("fcntl error fo fd %d", atoi(argv[1]));
	
	switch (flag & O_ACCMODE) {
	case O_RDONLY:
		printf("read only");
		break;
	case O_WRONLY:
		printf("write only");
		break;
	case O_RDWR:
		printf("read write");
		break;
	default:
		err_dump("unknown access mode");
	}
	
	if (flag & O_APPEND)
		printf(", append");
	if (flag & O_NONBLOCK)
		printf(", nonblock");
#if defined(O_SYNC)
	if (flag & O_SYNC)
		printf(", synchronous writes");
#endif

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC)
	if (flag & O_FSYNC)
		printf(", synchronous writes");
#endif

	putchar('\n');
	exit(0);
}
