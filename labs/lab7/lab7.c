#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

#define LINESIZE 1024
/*
To compile: make 
To run: ./lab7 File1.txt
*/
int main(char argc, char **argv){
	char line[LINESIZE];
	char* str;
	int i, status;
	pid_t pid;
	time_t before;
	time_t after;

	FILE *fptr = fopen(argv[1], "r");
	if(fptr == NULL){
		printf("Error reading input file %s\n",argv[1]);
		exit (-1);
	}
	int count =1;
	while (fgets(line, LINESIZE, fptr) != NULL){
		//printf("%ld:%s",strlen(line), line);
		char* strArray = malloc(LINESIZE);
		str=strtok(line," \n");
		if(str!=NULL){
		 	strcpy((strArray+0),str);
		}
		while(str!=NULL){
			//printf("%s",str);
			str=(strtok(NULL, " \n"));
			if(str!=NULL){
		 		strcpy((strArray+count),str);
				count ++;
		  	}
		}
		if (argc < 2) {
        	printf("Usage: %s <command> [args]\n", argv[0]);
        	exit(-1);
    }
	time (&before);
	//printf("%s",ctime(&before));
    pid = fork();

    if (pid == 0) { /* this is child process */
        execvp((strArray+0),&strArray);/*use array here. Working on this part*/
        printf("If you see this statement then execl failed ;-(\n");
		perror("execvp");
		exit(-1);

    } 
	else if (pid > 0) { /* this is the parent process */
        //char name[BUFSIZ];
       // printf("[%d-stdout]: Hello %s!\n", getpid(), name);
        //fprintf(stderr, "[%d-stderr]: Hello %s!\n", getpid(), name);

        wait(&status); /* wait for the child process to terminate */
        if (WIFEXITED(status)) { /* child process terminated normally */
            printf("Child process exited with status = %d\n", WEXITSTATUS(status));
			time (&after);
			//printf("%s",ctime(&after));
        } 
		else { /* child process did not terminate normally */
            printf("Child process did not terminate normally!\n");
            /* look at the man page for wait (man 2 wait) to determine
               how the child process was terminated */
        }
	}
	else { /* we have an error */
		perror("fork"); /* use perror to print the system error message */
		exit(EXIT_FAILURE);
    }
	printf("%s%s%s",line, ctime(&before), ctime(&after));
    //printf("[%ld]: Exiting program .....\n", (long)getpid());

    
}
fclose(fptr);		
return 0;		
}
	
	

