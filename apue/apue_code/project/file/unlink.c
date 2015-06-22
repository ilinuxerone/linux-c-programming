#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (open("foo", O_RDWR) < 0)
		err_ret("open error");
	if (unlink("foo") < 0)
		err_ret("unlink error");
	printf("file unlinked\n");
	sleep(15);
	printf("done\n");
	exit(0);
}