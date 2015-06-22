
/*
*#include <sys/times.h>
*
*clock_t  times(struct tms *buf);
*All the clock_t values returned by this function 
*are converted to seconds using the number of 
*clock ticks per secondthe _SC_CLK_TCK value returned by sysconf 
*struct tms{
*clock_t  tms_utime;
*clock_t  tms_stime;
*clock_t  tms_cutime;
*clock_t  tms_cstime;
*};
*/

#include "apue.h"
#include <sys/times.h>
#include <limits.h>
#include <unistd.h>

static void pr_times(clock_t, struct tms *, struct tms *);
static void do_cmd(char *);

int main(int argc, char *argv[])
{
	int  i;
	
	setbuf(stdout, NULL);
	for (i = 1; i < argc; i++)
		do_cmd(argv[i]);
	exit(0);
}

static void do_cmd(char *cmd)    /*execute and time the "cmd"*/
{
	struct tms  tmsstart, tmsend;
	clock_t   start, end;
	int  status;
	
	printf("\ncommand:%s\n", cmd);
	
	if ( (start = times(&tmsstart)) == -1 )
		err_sys("times error");
	
	if ( (status = system(cmd)) < 0 )
		err_sys("system() error");
	
	if ( (end = times(&tmsend)) == -1 )
		err_sys("times error");
	
	pr_times(end - start, &tmsstart, &tmsend);
	pr_exit(status);
}

static void pr_times(clock_t  real, struct tms *tmsstart, struct tms *tmsend)
{
	static long  clktck = 0;
	
	if (0 == clktck)
		if ( (clktck = sysconf(_SC_CLK_TCK)) < 0 )
			err_sys("sysconf error");
		printf("real: %7.2f\n", real / (double)clktck);
		printf("user: %7.2f\n", 
		 	(tmsend->tms_utime - tmsstart->tms_utime) / (double)clktck);
		printf(" sys: %7.2f\n", 
			(tmsend->tms_stime - tmsstart->tms_stime) / (double)clktck);
		printf("child user:%7.2f\n", 
			(tmsend->tms_cutime - tmsstart->tms_cutime) / (double)clktck);
		printf("child sys:%7.2f\n", 
			(tmsend->tms_cstime - tmsstart->tms_cstime) / (double)clktck);
}
