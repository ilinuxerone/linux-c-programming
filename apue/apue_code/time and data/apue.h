/*our own header, uncompleted */

#ifndef  __APUE_H
#define  __APUE_H

#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define  MAXLINE   4096

#define  min(a,b)  ((a) < (b) ? (a) : (b))
#define  max(a,b)  ((a) > (b) ? (a) : (b))

/*Protocol for our own function*/

void  err_sys(const char *, ...);


#endif /*__APUE_H*/