#include "apue.h"

/* ͨ����getenv��putenv�������ض��Ļ������������Ҫ�鿴��������������
*�������ȫ�ֱ���environָ�롣
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