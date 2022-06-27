#ifndef __SIGNAL_H
#define __SIGNAL_H

#include "types.h"

#define SIGTERM 	15
#define SIGALRM		14
#define SIGINT 		2

#define SIG_DEF		((void(*)(int))1)
#define SIG_IGN		((void(*)(int))2)

// #define SIG_DEF		0
// #define SIG_IGN		1

typedef void (*func)(int);

struct sigaction{
	uint64 sig;
	// uint64 handler;
	func handler;
};

void sighandle(void);
// void sigreturn(void);

#endif