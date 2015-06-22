#include <stdio.h>
#include <stdlib.h>

/*calloc ��������ڴ�ռ��ʼ��Ϊ0������ISO C������֤0ֵ�븡��0 �� ��ָ���ֵ��ͬ
*ֻ��ͨ��exec����ִ��һ������ʱ���Ż����Ѻ�ջ�� �����size ����ʽ������ʾ�Ѻ�ջ�Ĵ�С��
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

