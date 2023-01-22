#include <stdio.h>
/*Program checks if a number is prime. */

/*isPrime function checks if a given number is Prime. */
int isPrime(int givenNumber)
{
    /* scanf() used to get value in givenNumber.*/
    int i;
    printf("Enter your dang number: ");
    scanf("%d", &givenNumber);
    /*for loop checks given number for prime */
    if(givenNumber<1)
    {
        printf("Not prime!");
        return 0;
    }
    for(i=givenNumber-1;i>0;i--)
    {
        if(givenNumber%i==0)
        {
            printf("This given number is not Prime. \n");
            return 0;
        }
    }
    printf("Is prime!");
    return 0;
}
