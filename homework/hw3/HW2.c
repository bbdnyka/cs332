/* 
Name: Grant Davis
BlazerId: gdavis19
Project #: HW2
To compile: "gcc HW2.c -Wall -o HW2" 
To run: "./HW2 <Flags> <Directory>"
        i.e. "./HW2 -S -s 15000 ~/Desktop"
        i.e. "./HW2 -f ".c 5" -S -t f"
        i.e. "./HW2"
If no directory is specified, defaults to current directory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAX_PATH_SIZE 2000

typedef struct Flags {

    // "S" Argument
    int is1; 

    // "s" Argument
    int is2; 
    int arg2;

    // "f" Argument
    int is3; 
    char *arg3;
    int depth;

    // "t" Argument
    int is4;
    char *arg4;
} Flags;

Flags* init_Flags(Flags *flags) {

    flags->is1 = FALSE;
    flags->is2 = FALSE;
    flags->arg2 = 0;
    flags->is3 = FALSE;
    flags->arg3 = NULL;
    flags->depth = 0;
    flags->is4 = FALSE;
    flags->arg4 = NULL;

    return flags;
} 

int check_File(char *fileName, struct stat *stats, Flags flags, int tabSpaces) {

    // A file can only be disqualified by the "s", "f", and "t" flags.

    // Return TRUE (1) if the file meets all flag criteria (if it should be printed), FALSE (0) otherwise

    // "s" Argument
    if (flags.is2 && !(stats->st_size <= flags.arg2)) {
        return FALSE;
    }
    // "f" Argument
    if (flags.is3 && (strstr(fileName, flags.arg3) == NULL || !(tabSpaces <= flags.depth))) {
            return FALSE;
    }
    // "t" Argument
    if (flags.is4 && (strcmp(flags.arg4, "f") == 0) && ((stats->st_mode & S_IFMT) != S_IFREG)) {
        return FALSE;
    }
    if (flags.is4 && (strcmp(flags.arg4, "d") == 0) && ((stats->st_mode & S_IFMT) != S_IFDIR)) {
        return FALSE;
    }

    return TRUE;
}


typedef void MyFunc_1 (char *fileName, struct stat *stats, int *count, int tabSpaces, Flags flags);

void print_File(char *fileName, struct stat *stats, int *count, int tabSpaces, Flags flags) {

    // The print statement changes only with the S flag.

    if (!flags.is1) {
        printf("%*s[%d] %s\n", 4 * tabSpaces, "", *count, fileName); 
    }
    else {

        // Print 0 for file size if directory.
        if ((stats->st_mode & S_IFMT) == S_IFDIR) {
            printf("%*s[%d] %s %d Bytes, %o, %s\n", 4 * tabSpaces, "", *count, fileName, 0, stats->st_mode & 0777, ctime(&stats->st_mtime)); 
        }
        // Print actual size for everything else.
        else {
            printf("%*s[%d] %s %ld Bytes, %o, %s\n", 4 * tabSpaces, "", *count, fileName, stats->st_size, stats->st_mode & 0777, ctime(&stats->st_mtime));
        } 
    }
    *(count) += 1;
}

// Notice: funcPtr in traverse_Directory is a function pointer.

void traverse_Directory(char *path, int tabSpaces, Flags flags, MyFunc_1 funcPtr) {

    struct dirent *dirent;
    struct stat stats;
    DIR *parentDir;

    if (tabSpaces == 0) {
        printf("Starting Directory: %s\n", path);
    }

    parentDir = opendir(path);
    if (parentDir == NULL) { 
        printf ("Error opening directory '%s'\n", path); 
        exit(-1);
    }

    int count = 1; 
    while((dirent = readdir(parentDir)) != NULL) {

        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) {
            continue;
        }

        // Create path to file
        char *filePath = (char *) malloc(MAX_PATH_SIZE);
        strcpy(filePath, path);
        strcat(filePath, "/");
        strcat(filePath, dirent->d_name);

        // Use stat function to gather info about file (stored in stats variable)
        if (stat(filePath, &stats) == -1) {
            printf("Error with stat '%s\n", filePath);
            exit(-1);
        }

        // Check if the file meets all flag criteria
        if (check_File(dirent->d_name, &stats, flags, tabSpaces)) {
            // Perform action on file
            funcPtr(dirent->d_name, &stats, &count, tabSpaces, flags);
        }

        if (dirent->d_type == DT_DIR) {
            // Traverse subdirectory
            traverse_Directory(filePath, tabSpaces + 1, flags, funcPtr);
        }

        free(filePath);

    }
    closedir(parentDir);
}

int main(int argc, char **argv) {

    int opt;
    Flags flags;

    init_Flags(&flags);

    while ((opt = getopt(argc, argv, "Ss:f:t:")) != -1) {
        switch(opt) {
            case 'S':
                flags.is1 = 1;
                break;
            case 's':
                flags.is2 = 1;
                flags.arg2 = atoi(optarg);
                break;
            case 'f':
                flags.is3 = 1;
                // Tokenize the -f argument (e.g. "zip 3")
                flags.arg3 = strtok(optarg, " ");
                flags.depth = atoi(strtok(NULL, " "));
                break;
            case 't':
                flags.is4 = 1;
                flags.arg4 = optarg;
        }
    }
    if (optind == argc) {
        // No directory was specified.
        traverse_Directory(".", 0, flags, &print_File);
    }
    else {
        // A directory was specified.
        traverse_Directory(argv[argc - 1], 0, flags, &print_File);
    }

    return 0;
}
