#include "include/types.h"
#include "include/proc.h"
#include "include/printf.h"
#include "include/string.h"
#include "include/signal.h"
#include "include/memlayout.h"

void sighandle(void)
{
	struct proc *p = myproc();
	int signum = p->killed;
	int i = 0;
	for(i=0;i<2;i++){
		if(signum == p->sigact[i].sig){
			if(p->sigact[i].handler == SIG_DEF){
				p->killed = 0;
				kill(p->pid,SIGTERM);		
			}else if(p->sigact[i].handler == SIG_IGN){
				p->killed = 0;
				break;
			}else{
				// memmove(p->sigframe, p->trapframe, sizeof (struct trapframe));
				// p->trapframe->sp -= 4;
				// *(uint64*)(p->trapframe->sp) = p->trapframe->epc;
				p->trapframe->a0 = p->killed;
				p->trapframe->epc = (uint64)p->sigact[i].handler;
				p->killed = 0;
			}
		}
	}
}

// void sigreturn(void)
// {
// 	struct proc* p = myproc();
	// memmove(p->trapframe, p->sigframe, sizeof(struct trapframe));
// 	p->killed = 0;
// 	p->sigflag = 0;
// }