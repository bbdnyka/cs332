#include <stdio.h>
/*Write a program that takes a user input for array size and elements and implements insertion sort.*/

int* insertionSort(int arr[], int size)
{
    int i;
    int j;
    int key;//used to check elements

    //For loop iterates through array size to add current element to key.
    for(i=1;i<size;i++)
    {
        //key = current element
        key=*(arr+i);
        //j = element to left
        j=i-1;

    //while loop iterates until falsee
    while(j>=0 && key< *(arr+j))
    {   
        //switches element on right to left while statement true.
        *(arr+j+1) = *(arr+j);
        j-=1;
    }
    //if statement false, switches with current.
    *(arr+j+1)=key;
    }
    //Returns sorted array.
    return arr;
}

    
