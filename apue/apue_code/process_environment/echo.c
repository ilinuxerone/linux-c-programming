#include "apue.h"

int main(int argc, char *argv[])
{
	int i = 0;
	
	/*
	do {
		printf("%s ", *++argv);
	  }while (*argv);  //����������ʺ���do while���
	 */
	
	/* 
	 for (i = 1; i < argc; i++)
	 	printf("%s ", argv[i]);
	 printf("\n");
	 */
	
	/*	 
	 for (i = 1; argv[i]; i++)
	 	printf("%s ", argv[i]);
	 printf("\n"); 
	 */
	 
	 /*
	 for (; *++argv; )
	 	printf("%s ", *argv);
	 printf("\n");
	 */
	 
	 while (*++argv)
	 	printf("%s ", *argv);
	 printf("\n");
	 
	 return (0);		
}