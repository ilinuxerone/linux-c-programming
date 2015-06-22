#include <stdlib.h>
#include <pthread.h>

struct foo {
	int    			f_count;
	pthread_mutex_t		f_lock;
	/*...more stuff here...*/
};

struct foo *foo_alloc(void)
{
	struct foo *fp;
	
	if (NULL != (fp = malloc(sizeof(struct foo)))){
		fp->f_count = 1;
		if (0 != pthread_mutex_init(&fp->f_lock, NULL)){
			free(fp);
			return (NULL);
		}
		/*...continue initialization...*/
	}
	return (fp);
}

void  foo_hold(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	if (0 == --fp->f_count){
		