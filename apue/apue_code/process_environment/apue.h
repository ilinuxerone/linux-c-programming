
#ifndef  __APUE_H
#define  __APUE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#define   MAXLINE   4096

#define  max(a,b)  ((a) > (b) ? (a) : (b))
#define  min(a,b)   ((a) < (b) ? (a) : (b))

void  err_sys(char *, ...);






#endif /*__APUE_H*/





