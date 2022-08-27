#ifndef __PS_H
#define __PS_H

#include "types.h"
#include "times.h"

#define PS_PID		0x01
#define PS_PPID		0x02
#define PS_COMMAND	0x04
#define PS_S 		0x08
#define PS_TIME		0x10
#define PS_ELAPSED  0x20
#define PS_VSZ		0x40

struct procinfo {
	int pid;
	int ppid;
	char command[16];
	char state;
	uint64 times;
	uint64 etime;
	int vsz;
};

#endif