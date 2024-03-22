#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define NTHREADS 10
sem_t semaphore;

void *my_thread(void * arg)
{
    printf("I'm thread %s\n", (char*)arg);
    pthread_exit(0);
}

int main (int argc, char *argv[])  {
  pthread_t thread[NTHREADS];
  int err;

  err=sem_init(&semaphore, 0, 1); 
  if(err!=0) {
      fprintf (stderr, "sem_init error\n");
      exit (1);
  }
  for(int i=0;i<NTHREADS;i++) {
    err=pthread_create(&(thread[i]),NULL,my_thread, i);
    if(err!=0) {
      fprintf (stderr, "pthread_create error for thread %d\n", i);
      exit (1);
    }
  }

  for(int i=0;i<NTHREADS;i++) {
    err=pthread_join(thread[i],NULL);
    if(err!=0) {
      fprintf (stderr, "pthread_join error\n");
      exit (1);
    }
  }
  sem_destroy(&semaphore);
  if(err!=0) {
      fprintf (stderr, "sem_destroy error\n");
      exit (1);
  }
  return(EXIT_SUCCESS);
}