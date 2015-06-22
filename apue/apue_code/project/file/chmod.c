#include "apue.h"
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	struct  stat   buf;
	
	if (stat("foo", &buf) < 0)
		err_msg("stat error for foo");
	if (chmod("foo", (buf.st_mode & ~S_IRGRP) | S_ISGID) < 0)
		err_msg("chmod error for foo");
	
	if (chmod("bar", S_IRUSR | S_IWUSR | S_IXUSR) < 0)
		err_msg("chmod error for bar");
	
	exit(0);
}