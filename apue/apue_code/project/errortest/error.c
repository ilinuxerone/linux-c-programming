#include "apue.h"

int main(int argc, char *argv[])
{
	/*test err_sys()*/
	errno = -1;
	err_msg("just test err_msg()");
	err_quit("just test err_quit()");
	err_exit( 2, "just test err_exit()");
	err_ret("just test err_ret()");
	err_sys("just test err_sys()");
	err_dump("just test err_dump()");
	
	
	exit(0);
}
	
	