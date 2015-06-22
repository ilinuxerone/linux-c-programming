#include <stdio.h>
#include <stdlib.h>

/*calloc 将分配的内存空间初始化为0，但是ISO C并不保证0值与浮点0 或 空指针的值相同
*只有通过exec函数执行一个程序时，才会分配堆和栈， 因此用size 命令式并不显示堆和栈的大小。
*/

void *mycalloc(size_t  nobjs, size_t size)
{
	void  *result = NULL;
	
	/*use malloc to get the memory*/
	result = malloc(nobjs * size);
	
	/*and clear the memory on successful allocation*/
	if (NULL != result) {
		memset(result, 0, nobjs * size);
	}
	
	/*and return the result*/
	return (result);
	
}

int main(int argc, char *argv[])
{
	int *p = NULL;
	int i = 0;
	
	p = mycalloc(100, sizeof(*p));
	if (NULL == p){
		printf("mycalloc failed...\n");
	} else {
		for (i = 0; i < 100; i++) {
			printf("%d", p[i]);
			if (i % 8 == 7) {
				printf("\n");
			}
		}
		printf("\n");
		free(p);
	}
	
	return (0);
}

