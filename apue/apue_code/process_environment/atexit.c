#include "apue.h"
/*printf() ���ʲôʱ�������
*�������ڽ������з�ʽʱ����׼���ͨ�������л��巽ʽ������
*��������з�ʱ���ϴε��������ű����������������׼���������
*һ���ļ���������ȫ���巽ʽ���򵱱�׼IO�������ִ��ʱ������ű������
*/
static  void  my_exit1(void);
static  void  my_exit2(void);

int  main(int argc, char *argv[])
{
	if (0 != atexit(my_exit2))
		err_sys("can't register my_exit1");
	if (0 != atexit(my_exit2))
		err_sys("can't register my_exit1");
	if (0 != atexit(my_exit1))
		err_sys("can't register my_exit2");
		
	printf("main is done\n");
	
	return (0);
}

static void my_exit1(void)
{
	printf("first exit handler\n");
}

static void my_exit2(void)
{
	printf("second exit handler\n");
}

