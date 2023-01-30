#include "hw1.h"

int main()
{  
    /*intro332532*/ 
    intro332532(30);

    /*UABNumber*/ 
    printf("UABNumber= %d \n",UABNumber(0));

    /*reverseNum*/
    printf("reverseNum= %d \n",reverseNum(29));

    /*smallerThanIndex*/
    int inp1[]= {1,2,0,44,29,309};
    int inp1Size = 6;
    printf("smallerThanIndex= %d \n",smallerThanIndex(inp1,inp1Size));

    /*arrayDetails*/
    int inp[] = {-8,-23,18,103,0,1,-4,631,3,-41,5};
    int size = 11;
    int i;
    int* ptr;
    ptr=arrayDetails(inp,size);
    printf("arraydetails= [");

    /*Iterates to print out each array element*/
    for(i=0;i<6;i++)
    {
        printf(" %d ",*(ptr+i));
    }
    printf("] \n");

}