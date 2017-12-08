#include <stdio.h>
#include <time.h>
#include <sys/time.h>


/* retorna "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b)
{
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}

int main(int argc, char *argv[])
{
  int i;
  double x, y, z;
  x = 2.0;
  y = 4.0;


  struct timeval t_ini, t_fin;
  double secs;

  gettimeofday(&t_ini, NULL);

  //hacer algo aqui
    for(i=1;i<=1000000;i++)
    {
      z=x+y+i;
      //printf("%f\n", z );
    }


  gettimeofday(&t_fin, NULL);

  secs = timeval_diff(&t_fin, &t_ini);
  printf("%.16g milliseconds\n", secs * 1000.0);
  return 0;
}
