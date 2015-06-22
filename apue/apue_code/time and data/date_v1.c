#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define  MAXSIZE    1024

int main(int argc, char *argv[])
{
	struct tm  *tmptr = NULL;
	time_t     caltime;
	char  buf[MAXSIZE];
	size_t  size;
	
	caltime = time(NULL);
	if (time < 0){
		fprintf(stderr, "get time error:%s\n", strerror(errno));
		return -1;
	}
		
	printf("time: %ld\n", caltime);
	printf("ctime:%s", ctime(&caltime));
	
	tmptr = localtime(&caltime);
	if (NULL == tmptr){
		fprintf(stderr, "localtime call failed:%s!\n", strerror(errno));
		return -1;
	}
	
	printf("local time:%s", asctime(tmptr));
	
//	size = strftime(buf, MAXSIZE, "%c\n", tmptr);
	size = strftime(buf, MAXSIZE, "%a %b %d %X %Z %Y\n", tmptr);
	if (size){
	//	fprintf(stdout, "strftime:%s, size :%d\n", buf, size);
		fputs(buf, stdout);
	}
	
	return 0;
}
