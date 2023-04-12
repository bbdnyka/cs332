/*
    To compile: gcc -O -Wall lab12.c -lpthread 
    To run: ./a.out 1000 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

typedef struct MyVariables{

  double *a, sum; 

  int N, size; 
  
  long tid;

  }MyVariables;

  MyVariables* init_MyVariables(MyVariables *myVariable){

    myVariable->a = NULL;

    myVariable->sum = 0.0;

    myVariable->N = 0;

    myVariable->size = 0;

    return myVariable;

  }

void *compute(void *arg) {

    
    //MyVariables *myVariable;

    MyVariables *myVariable=(MyVariables *)arg;
    //init_MyVariables(&myVariable);
     
    int myStart, myEnd, myN, i;

    myVariable->tid = (long)arg;

    // determine start and end of computation for the current thread
    myN = myVariable->N/myVariable->size;
    myStart = myVariable->tid*myN;
    myEnd = myStart + myN;
    if (myVariable->tid == (myVariable->size-1)) myEnd = myVariable->N;

    // compute partial sum
    double mysum = 0.0;
    printf("jfdkajskl");
    for (i=myStart; i<myEnd; i++)
      mysum += myVariable->a[i];

    // grab the lock, update global sum, and release lock
     //pthread_mutex_lock(&mutex);
     //printf("jdfaksfj");
     //myVariable->sum += mysum;
     //pthread_mutex_unlock(&mutex);

    return (NULL);
}

int main(int argc, char **argv) {

    long i;

    double *a, sum;

    pthread_t *tid;
    if (argc != 3) {
       printf("Usage: %s <# of elements> <# of threads>\n",argv[0]);
       exit(-1);
    }

    int N = atoi(argv[1]); // no. of elements
    int size = atoi(argv[2]); // no. of threads

    MyVariables *myVariable = malloc(sizeof(myVariable)*size);

    //init_MyVariables(myVariable);

    // allocate vector and initialize
    tid = (pthread_t *)malloc(sizeof(pthread_t)*size);
    a = (double *)malloc(sizeof(double)*N);
    
    //defining each struct for each thread
    for(int i = 0; i<size; i++){

      myVariable[i].a = a;

      myVariable[i].sum = 0.0;

      myVariable[i].N = N;

      myVariable[i].size = size;

      myVariable[i].tid = i;

    }

    for (i=0; i<N; i++)
      a[i] = (double)(i + 1);
    // create threads
    for ( i = 0; i < size; i++)
      pthread_create(&tid[i], NULL, compute, ((void *)&myVariable[i]) /*remove i. 
      replace with structure. we can only pass in one argument with a thread.*/);
    
    // wait for them to complete
    for ( i = 0; i < size; i++)
      pthread_join(tid[i], NULL);
    
    printf("The total is %g, it should be equal to %g\n", 
           sum, ((double)N*(N+1))/2);
    
    return 0;
}