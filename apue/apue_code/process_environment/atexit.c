#include "apue.h"
/*printf() 语句什么时候输出呢
*当程序处于交互运行方式时，标准输出通常处于行缓冲方式，所以
*当输出换行符时，上次的输出结果才被真正输出。若果标准输出被定向到
*一个文件而处于完全缓冲方式，则当标准IO清理操作执行时，结果才被输出。
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

