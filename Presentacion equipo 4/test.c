#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

#define TIME_THIS(X)                                         \
  {                                                          \
    struct timespec ts1, ts2;                                \
    clock_gettime( CLOCK_REALTIME, &ts1 );                   \
    X;                                                       \
    clock_gettime( CLOCK_REALTIME, &ts2 );                   \
    printf( #X " demora: %f\n",                              \
      (float) ( 1.0*(1.0*ts2.tv_nsec - ts1.tv_nsec*1.0)*1e-9 \
      + 1.0*ts2.tv_sec - 1.0*ts1.tv_sec ) );                 \
  }

/* podemos usarla así */
void main(void)
{

  int i;
  double x, y, z;
  x = 2.0;
  y = 4.0;
//  TIME_THIS(z =x*x + y*y);
  TIME_THIS(for(i=1;i<=10000;i++){z = x*x + y*y;});
}
