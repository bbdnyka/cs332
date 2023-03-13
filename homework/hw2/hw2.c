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
        /*
        copy of path
        concatenate file name to copyPath
        (HW2/file name )
        */
        char* copyPath = malloc(MAX_PATH_SIZE);
        strcpy(copyPath, path);
        strcat(copyPath, "/");
        strcat(copyPath,dtype->d_name);
        lstat(copyPath,sb); /*copyPath added to sb*/ 
        /*Empties copyPath after added to sb*/
        // strcpy(copyPath, " ");
        // memset(copyPath,0,strlen(copyPath));
        // file format
        if(flags==1){// S
        printf("%*s[%d] %s (%s) (Octal Permission: %o, File size: %ld, Access time: %s)\n", 4 * tabSpaces, " ",
        count, dtype->d_name, fileType(dtype->d_type),sb->st_mode, sb->st_size,ctime(&sb->st_atime)); 
        }
        if(flags==2){// s
            printf("s flag = %d\n",flags);
            break;
        }
        if(flags==3){// f
            printf("f flag = %d\n",flags);
            break;
        }
        break;
        if(flags== 0){// no dir spec
            printf("no directory specified. flag = %d\n",flags);
            printf();
            break;
        }
        count++;// count for numbering   
    
// Check to see if the file type is a directory. If it is, recursively call traverseDirectory on it.
        if (dtype->d_type == DT_DIR) {
            // Build the new file path.
            char *subDirPath = (char *) malloc(MAX_PATH_SIZE);
            strcpy(subDirPath, path);
            strcat(subDirPath, "/");
            strcat(subDirPath, dtype->d_name);
            traverseDir(subDirPath, tabSpaces + 1,flags);
            free(subDirPath); 
        }
        free(copyPath);
    }
    free(sb);       
}
int main(int argc, char **argv) {
    struct stat sb;// used for stat print
    /* opt = getopt, nsecs = file size, flag1 = S, flag2 = s, flag 3 = f */
    int opt,flag1=0,flag2=0,flag3=0;// flags and getop variable
    int tabSpaces = 0;// tabs for traveerseDIR
    char* fin;
    int flags = 0;
    int size;


    // check flags
    while((opt = getopt(argc, argv, "f:Ss:")) != -1){
        //printf("%c\n",opt);
        switch(opt){
           
        // List all files in the hierarchy that 1) file name contains substring in string pattern.
        // 2) the depth of the filerelative to starting traversal is <= depth option. (starting directory is 0)
            case 'S':
            flag1=1;
            break;
        // This should list all files in the hierarchy with file size less than or equal to the value 
        // specified
            case 's':
            size = atoi(optarg);
            flag2=1;
            break;
        // 1) the file name contains the substring in the string pattern option, AND 2) the depth of the file 
        // relative to the starting directory of the traversal is less than or equal to the depth option. 
            case 'f':
            fin = strtok(optarg, " ");
            flag3=1;
            break;
        }
    }
    if(flag1==1){// S
        traverseDir(argv[optind],tabSpaces, flags+1);
    }
    if(flag2==1){// s
        printf("%d Bytes\n",size);
        traverseDir(argv[optind],tabSpaces,flags+2);
    }
    if(flag3==1){// f
        printf("%s = ", fin);
        traverseDir(argv[optind],tabSpaces,flags+3);
    }
    else{
        flags=0;
    }
    if (optind == argc) {
        // No directory was specified.
        traverseDir(".", tabSpaces, flags);
    }
    else {
        // A directory was specified.
        traverseDir(argv[argc - 1], tabSpaces, flags);
    }
}



    




    