#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>


monitor bridge
{
  condition c;
  int traffic = 0;


  enter_bridge()
  {
    while(traffic >= 0)
      c.wait();
    traffic++;
    c.signal();
  }

  exit_bridge()
  {
    if(off_bridge)
      traffic--;
    c.signal();
  }

}