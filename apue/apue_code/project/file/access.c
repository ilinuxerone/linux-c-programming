#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int ret;
	
	if (2 != argc)
		err_quit("Usage: %s <pathname>", argv[0]);
	if ((ret = access(argv[1], R_OK)) < 0)
		err_msg("access error for %s", argv[1]);
	else
		printf("read access ok\n");
	if (open(argv[1], O_RDONLY) < 0)
		err_msg("open error for %s", argv[1]);
	else 
		printf("open for read ok\n");
	exit(0);
}

