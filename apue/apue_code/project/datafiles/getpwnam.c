#include <pwd.h>
#include <string.h>

struct passwd  *getpwnam(const char *name)
{
	struct passwd  *ptr;
	
	setpwent();
	while (NULL != (ptr = getpwent()))
		if (!strcmp(name, ptr->pw_name))
			break;
	endpwent();
	
	return (ptr);
}

