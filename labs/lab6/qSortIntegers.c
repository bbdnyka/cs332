#include <stdio.h>
#include <stdlib.h>


int compar(const void *a1, const void *a2) {

    // Cast back to integer pointers.
    int *arg1 = (int *) a1;
    int *arg2 = (int *) a2;

    if (*arg1 < *arg2) {
        return -1;
    }
    else if (*arg1 == *arg2) {
        return 0;
    }
    else if (*arg1 > *arg2) {
        return 1;
    }
}

int main() {

    // Initialize the array.
    int arr[7] = {5, 3, 6, 8, 3, 4, 1};

    // Call qsort on the array.
    qsort(arr, 7, sizeof(int), compar);

    // Print the array.
    for (int i = 0; i < 7; i++) {
        printf("%d ", arr[i]);
    }
}