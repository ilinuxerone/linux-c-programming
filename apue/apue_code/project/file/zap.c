#include "apue.h"
#include <utime.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	struct  stat  buf;
	struct  utimbuf  timebuf;
	int  i, fd;
	
	for (i = 1; i < argc; i++){
		if (stat(argv[i], &buf) < 0){
			err_msg("%s: fstat error", argv[i]);
			continue;
		}
		if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0){
			err_ret("%s: open error", argv[i]);
			continue;
		}
		close(fd);
		timebuf.actime = buf.st_atime;
		timebuf.modtime = buf.st_mtime;
		if (utime(argv[i], &timebuf) < 0){
			err_ret("%s: utime error", argv[i]);
			continue;
		}
	}
}
		