/* 
   Simple Pthread Program to illustrate the create/join threads.
   Author: Purushotham Bangalore
   Date: Jan 25, 2009

   To Compile: gcc -O -Wall pthread1.c -lpthread
   To Run: ./a.out 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int nthreads;

void *compute(void *arg) {
  long tid = (long)arg;

  printf("Hello, I am thread %ld of %d\n", tid, nthreads);

  return (NULL);
}

int main(int argc, char **argv) {
  long i;
  pthread_t *tid;

  if (argc != 2) {
    printf("Usage: %s <# of threads>\n",argv[0]);
    exit(-1);
  }

  nthreads = atoi(argv[1]); // no. of threads

  // allocate vector and initialize
  tid = (pthread_t *)malloc(sizeof(pthread_t)*nthreads);

  // create threads
  for ( i = 0; i < nthreads; i++)
    pthread_create(&tid[i], NULL, compute, (void *)i);
    
  // wait for them to complete
  for ( i = 0; i < nthreads; i++)
    pthread_join(tid[i], NULL);
    
  printf("Exiting main program\n");

  return 0;
}



