//I, __Denyka Brown_____, declare that I have completed this assignment completely and entirely on my own, 
//without any unathorized consultation from others or unathorized access to online websites. 
//I have read the UAB Academic Honor Code and understand that any breach of the UAB Academic
// Honor Code may result in severe penalties.

// Student Signature/Initials: ___DB_________

// Date: ____15February2023________

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define	BUFFSIZE 4096

int main(int argc, char *argv[]) {
	int  readFileDescriptor, writeFileDescriptor;
	long int n;
	char buf[BUFFSIZE];
	
	if (argc != 3){
		printf("Usage: %s <source_filename> <destination_filename>\n", argv[0]);
		exit (-1);
	}
	
	readFileDescriptor = open(argv[1], O_RDONLY);
	writeFileDescriptor = open(argv[2], O_CREAT|O_WRONLY|O_APPEND, 0700);
	
	if (readFileDescriptor == -1 || writeFileDescriptor == -1){
		printf("Error with file open\n");
		exit (-1);
	}
	
	if(strcmp(argv[1],argv[2])==0){
		printf("Error with similar file name.");
	}

	while ((n = read(readFileDescriptor, buf, BUFFSIZE)) > 0){
		if (write(writeFileDescriptor, buf, n) != n){
			printf("Error writing to output file\n");
			exit (-1);
		}
	}
	if (n < 0){
		printf("Error reading input file\n");
		exit (-1);
	}

	close(readFileDescriptor);
	close(writeFileDescriptor);

	return 0;
	
}