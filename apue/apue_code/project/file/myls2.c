#include "apue.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <pwd.h>

/*
int  get_type(char *path);
int  get_mode(char *path);
int  get_size(char *path);
int  get_time(char *path, char *ch);
int  get_nlink(char *path);
int  get_name(char *path);
struct dirent **scan_dir(int *n);
int no_ls();
int l_ls();
int al_ls();
int a_ls();
int A_ls();
int  dir_ls(char *name);
int  name_ls(int argc, char *argv[]);
int  file_ls(char *path);
int mylist(char *option);
*/

int get_type(char *path)
{
	struct stat buf;
	char   *ptr;
	
	if (lstat(path, &buf) < 0)
		err_msg("lstat error");
	switch (S_IFMT & buf.st_mode)
	

