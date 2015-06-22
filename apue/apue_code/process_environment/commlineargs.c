#include "apue.h"

int main(int argc, char *argv[])
{
	int  i;
	
	/*
	for (i = 0; i < argc; i++)
		printf("argv[%d]: %s\n", i, argv[i]);
	*/
	
	/*
	for (i = 0; NULL != argv[i]; i++)
		printf("argv[%d]: %s\n", i, argv[i]);
	*/
	
	/*
	while (NULL != *argv) {
		printf("%s\n", *argv);	
		*argv++;
	}
	*/
	
	/*
	for (; NULL != *argv; *argv++)
		printf("%s\n", *argv);
	*/
	
	do {
		printf("%s\n", *argv);
	} while (NULL != *++argv);
	
	return (0);
}