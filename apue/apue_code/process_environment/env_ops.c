#include "apue.h"
#include <stdlib.h>


int main(int argc, char *argv[])
{
	putenv("HOME=hahs");
	printf("home:%s\n", getenv("HOME"));
	
	setenv("HOME", "haha", 0);
	printf("%s\n", getenv("HOME"));
	
	setenv("HOME", "haha", 1);
	printf("%s\n", getenv("HOME"));
	
	return (0);
}