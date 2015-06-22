#include "apue.h"
#include <fcntl.h>

#define  BUFFSIZE   4096

/*version1*/
void mycp1(const char *src, char *dst)
{
	FILE  *fsrc,  *fdst;
	int 	c;
	char  buf[BUFFSIZE];
	
	if (NULL == (fsrc = fopen(src, "r")))
		err_quit("fopen error");
	if (NULL == (fdst = fopen(dst, "w+")))
		err_quit("fopen error");
	
	while (EOF != (c = fgetc(fsrc)))
		if (EOF == fputc(c, fdst))
			err_quit("fputs error");
	if (ferror(fsrc))
		err_quit("fgetc error");	
}


/*version3: */
void mycp3(const char *src,  char *dst)
{
	int   srcfd,  dstfd;
	int   n;
	char  buf[BUFFSIZE];
	
	if ((srcfd = open(src, O_RDONLY)) < 0)
		err_sys("open error");
	if ((dstfd = open(dst, O_RDWR | O_CREAT | O_TRUNC)) < 0)
		err_sys("open error");
	
	while ((n = read(srcfd, buf, BUFFSIZE)) > 0)
		if (n != write(dstfd, buf, n))
			err_sys("write error");
	if (n < 0)
		err_sys("read error");
}

int main(int argc, char *argv[])
{
	if (argc != 3)
		err_quit("Usage:  srcfile  dstfile");
	
	mycp1(argv[1], argv[2]);
	//mycp2(argv[1], argv[2]); { fgets() fputs() why not?}
	//mycp3(argv[1], argv[2]);
	exit(0);
}



