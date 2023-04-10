/*
    To compile: gcc -Wall -o lab12.c -lpthread 
    To run: ./a.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

typedef struct MyVariables{

  double *a, sum; 
  
  int N, size; 
  
  long tid

  }MyVariables;

  MyVariables* init_MyVariables(MyVariables *myVariable){

    myVariable->a = NULL;

    myVariable->sum = 0.0;


    return myVariable;

  }

void *compute(void *arg) {

    MyVariables myVariable;

    init_MyVariables(&myVariable);
     
    int myStart, myEnd, myN, i;

    myVariable.tid = (long)arg;

    // determine start and end of computation for the current thread
    myN = myVariable.N/myVariable.size;
    myStart = myVariable.tid*myN;
    myEnd = myStart + myN;
    if (myVariable.tid == (myVariable.size-1)) myEnd = myVariable.N;

    // compute partial sum
    double mysum = 0.0;
    for (i=myStart; i<myEnd; i++)
      mysum += myVariable.a[i];

    // grab the lock, update global sum, and release lock
    pthread_mutex_lock(&mutex);
    myVariable.sum += mysum;
    pthread_mutex_unlock(&mutex);

    return (NULL);
}

int main(int argc, char **argv) {

    MyVariables myVariable;

    init_MyVariables(&myVariable);

    long i;
    pthread_t *tid;

    if (argc != 3) {
       printf("Usage: %s <# of elements> <# of threads>\n",argv[0]);
       exit(-1);
    }

    myVariable.N = atoi(argv[1]); // no. of elements
    myVariable.size = atoi(argv[2]); // no. of threads

    // allocate vector and initialize
    tid = (pthread_t *)malloc(sizeof(pthread_t)*myVariable.size);
    myVariable.a = (double *)malloc(sizeof(double)*myVariable.N); 
    for (i=0; i<myVariable.N; i++)
      myVariable.a[i] = (double)(i + 1);

    // create threads
    for ( i = 0; i < myVariable.size; i++)
      pthread_create(&tid[i], NULL, compute, (void *)i);
    
    // wait for them to complete
    for ( i = 0; i < myVariable.size; i++)
      pthread_join(tid[i], NULL);
    
    printf("The total is %g, it should be equal to %g\n", 
           myVariable.sum, ((double)myVariable.N*(myVariable.N+1))/2);
    
    return 0;
}
