#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
void mydir(DIR *tmp, int*c_dir, int *c_file, int c_indent){
	struct dirent *curfile=NULL;
	int i=0;
	int c=0;
	static int queue;
	char st_name[1024][256];
	while(curfile=readdir(tmp)){
		if(!strcmp(curfile->d_name,".") || !strcmp(curfile->d_name,".." ))
			continue;
		DIR *inner=opendir(curfile->d_name);
		if(inner){
			strcpy(st_name[c],curfile->d_name);
			c++;
			(*c_dir)++;
			closedir(inner);
		}else{
			if(c_indent)
				printf("|");
			for(i=0;i<c_indent;i++){
					printf("   ");
			}
			printf("|__%s\n",curfile->d_name);
			(*c_file)++;
		}
	}
/*
	if(c==0){
		return;
	}*/
	for(c=c-1;c>=0;c--){
		if(c_indent)
			printf("|");
		for(i=0;i<c_indent;i++){
			printf("   ");
		}
		printf("|__%s\n",st_name[c]);
		DIR *tmpdir=opendir(st_name[c]);
		c_indent++;
		chdir(st_name[c]);
		mydir(tmpdir,c_dir,c_file,c_indent);
		c_indent--;
		closedir(tmpdir);
		chdir("..");
	}
}
int main(void)
{
	//opendir
	DIR *cur=opendir(".");
	int dir=0;
	int file=0;
	int indent=0;
	printf(".\n");
	mydir(cur, &dir, &file, indent);
	printf("\n%d directories, %d files\n",dir,file);
	closedir(cur);
	return 0;
}
