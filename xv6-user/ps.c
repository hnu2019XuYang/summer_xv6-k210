#include "kernel/include/types.h"
#include "kernel/include/param.h"
#include "kernel/include/ps.h"
#include "xv6-user/user.h"

void print_usage()
{
	printf("\nUsages:\n");
	printf("Try \"-> / $ ps\"\n");
	printf("Or  \"-> / $ ps -o pid,ppid,comm,state,time,etime,vsz (7 fields: optional)\"\n");
}

int setflag(char* tmp, int n)
{
	int flag = n;
	if(strncmp(tmp,"pid",6) == 0)
	{
		flag |= PS_PID;
	}
	else if(strncmp(tmp,"ppid",6) == 0)
	{
		flag |= PS_PPID;
	}
	else if(strncmp(tmp,"comm",6) == 0)
	{
		flag |= PS_COMMAND;
	}
	else if(strncmp(tmp,"state",6) == 0)
	{
		flag |= PS_S;
	}
	else if(strncmp(tmp,"time",6) == 0)
	{
		flag |= PS_TIME;
	}
	else if(strncmp(tmp,"etime",6) == 0)
	{
		flag |= PS_ELAPSED;
	}
	else if(strncmp(tmp,"vsz",6) == 0)
	{
		flag |= PS_VSZ;
	}
	if(flag == n)
	{
		printf("error: unknown user-defined format specifier \"%s\"\n",tmp);
		print_usage();
		exit(0);
	}
	return flag;
}

int parse_arg(char *arg)
{
	int flag = 0;
	char* ptr;
	char tmp[6];
	while((ptr = strchr(arg,',')) != NULL)
	{
		int len = ptr-arg;
		strncpy(tmp,arg,len);
		tmp[len] = '\0';
		flag = setflag(tmp,flag);
		arg = ptr + 1;
	}
	flag = setflag(arg,flag);
	return flag;
}

void format_time(char* times, uint64 ticks)
{
	if(ticks)
		ticks /= CLK_INTER_FREQ;
	int hh,mm,ss;
	char tmp[3];
	ss = ticks % 60;
	ticks /= 60;
	mm = ticks % 60;
	hh = ticks / 60;
	times[0] = '\0';
	itoa(hh,tmp);
	if(hh > 10){
		strcat(times,tmp);
	}else{
		strcat(times,"0");
		strcat(times,tmp);
	}
	strcat(times,":");
	itoa(mm,tmp);
	if(mm > 10){
		strcat(times,tmp);
	}else{
		strcat(times,"0");
		strcat(times,tmp);
	}
	strcat(times,":");
	itoa(ss,tmp);
	if(ss > 10){
		strcat(times,tmp);
	}else{
		strcat(times,"0");
		strcat(times,tmp);
	}
}

void print_hint(int flag)
{
	if(flag & PS_PID)
	{
		printf("PID\t");
	}
	if(flag & PS_PPID)
	{
		printf("PPID\t");
	}
	if(flag & PS_COMMAND)
	{
		printf("COMMAND\t");
	}
	if(flag & PS_S)
	{
		printf("S\t");
	}
	if(flag & PS_TIME)
	{
		printf("TIME\t\t");
	}
	if(flag & PS_ELAPSED)
	{
		printf("ELAPSED\t\t");
	}
	if(flag & PS_VSZ)
	{
		printf("VSZ");
	}
	printf("\n");
}

void print_res(struct procinfo *p, int flag)
{
	if(flag & PS_PID)
	{
		printf("%d\t",p->pid);
	}
	if(flag & PS_PPID)
	{
		printf("%d\t",p->ppid);
	}
	if(flag & PS_COMMAND)
	{
		printf("%s\t",p->command);
	}
	if(flag & PS_S)
	{
		printf("%c\t",p->state);
	}
	if(flag & PS_TIME)
	{
		char tm[10];
		format_time(tm,p->times);
		printf("%s\t",tm);
		// printf("%d\t\t",p->times);
	}
	if(flag & PS_ELAPSED)
	{
		char tm[10];
		format_time(tm,p->etime);
		printf("%s\t",tm);
		// printf("%d\t\t",p->etime);
	}
	if(flag & PS_VSZ)
	{
		printf("%d",p->vsz/1024);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	if(argc > 1 && argc != 3)
	{
		print_usage();
		exit(0);
	}
	int flag = 0x7f;
	if(argc == 3)
	{
		if(strncmp(argv[1],"-o",3) != 0)
		{
			print_usage();
			exit(0);
		}
		flag = parse_arg(argv[2]);
	}
	struct procinfo pi[NPROC];
	int cnt = 0;
	if((cnt = procps(pi)) > 0)
	{
		print_hint(flag);
		int i;
		for(i = 0; i < cnt; i++)
		{
			print_res(&pi[i],flag);
		}
	}
	exit(0);
}