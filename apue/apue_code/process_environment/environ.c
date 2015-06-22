#include "apue.h"

/* 通常用getenv和putenv来访问特定的环境变量，如果要查看整个环境变量，
*则必须用全局变量environ指针。
*/
extern char **environ;

int main(int argc, char *argv[])
{
	/*
	do {
		printf("%s\n", *environ);
		usleep(1);
	}while (*++environ);
	*/
	
	for (; *environ; *environ++)
		printf("%s\n", *environ);
		
	
	return 0;
}