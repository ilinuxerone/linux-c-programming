#include "apue.h"
#include <pwd.h>

static void my_alarm(int signo)
{
	struct passwd  *rootptr;
	
	printf("in signal handler\n");
	if (NULL == (rootptr = getpwnam("root")))
		err_sys("getpwname(root) error");
	alarm(1);
}


int main(int argc, char *argv[])
{
	struct passwd  *ptr;
	
	signal(SIGALRM, my_alarm);
	alarm(1);
	for (; ;) {
		if (NULL == (ptr = getpwnam("zhihong")))
			err_sys("getpwnam error");
		if (strcmp(ptr->pw_name, "zhihong") != 0)
			printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
	}
}
