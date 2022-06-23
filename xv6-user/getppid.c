#include "xv6-user/user.h"

int test_getppid()
{
	int status;
	int pid = fork();
	if(pid > 0){
		wait(&status);
		int ppid = getpid();
		printf("parent[%d]: child = %d\n", ppid, pid);
	}else if(pid == 0){
		int cpid = getpid();
		int ppid = getppid();
		printf("child[%d]: parent = %d\n", cpid, ppid);
		exit(0);
	}else{
		printf("fork error\n");
	}
	return 0;
}

int main(void) {
	test_getppid();
	exit(0);
    return 0;
}