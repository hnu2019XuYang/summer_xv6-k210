#include "kernel/include/types.h"
#include "kernel/include/times.h"
#include "xv6-user/user.h"

int test_times()
{
	struct tms t;
	int status;
	int pid = fork();
	if(pid > 0){
		wait(&status);
		clock_t ticks = times(&t);
		printf("parent process:\n");
		printf("the total time: %d\n",ticks);
		printf("utime:%d,stime:%d,cutime:%d,cstime:%d\n",t.utime,t.stime,t.cutime,t.cstime);
	}else if(pid == 0){
		printf("Hello from child process!\n");
		exit(0);
	}else{
		printf("fork error\n");
	}
	return 0;
}

int main(void) {
	test_times();
	exit(0);
    return 0;
}