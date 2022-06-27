#include "kernel/include/signal.h"
#include "xv6-user/user.h"

int test_alarm()
{
  printf("Alarm testing!\n");

  alarm (5);
  
  printf("Waiting for alarm to go off\n");
  (void) signal ( SIGALRM, SIG_DEF );
  // (void) signal ( SIGALRM, SIG_IGN );
 
  pause();      //process suspended, waiting for signals to wake up
  printf("now reachable!\n");
  return 0;
}

int main()
{
  test_alarm();
  exit(0);
}