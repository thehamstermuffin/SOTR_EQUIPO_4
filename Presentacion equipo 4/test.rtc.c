#include <stdio.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>


/* retorna "a - b" en segundos */


int main(int argc, char *argv[])
{
  int i;
  double x, y, z;
struct rtc_time cutoff_dates[10];
struct rtc_time rtc1;

        rtc1.tm_year = 70, /* 1970 -1900 */
        rtc1.tm_mday = 1,

cutoff_dates[0]=rtc1;
///  rtc1.RTC_SET_TIME();
//  for(i=1;i<=10000;i++){z = x*x + y*y;}

  printf(": %p\n", &cutoff_dates[0].tm_sec);

}
