/*
Name:Denyka Brown
BlazerId:browden2
Project #:3
To compile: make
To run: ./hw3 <flag> <file name>
    or  ./hw3 <flag> <size> <file name>
    or  ./hw3 <flag> <substring> <file name>
    or  ./hw3 <flag> <size> <flag> <arg>
*/
/*
  I, __denyka brown_____, 
declare that I have completed this assignment completely and entirely on my own, 
without any unathorized consultation from others or unathorized access to online websites. 
I have read the UAB Academic Honor Code and understand that any breach of the
 UAB Academic Honor Code may result in severe penalties.

Student Signature/Initials: ___db_________

Date: ___12March2023_________

*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
// malloc input for traversal
#define MAX_PATH_SIZE 2000

//cases for file types
char *fileType(unsigned char type){
    char *str;
    switch(type){
        case DT_BLK: str = "block device"; break;
        case DT_CHR: str = "character device"; break;
        case DT_DIR: str = "directory"; break;
        case DT_FIFO: str = "named pipe (FIFO)"; break;
        case DT_LNK: str = "symbolic link"; break;
        case DT_REG: str = "regular file"; break;
        case DT_SOCK: str = "UNIX domain socket"; break;
        case DT_UNKNOWN: str = "unknown file type"; break;
        default: str = "UNKNOWN";
  }
  return str;
}
/*
directory traversal
path name changes with each recurse of directory
*/  
void traverseDir(char* path, int tabSpaces,int flags){
    struct dirent *dtype;// used for d_type
    DIR *parentDir;// used for opendir
    parentDir = opendir(path); /*Open directory */
    /*if file name typed wrong, error prints*/
    if (parentDir == NULL) { 
        printf ("Error opening directory '%s'\n", path); 
        exit (-1);
    }
    int count = 1;
    struct stat *sb = malloc(sizeof(struct stat));
    /*
    read the contents of the directory, file by file.
    */
    while((dtype =readdir(parentDir)) != NULL){ 
        // If the file's name is "." or "..", ignore them. We do not want to infinitely recurse.
        if (strcmp(dtype->d_name, ".") == 0 || strcmp(dtype->d_name, "..") == 0) {
            continue;
        } 
        // Copy pathing to copyPath and concatenate filename to copyPath
        char* copyPath = malloc(MAX_PATH_SIZE);
        strcpy(copyPath, path);
        strcat(copyPath, "/");
        strcat(copyPath,dtype->d_name);

        // add to sb struct
        lstat(copyPath,sb);
        
        /*Empties copyPath after added to sb*/
        // strcpy(copyPath, " ");
        // memset(copyPath,0,strlen(copyPath));

        // "S" argument
        if(flags==1){
        printf("%*s[%d] %s (%s) (Octal Permission: %o, File size: %ld, Access time: %s)\n", 4 * tabSpaces, " ",
        count, dtype->d_name, fileType(dtype->d_type),sb->st_mode, sb->st_size,ctime(&sb->st_atime)); 
            if (dtype->d_type == DT_DIR) {
                // Build the new file path.
                char *subDirPath = (char *) malloc(MAX_PATH_SIZE);
                strcpy(subDirPath, path);
                strcat(subDirPath, "/");
                strcat(subDirPath, dtype->d_name);
                traverseDir(subDirPath, tabSpaces + 1,flags);
                free(subDirPath); 
            }
        }
        // "s" argument
        if(flags==2){
            //printf("s flag = %d\n",flags);
        }
        // "f" argument
        if(flags==3){
            //printf("f flag = %d\n",flags);
        }
        // "e" argument
        if(flags==4){
            //printf("e flag = %d\n",flags);

        }
        // "No directory"
        if(flags== 0){
            printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ",count, dtype->d_name, fileType(dtype->d_type)); 
            //printf();
            if (dtype->d_type == DT_DIR) {
                // Build the new file path.
                char *subDirPath = (char *) malloc(MAX_PATH_SIZE);
                strcpy(subDirPath, path);
                strcat(subDirPath, "/");
                strcat(subDirPath, dtype->d_name);
                traverseDir(subDirPath, tabSpaces + 1,flags);
                free(subDirPath); 
            }
        }
        count++;// count for numbering   
        free(copyPath);
    }
    free(sb);         
}

int main(int argc, char **argv) {
    struct stat sb;// used for stat print
    /* opt = getopt, nsecs = file size, flag1 = S, flag2 = s, flag 3 = f, flag4 = e*/
    int opt,flag1=0,flag2=0,flag3=0,flag4=0;// flags and getop variable
    int tabSpaces = 0;// tabs for traveerseDIR
    char* findSub;
    char* exe;
    int flags=0;
    int size;


    // check flags
    while((opt = getopt(argc, argv, "f:Ss:es:")) != -1){
        //printf("%c\n",opt);
        switch(opt){
           
        // "S" argument List all files in the hierarchy that 1) file name contains substring in string pattern.
        // 2) the depth of the filerelative to starting traversal is <= depth option. (starting directory is 0)
            case 'S':
            flag1=1;
            flags=1;
            break;
        // "s" argument This should list all files in the hierarchy with file size less than or equal to the value 
        // specified
            case 's':
            size = atoi(optarg);
            flag2=1;
            flags-2;
            break;
        // "f" argument 1) the file name contains the substring in the string pattern option, AND 2) the depth of the file 
        // relative to the starting directory of the traversal is less than or equal to the depth option. 
            case 'f':
            findSub = strtok(optarg, " ");
            size = atoi(optarg);
            flag3=1;
            flags=3;
            break;
            // "e" argument
            case 'e':
            flag4=1;
            flags=4;
            break;
        }
    }
    // "S" argument
    if(flag1==1){
        traverseDir(argv[optind],tabSpaces, flags);
    }
    // "s" argument
    if(flag2==1){
        printf("%d Bytes\n",size);
        traverseDir(argv[optind],size,flags);
    }
    // "f" argument
    if(flag3==1){// f
        printf("sub string=%s", findSub);
        traverseDir(argv[optind],size,flags);
    }
    // "e" argument
    if(flag4==1){
        printf("%s", exe);
        
        int status;
        pid_t pid;
        pid = fork();

        if (pid == 0) { /* this is child process */
            execvp(argv[2],argv);/*use array here. Working on this part*/
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
        
        printf("[%ld]: Exiting program .....\n", (long)getpid());
        traverseDir(argv[optind],tabSpaces,flags);
    }
    if (optind == argc) {
        // No directory was specified.
        traverseDir(".", tabSpaces, flags);
    }
    else {
        // A directory was specified.
        traverseDir(argv[argc - 1], tabSpaces, flags);
    }
    return 0;
}



    




    