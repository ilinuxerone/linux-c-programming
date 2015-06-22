/*need correction*/

#include "apue.h"
#include <pthread.h>

struct  foo{
	int a, b, c, d;
};

void printfoo(const char *str, const struct foo *fp)
{
	printf(str);
	printf(" structure at 0x%x\n", (unsigned)fp);
	printf(" foo.a = %d\n", fp->a);
	printf(" foo.b = %d\n", fp->b);
	printf(" foo.c = %c\n", fp->c);
	printf(" foo.d = %d\n", fp->d);
}

void *thr_fn1(void *arg)
{
	struct foo  fo = {1, 2, 3, 4};
	printfoo("thread 1:\n", &fo);
	pthread_exit((void *)&fo);	
}

void *thr_fn2(void *arg)
{
	printf("thread 2: ID is %d\n", pthread_self());
	pthread_exit((void *)0);
}

int main(int argc, char *argv[])
{
	pthread_t    	tid1, tid2;
	int		err;
	struct 	foo 	*fp;
	
	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (0 != err)
		err_quit("can't create thread 1:%s\n", strerror(err));
	err = pthread_join(tid1, (void *)&fp);
	if (0 != err)
		err_quit("can't join with thread 1:%s\n", strerror(err));
	sleep(1);
	printf("parent starting second thread\n");
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (0 != err)
		err_quit("can't create thread 2:%s\n", strerror(err));
	err = pthread_join(tid2, (void *)&fp);
	if (0 != err)
		err_quit("can't join with thread 2:%s\n", strerror(err));
	sleep(1);
	printfoo("parent:\n", fp);
	exit(0);
}