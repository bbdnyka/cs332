/*
I, __Denyka Brown_____, declare that I have completed this assignment completely and entirely on my own, without any unathorized consultation from others or unathorized access to online websites. I have read the UAB Academic Honor Code and understand that any breach of the UAB Academic Honor Code may result in severe penalties.

Student Signature/Initials: ___DBB_________

Date: _____6APRIL2023_______

 * To Compile: gcc -Wall -O hw4.c -lpthread -o hw4 
 * To Run: ./hw4 commands.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int nthreads;

/* create the queue data structure and initialize it */
queue *queue_init(int n) {
	queue *q = (queue *)malloc(sizeof(queue));
	q->size = n;
	q->buffer = malloc(sizeof(int)*n);
	q->start = 0;
	q->end = 0;
	q->count = 0;
	return q;
}
/* insert an item into the queue, update the pointers and count, and
   return the no. of items in the queue (-1 if queue is null or full) */
int queue_insert(queue *q, int item) {
	if ((q == NULL) || (q->count == q->size))
	   return -1;

	q->buffer[q->end % q->size] = item;	
	q->end = (q->end + 1) % q->size;
	q->count++;

	return q->count;
}
/* delete an item from the queue, update the pointers and count, and 
   return the item deleted (-1 if queue is null or empty) */
int queue_delete(queue *q) {
	if ((q == NULL) || (q->count == 0))
	   return -1;

	int x = q->buffer[q->start];
	q->start = (q->start + 1) % q->size;
	q->count--;

	return x;
}
/* display the contents of the queue data structure */
void queue_display(queue *q) {
	int i;
	if (q != NULL && q->count != 0) {
		printf("queue has %d elements, start = %d, end = %d\n", 
			q->count, q->start, q->end);
		printf("queue contents: ");
		for (i = 0; i < q->count; i++)
	    		printf("%d ", q->buffer[(q->start + i) % q->size]);
		printf("\n");
	} else
		printf("queue empty, nothing to display\n");
}

/* delete the queue data structure */
void queue_destroy(queue *q) {
	free(q->buffer);
	free(q);
}
void *compute(void *arg) {
  long tid = (long)arg;

  printf("Hello, I am thread %ld of %d\n", tid, nthreads);

  return (NULL);
}


int main(int argc, char **argv) {
    queue *q;

    long i;

    pthread_t *tid;

    /* create a queue data structure */
	queue *q = malloc(queue_init(q->size));
    nthreads = atoi(argv[1]); // no. of threads

    if (argc != 2) {
        printf("Usage: %s <arg>>\n",argv[0]);
        exit(-1);
    }
    
    // allocate vector and initialize
    tid = (pthread_t *)malloc(sizeof(pthread_t)*nthreads);

    // create threads
    for ( i = 0; i < nthreads; i++)
        
        pthread_create(&tid[i], NULL, compute, (void *)i);

        //queue up
    /* insert 5 items to the queue */
	for (i = 0; i < 5; i++) {
	    queue_insert(q, 100+i);
	    queue_display(q);
	}
	/* delete 5 items from the queue */
	for (i = 0; i < 5; i++) {
	    queue_delete(q);
	    queue_display(q);
	}
	/* delete the queue */
	queue_destroy(q);

    // wait for them to complete
    for ( i = 0; i < nthreads; i++)
        pthread_join(tid[i], NULL);
        
    printf("Exiting main program\n");


return 0;

}