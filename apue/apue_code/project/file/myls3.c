#include "apue.h"
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#define PATH_MAX  256

void do_ls(char *);
void do_stat(char *);
void show_file_info(char *, struct stat *);
void mode_str(int, char *);
char *uid_str(uid_t);
char *gid_str(gid_t);

int main(int argc, char *argv[])
{
	if (1 == argc)
		do_ls(".");
	else {
		while (--argc){
			printf("%s:\n", *++argv);
			do_ls(*argv);
		}
	}
	exit(0);
}

void do_ls(char *path)
{
	DIR   *dp;
	struct dirent *dirp;
	char full_path[PATH_MAX];
	int  dir_len;
	
	if (NULL == (dp = opendir(path))){
		err_msg("opendir error");
		return ;
	}else {
		while (NULL != (dirp = readdir(dp))){
			strcpy(full_path, path);
			dir_len = strlen(path);
			if ('/' != path[dir_len - 1]){
				full_path[dir_len] = '/';
				strcpy(full_path + dir_len + 1, dirp->d_name);
			}else 
				strcpy(full_path + dir_len, dirp->d_name);
				do_stat(full_path);
		}
		closedir(dp);
	}
}

void do_stat(char *path)
{
	struct  stat   buf;
	char *pname;
	
	if (stat(path, &buf) < 0){
		err_msg("stat error");
		return;
	}else {
		pname = strrchr(path, '/');
		show_file_info(pname + 1, &buf);	
	}
}

void show_file_info(char *path, struct stat *pbuf)
{
	char  modestr[11];
	
	mode_str(pbuf->st_mode, modestr);
	printf("%s", modestr);
	
	printf("%3d ", (int)pbuf->st_nlink);
	printf("%-8s", uid_str(pbuf->st_uid));
	printf("%-8s", gid_str(pbuf->st_gid));
	printf("%4ld ", (long)pbuf->st_size);
	printf("%.12s ",4 + ctime(&pbuf->st_mtime));
	printf("%s\n", path);
}

/*Ã»ÓÐ¿¼ÂÇS_ISGID S_ISUID S_ISVTX Î»*/
void mode_str(int mode, char *modestr)
{
	strcpy(modestr, "----------");
	if (S_ISDIR(mode)) modestr[0] = 'd';
	if (S_ISCHR(mode)) modestr[0] = 'c';
	if (S_ISBLK(mode)) modestr[0] = 'b';
	if (S_ISLNK(mode)) modestr[0] = 'l';
	if (S_ISFIFO(mode)) modestr[0] = 'f';
	if (S_ISSOCK(mode)) modestr[0] = 's';
	
	if (mode & S_IRUSR) modestr[1] = 'r';
	if (mode & S_IWUSR) modestr[2] = 'w';
	if (mode & S_IXUSR) modestr[3] = 'x';
	
	if (mode & S_IRGRP) modestr[4] = 'r';
	if (mode & S_IWGRP) modestr[5] = 'w';
	if (mode & S_IXGRP) modestr[6] = 'x';
	
	if (mode & S_IROTH) modestr[7] = 'r';
	if (mode & S_IWOTH) modestr[8] = 'w';
	if (mode & S_IXOTH) modestr[9] = 'x';
}

char *uid_str(uid_t uid)
{
	static  char numstr[10];
	struct passwd  *pw_ptr;
	
	if (NULL == (pw_ptr = getpwuid(uid))){
		sprintf(numstr, "%d", uid);
		return numstr;
	}else
		return pw_ptr->pw_name;
}

char *gid_str(gid_t gid)
{
	static char numstr[10];
	struct group  *grp_ptr;
	
	if (NULL == (grp_ptr = getgrgid(gid))){
		sprintf(numstr, "%d", gid);
		return numstr;
	}else
		return grp_ptr->gr_name;
}
	

			