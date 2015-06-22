#include "apue.h"
#include <fcntl.h>

void set_fl(int fd, int flags)           /*flags are file status flags to turn on*/
{
	int   flag;
	
	if ((flag = fcntl(fd, F_GETFL, 0)) < 0)
		err_quit("fcntl F_GETFL error");
	
	flag |= flags;		/*turn on flags*/
	
	/*turn of flags*/
	//flag &= ~flags;
		
	if (fcntl(fd, F_SETFL, flag) < 0)
		err_quit("fcntl F_SETFL error");
}