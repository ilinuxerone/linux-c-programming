#include "apue.h"

/*
*vfork:
the child share the address space of the parent.
*parent is put to sleep by the kernel until the child calls either
*exec or exit. 
*/

int glob = 6;

int main(int argc, char *argv[])
{
	int  var;
	pid_t  pid;
	
	var = 88;
	printf("before vfork\n");
	if ( (pid = vfork()) < 0 ){
		err_sys("vfork error");
	} else if (0 == pid){
		glob++;
		var++;
		_exit(0);
	}
	
	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
	exit(0);
}