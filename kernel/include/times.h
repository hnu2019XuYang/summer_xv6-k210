#ifndef __TIMES_H
#define __TIMES_H

#include "types.h"

struct tms {
	uint64 utime; // user time (in seconds)
	uint64 stime; // system time
	uint64 cutime; // user time of children
	uint64 cstime; // system time of children
};

#endif