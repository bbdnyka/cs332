#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compar (const void *a1, const void *a2) {

    // Cast the argument back to the the type we passed in.
    char **arg1 = (char **) a1;
    char **arg2 = (char **) a2;

    // De-reference each value (strcmp() requires each type to be char *)
    if (strcmp(*arg1, *arg2) < 0) {
        return -1;
    } 
    else if (strcmp(*arg1, *arg2) == 0) {
        return 0;
    }
    else if (strcmp(*arg1, *arg2) > 0) {
        return 1;
    }
}

int main(int argc, char **argv) {

    qsort(&argv[1], argc - 1, sizeof(char *), compar);

    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
}