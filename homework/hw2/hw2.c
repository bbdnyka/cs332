/*I, __denyka brown_____, 
declare that I have completed this assignment completely and entirely on my own, 
without any unathorized consultation from others or unathorized access to online websites. 
I have read the UAB Academic Honor Code and understand that any breach of the
 UAB Academic Honor Code may result in severe penalties.

Student Signature/Initials: ___db_________

Date: ___19february23_________

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
// function for directory traversal    
void traverseDir (char* path, int tabSpaces){
    struct dirent *dirent;// used for d_type
    DIR *parentDir;// used for opendir

    // First, we need to open the directory.
    parentDir = opendir(path);
    // if file name typed wrong, error prints
    if (parentDir == NULL) { 
        printf ("Error opening directory '%s'\n", path); 
        exit (-1);
    }
    int count = 1;
    // After we open the directory, we can read the contents of the directory, file by file.
    while((dirent = readdir(parentDir)) != NULL){ 

        // If the file's name is "." or "..", ignore them. We do not want to infinitely recurse.
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) {
            continue;
        }

    // Print the formated file.
        printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name, fileType(dirent->d_type)); 
    // count for numbering
        count++; 
    }
    
}
int main(int argc, char **argv) {
    char* filename;// stores argv[1]
    struct stat sb;// used for stat print
    int flagS,flags, flagf, opt;// flags and getop variable
    flagS = 0;// [-S]
    flags = 0;// [-s]
    flagf = 0;// [-f]
    int tabSpaces = 0;// tabs for traveerseDIR

// check flags
    while((opt = getopt(argc, argv, "f;Ss;")) != -1){
        //printf("%c\n",opt);
        switch(opt){
           
        // List all files in the hierarchy that 1) file name contains substring in string pattern.
        // 2) the depth of the filerelative to starting traversal is <= depth option. (starting directory is 0)
            case 'S':
        // flagS used to access function ttraverseDIR, stats cases
            flagS = 1;
            break;
        // List files in hierarchy 
            case 's':
        // flags used to access function ttraverseDIR
            flags = 1;
            break;
        // List files in hierarchy
            case 'f':
        // flagf used to access function ttraverseDIR
            flags = 1;
            break;
        // if anything other than implemented flags used, error prints
            default: /* '?' */
                fprintf(stderr, "Usage: %s name [-S] [-s] [-f] \n",*(argv+0));
                exit(EXIT_FAILURE);
            
        }
    // [-S] flag
        if(flagS == 1){
            // nothing entered
            if (stat(*(argv+1), &sb) == -1) {
                    perror("stat");
                    exit(EXIT_FAILURE);
                }
        // stores file name
            filename = argv[1];
        // stores stat info
            long fileMode = 0;
            long fileLink = 0;
            long long fileSize = 0;
            long long fileAccess = 0;
            printf("File type: ");
        // cases for stats
            switch (sb.st_mode & S_IFMT) {
                case S_IFBLK:  printf("block device\n");            break;
                case S_IFCHR:  printf("character device\n");        break;
                case S_IFDIR:  printf("directory\n");               break;
                case S_IFIFO:  printf("FIFO/pipe\n");               break;
                case S_IFLNK:  printf("symlink\n");                 break;
                case S_IFREG:  printf("regular file\n");            break;
                case S_IFSOCK: printf("socket\n");                  break;
                default:       printf("unknown?\n");                break;
                }
        //stats stored
            fileMode = sb.st_mode;
            fileLink = sb.st_nlink;
            fileSize = sb.st_size;
            fileAccess = sb.st_atime;
        //stats printed
            printf("File name: %s (Permission bits: %lo. Files in hierarchy: %ld. File size: %lld bytes. Time accessed: %s.)",filename,fileMode,fileLink,fileSize,ctime(&fileAccess));
            printf("\n");
        //function call for subpaths
            traverseDir(*(argv+1), tabSpaces+1);
            //}
        //exit code to stop compile
            exit(EXIT_SUCCESS);
        }
    // [-s] flag
        if(flags == 1){
    //function call for subpaths 
            traverseDir(*(argv+1), tabSpaces+1);
        } 
    // [-f] flag
        if(flagf == 1){
    //function call for subpaths
            traverseDir(*(argv+1), tabSpaces+1);
        }   
    }
    // Check to see if the user provides at least 2 command-line-arguments.
    if (argc < 2) { 
        printf ("Usage: %s <dirname>\n", *(argv+0)); 
        exit(-1);
    }
    else if(argc > 2){
        printf("Too many arguments.\n");
    }
    else{
        printf("The argument supplied is %s\n", *(argv+1));
    }
// function call for directory and sub paths
    traverseDir(argv[1], tabSpaces+1);
} 





    