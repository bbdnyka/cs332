#include "lab2.h"

int main()
{
    //Ask for user input for array size.
    printf("How big is this array? \n");
    int i;
    int count = 0;
    
    //User inputs array size for selection sorting
    scanf("%d",&count); 
    int arr4[count];

    //For loop gets user's input for each element
    for(i = 0;i<count;i++)
    {
        printf("Type a number here: ");
        scanf("%d",(arr4+i));
    }

    //for loop prints out unsorted input.
    int h;
    printf("Unsorted Input: \n");
    for(h=0;h<count;h++)
    {
        printf("%d ",*(arr4+h));
    }

    printf("\n");

    //for loop prints out insertion sorted input.
    insertionSort(arr4,count);
    int j;
    printf("Insertion sorted input: \n");
    for(j=0;j<count;j++)
    {
        printf("%d ",*(arr4+j));
    }
}

