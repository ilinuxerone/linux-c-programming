#include "apue.h"
#include <dirent.h>

void do_ls(const char *);

int main(int argc, char *argv[])
{
//	DIR        *dp;
//	struct   dirent  *dirp;
//	int 	i, j;
	
	/*
	if (2 != argc)
		err_quit("Usage %s <directory>", argv[0]);
		
	if (NULL == (dp = opendir(argv[1])))
		err_ret("can't open %s", argv[1]);	
	while (NULL != (dirp = readdir(dp))){
		printf("%s\n", dirp->d_name);
	}
	*/
	
	/*
	for (i = 1; i < argc; i++){
		if (NULL == (dp = opendir(argv[i]))){
			err_msg("can't access");
			continue;
		}
		printf("%s:\n", argv[i]);
		while (NULL != (dirp = readdir(dp)))
			printf("%s\n", dirp->d_name);
	}
	
	
	closedir(dp);
	exit(0);
	*/
	
	if (1 == argc)
		do_ls(".");
	else {
		while (--argc){
			do_ls(*++argv);
		}
	}
	exit(0);
}
		

void do_ls(const char *dname)
{
	DIR   *dp;
	struct dirent *dirp;
	
	if (NULL == (dp = opendir(dname))){
		err_msg("can't access");
		return ;
	}
	while (NULL != (dirp = readdir(dp)))
			printf("%s\n", dirp->d_name);
	closedir(dp);
}