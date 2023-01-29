#include "hw1.h"

int main()
{   
    intro332532(4);

    printf("UABNumber= %d \n",UABNumber(27));

    printf("reverseNum= %d \n",reverseNum(1234));

    int inp[] = {-1,2,3,5,4};
    int size = 5;
    printf("smallerThanIndex= %d \n",smallerThanIndex(inp,5));

    printf("arrayDetails= [%d] \n",*arrayDetails(inp,size));
}