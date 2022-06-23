#include "kernel/include/types.h"
#include "kernel/include/times.h"
#include "xv6-user/user.h"

int test_times()
{
	struct tms t;
	clock_t ticks = times(&t);
	printf("the usertime of the process: %d\n",ticks);
	return 0;
}

int main(void) {
	test_times();
	exit(0);
    return 0;
}