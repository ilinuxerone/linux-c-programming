#include "apue.h"

int main(int argc, char *argv[])
{
	int  characters, words, lines, flag;
	int  c;
	
	characters = words = lines = flag = 0;
	while (EOF != (c = getchar())){
		characters++;
		if ('\n' == c){
			lines++;
			continue;
		}else if (' ' == c){
			flag = 0;
			continue;
		}else if ('\t' == c){
			flag = 0;
			continue;
		}else {
			if (0 == flag){
				flag = 1;
				words++;
			}
			continue;
		}
	}
	printf("characters: %d words: %d lines : %d\n", characters, words, lines);
	exit(0);
}

		 
		
		