/*
    To compile: gcc -O -Wall lab12.c -lpthread 
    To run: ./a.out 1000 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
//define struct
typedef struct MyVariables{

  double *a, sum; 

  int N, size; 
  
  long tid; 

  }MyVariables;
  //struct function

  MyVariables* init_MyVariables(MyVariables *myVariable){

    myVariable->a = NULL;

    myVariable->sum = 0.0;

    myVariable->N = 0;

    myVariable->size = 0;
    
    myVariable->tid = 0;

    return myVariable;

  }

// void *compute(void *arg) {
 
//     //MyVariables *myVariable;
 
//     MyVariables *myVariable=(MyVariables *)arg;
    
//     //init_MyVariables(myVariable);
    
//     int myStart, myEnd, myN, i;

//     myVariable->tid = (long)arg;
   
//     // determine start and end of computation for the current thread
//     myN = myVariable->N/myVariable->size;
//     myStart = myVariable->tid*myN;
//     myEnd = myStart + myN;

//      //printf("This is compute %d ", arg);
//     printf("This is tid %d ", myVariable->tid);

//     //if (myVariable->tid == (myVariable->size-1)) myEnd = myVariable->N;
//     //printf("%d~~~~", myStart);
//     //printf("%d n ", myVariable->N);

//     // compute partial sum
//     double mysum = 0.0;

//     //for (i=myStart; i<myEnd; i++){
//       printf("%f\n", myVariable->a[i]);
//       //mysum += myVariable->a[i];

//      // myVariable->sum = mysum;
//     //}
//     // printf("%f", mysum);
//     // grab the lock, update global sum, and release lock
//      //pthread_mutex_lock(&mutex);
//      //printf("jdfaksfj");
     
//      //pthread_mutex_unlock(&mutex);

//     return (NULL);
// }
void *compute(void *arg) {
  
    int myStart, myEnd, myN, i;

    MyVariables *my = (MyVariables *) arg;

    my->tid = (long)arg;
    //printf("%d ", arg);
    // determine start and end of computation for the current thread
    myN = my->N/my->size;
    myStart = my->tid*myN;
    myEnd = myStart + myN;
    
    if (my->tid == (my->size-1)) myEnd = my->N;

    // compute partial sum
    double mysum = 0.0;
    for (i=myStart; i<myEnd; i++)
      mysum += my->a[i];

    // grab the lock, update global sum, and release lock
    
    my->sum += mysum;
    

    return (NULL);
}

int main(int argc, char **argv) {

    long i;

    double sum=0.0;

    pthread_t *tid;
    if (argc != 3) {
       printf("Usage: %s <# of elements> <# of threads>\n",argv[0]);
       exit(-1);
    }

    int N = atoi(argv[1]); // no. of elements
    int size = atoi(argv[2]); // no. of threads

    MyVariables *my =(MyVariables *) malloc(sizeof(MyVariables)*size);

    // allocate vector and initialize
    tid = (pthread_t *)malloc(sizeof(pthread_t)*size);
    
    //defining each struct for each thread
    for(i = 0; i<size; i++){
      
      my[i].a = (double *)malloc(sizeof(double)*N);
      for (int j=0; j<N; j++)
          my[i].a[j] = (double)(j + 1);

      my[i].N = N;

      my[i].size = size;

      my[i].tid = i;
      

    }

    // create threads. struct arg passed here.
    for ( i = 0; i < size; i++)
        pthread_create(&tid[i], NULL, compute, (void *)&my[i]); 
  
    //printf("This is the where the thread is created %d ", &myVariable[i]);
    // wait for them to complete
    for ( i = 0; i < size; i++)
        pthread_join(tid[i], NULL);

    for(i = 0; i < size; i++)
        sum += my[i].sum;

    printf("The total is %g, it should be equal to %g\n", 
        sum, ((double)N*(N+1))/2);
    
    return 0;
}