#include <sys/wait.h>
#include "apue.h"

/*
int main(int argc, char *argv)
{
	int   status;
	
	if ((status = mysystem("date")) < 0)
		err_sys("system() error");
	pr_exit(status);
	
	if ((status = mysystem("nosuchcommand")) < 0)
		err_sys("mysystem error");
	pr_exit(status);
	
	if ((status = mysystem("who; exit 44")) < 0)
		err_sys("system() error");
	pr_exit(status);
	
	exit(0);
}
*/

int main(int argc, char *argv[])
{
	int  status;
	
	if (argc < 2)
		err_quit("command-line argumen required");
	if ((status = system(argv[1])) < 0)
		err_sys("system() error");
	pr_exit(status);
	
	exit(0);
}