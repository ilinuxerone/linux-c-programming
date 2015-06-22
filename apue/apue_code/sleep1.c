#include "apue.h"

static void sig_alarm(int signo)
{
	/*nothing to do, just return to wake up the pause*/
}

unsigned int sleep1(unsigned int nsecs)
{
	if (SIG_ERR == (signal(SIGALRM, sig_alarm)))
		return (nsecs);
	alarm(nsecs);
	pause();
	return (alarm(0));
}
