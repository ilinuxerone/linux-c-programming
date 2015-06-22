/*
 *pthreads wrapper functions.
 */

#include "unpipc.h"

void Pthread_create(pthread_t *tid, const pthread_attr_t *attr,
			void *(*func)(void *), void *arg)
{
	int	n;

	if ((n = pthread_create(tid, attr, func, arg)) == 0)
		return;
	errno = n;
	err_sys("pthread_create error");
}

void Pthread_join(pthread_t tid, void **status)
{
	int	n;
	
	if ((n = pthread_join(tid, status)) == 0)
		return;
	errno = n;
	err_sys("pthread_join error");
}

void Pthread_mutex_init(pthread_mutex_t *mptr, pthread_mutexattr_t *attr)
{
	int	n;
	
	if ((n = pthread_mutex_init(mptr, attr)) == 0)
		return;
	errno = n;
	err_sys("pthread_mutex_init error");
}


void Pthread_mutex_destroy(pthread_mutex_t *mptr)
{
	int	n;
	
	if ((n = pthread_mutex_destroy(mptr)) == 0)	
		return;
	errno = n;
	err_sys("pthread_mutex_destroy error");
}

void Pthread_mutex_lock(pthread_mutex_t *mptr)
{
	int 	n;
	
	if ((n = pthread_mutex_lock(mptr)) == 0)
		return;
	errno = n;
	err_sys("pthread_mutex_lock error");
}

void Pthread_mutex_unlock(pthread_mutex_t *mptr)
{
	int 	n;
	
	if ((n = pthread_mutex_unlock(mptr)) == 0)
		return;
	errno = n;
	err_sys("pthread_mutex_unlock error");
}


long pr_thread_id(pthread_t *ptr)
{
	return ((ptr == NULL) ? pthread_self() : *ptr);
}

