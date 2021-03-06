#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct fraction {
  int num;
  int denum;
};

typedef struct fraction Fraction_t;

void error(int err, char *msg) {
  fprintf(stderr,"%s a retourne %d, message d'erreur : %s\n",msg,err,strerror(errno));
  exit(EXIT_FAILURE);
}

float tofloat(Fraction_t t) {
  return (float) t.num/ (float) t.denum;

}


void *mythread(void * param) {
  Fraction_t *t=(Fraction_t *) param;
  float *r=(float *)malloc(sizeof(float));
  *r=(float) t->num/ (float) t->denum;
  return((void *) r);
}

int main (int argc, char *argv[])  {


  pthread_t t;
  Fraction_t f;
  f.num=1;
  f.denum=3;
  printf("%f \n",tofloat(f));
  float *r;
  int err;

  err=pthread_create(&t,NULL,&mythread,&f);
  if(err!=0)
    error(err,"pthread_create");

  r=pthread_join(t,NULL);

  if(err!=0)
    error(err,"pthread_join");

  printf("%f \n",(float) (*r));

  return(EXIT_SUCCESS);
}
