/*
I, __Denyka Brown_____, declare that I have completed this assignment completely and entirely on my own, without any unathorized consultation from others or unathorized access to online websites. I have read the UAB Academic Honor Code and understand that any breach of the UAB Academic Honor Code may result in severe penalties.

Student Signature/Initials: ___DBB_________

Date: _____6APRIL2023_______

 * To Compile: gcc -Wall -O hw4.c -lpthread -o hw4 
 * To Run: ./hw4 <command> <# of processes>
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include "queue.h"
#include <sys/wait.h>
#include <fcntl.h>


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
		//printf("queue contents: ");
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

	int fdOUT, fdERR;
	//buffer for output and error files
	char* buffer_out = malloc(sizeof(char)*BUFSIZ);
    char* buffer_err = malloc(sizeof(char)*BUFSIZ);
    
    if (argc != 3) {
        printf("Usage: %s <command> <#>\n",argv[0]);
        exit(-1);
    }
    if(strcmp(argv[1],"submit")==0){
		
		nthreads = atoi(argv[2]); // no. of threads based on args

		/* create a queue data structure */
		q = queue_init(sizeof(pthread_t)*nthreads);

		// initialize thread ids
		tid = (pthread_t *)malloc(sizeof(pthread_t)*nthreads);

		//get jobid to write to files
		sprintf(buffer_out, "%d.out", getpid()); /* adds pid to .out*/
		sprintf(buffer_err, "%d.err", getpid());/* adds pid to .err*/

		/* creates <jobid>.out as a write file*/
		if ((fdOUT = open(buffer_out, O_CREAT | O_WRONLY, 0755)) == -1) {
				printf("Error opening file stdout.txt for output\n");
				exit(-1);
		} 
		/* creates <jobid>.err as a write file*/
		if ((fdERR = open(buffer_err, O_CREAT | O_WRONLY, 0755)) == -1) {
				printf("Error opening file stdout.txt for output\n");
				exit(-1);
		}
		/* copies file descriptors to fdOUT and fdERR files*/
		dup2(fdOUT,1); 
		dup2(fdERR,2);

		printf("This is submit command. \n");
		printf("For creating processes and outputing with jobid.\n");
		// create threads
		for ( i = 0; i < nthreads; i++)
			
			pthread_create(&tid[i], NULL, compute, (void *)i);
		//queue up
		/* insert items to the queue */
		for (i = 0; i < nthreads; i++) {
			if (queue_insert(q, nthreads+i) != -1)
				queue_display(q);
			else
			printf("queue full, insertion failed!\n");
		}
		/* delete items from the queue */
		for (i = 0; i < nthreads; i++) {
			if (queue_delete(q) != -1) 
				queue_display(q);
			else
			printf("queue empty, deletion failed!\n");
		}
		/* delete the queue */
		queue_destroy(q);

		// wait for them to complete
		for ( i = 0; i < nthreads; i++)
			pthread_join(tid[i], NULL);
			
		printf("Exiting main program\n");
	}
	if(strcmp(argv[1],"showjobs")==0){
		
		//get jobid to write to files
		sprintf(buffer_out, "%d.out", getpid()); /* adds pid to .out*/
		sprintf(buffer_err, "%d.err", getpid());/* adds pid to .err*/

		/* creates <jobid>.out as a write file*/
		if ((fdOUT = open(buffer_out, O_CREAT | O_WRONLY, 0755)) == -1) {
				printf("Error opening file stdout.txt for output\n");
				exit(-1);
		} 
		/* creates <jobid>.err as a write file*/
		if ((fdERR = open(buffer_err, O_CREAT | O_WRONLY, 0755)) == -1) {
				printf("Error opening file stdout.txt for output\n");
				exit(-1);
		}
		/* copies file descriptors to fdOUT and fdERR files*/
		dup2(fdOUT,1); 
		dup2(fdERR,2);
		printf("This is for showjobs command.\n");
		printf("For showing jobs that are waiting and their times along with their jobid.\n");
	}
return 0;

}