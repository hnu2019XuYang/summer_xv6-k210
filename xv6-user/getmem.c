#include "xv6-user/user.h"

int test_getmem()
{
	int size = getmem();
	printf("the virtual memory size of the process is %d\n",size);
	char* str = malloc(20);
	size = getmem();
	strcpy(str,"hello world!");
	printf("after malloc with size of %d: %d\n",strlen(str),size);
	return 0;
}

int main(void) {
	test_getmem();
	exit(0);
    return 0;
}