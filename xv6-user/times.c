#include "kernel/include/types.h"
#include "kernel/include/times.h"
#include "xv6-user/user.h"

int test_times()
{
	struct tms t;
	clock_t ticks = times(&t);
	printf("the usertime of the process: %d\n",ticks);
	printf("utime:%d,stime:%d,cutime:%d,cstime:%d\n",t.utime,t.stime,t.cutime,t.cstime);
	return 0;
}

int main(void) {
	test_times();
	exit(0);
    return 0;
}