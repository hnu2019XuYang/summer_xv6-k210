#include "kernel/include/signal.h"
#include "xv6-user/user.h"

void ding (int sig)
{
  printf("[%d] Alarm has gone off\n",sig);
}

int test_alarm()
{
  printf("Alarm testing!\n");

  alarm (5);
  printf("Waiting for alarm to go off\n");

  (void) signal ( SIGALRM, ding );
 
  pause();      //process suspended, waiting for signals to wake up
  printf("now reachable!\n");
  return 0;
}

int main()
{
  test_alarm();
  exit(0);
}
