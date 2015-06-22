#include "apue.h"

unsigned int sleep2(unsigned int);
static void sig_intr(int);

int main(int argc, char *argv[])
{
	unsigned int unslept;
	
	if (SIG_ERR == signal(SIGINT, sig_intr))
		err_sys("signal error");
	unslept = sleep2(5);
	printf("sleep2 returnd %d\n", unslept);
	return (0);
}

static void sig_intr(int signo)
{
	int i, j;
	volatile int k;
	
	printf("\nsig_intr start...\n");
	for (i = 0; i < 300000; i++)
		for(j = 0; j < 4000; j++)
			k += i * j;
	printf("\nsig_intr finished\n");
}