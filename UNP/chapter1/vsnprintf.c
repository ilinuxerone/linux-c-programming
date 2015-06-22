/*
*printf()
*sprintf()
*snprintf()
*fprintf()
*vprintf()
*vsprintf()
*vsnprintf()
*vfprintf()
*/


#include <stdio.h>
#include <string.h>
#include <stdarg.h>

char msgbuf[80];


char *fmtmsg(char *format, ...)
{
	va_list  arglist;
	
	va_start(arglist, format);
	strcpy(msgbuf, "Error: ");
	vsnprintf(&msgbuf[7], 80 - 7, format, arglist);
	va_end(arglist);
	return(msgbuf);
}

int main(void)
{
	char *msg;
	
	msg = fmtmsg("%s %d %s", "failed", 100, "times");
	printf("%s\n", msg);
	
	return 0;	
}













