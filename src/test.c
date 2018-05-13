/* localtime example */
#include <stdio.h>
#include <time.h>
#include <string.h>

int main ()
{
  time_t rawtime;
  struct tm * timeinfo;
  char time_stamp[50];

  time( &rawtime );
  timeinfo = localtime ( &rawtime );
  strcpy(time_stamp, asctime(timeinfo));
  printf ( "Current local time and date: %s\n", time_stamp );

  return 0;
}
