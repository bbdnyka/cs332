#include <stdio.h>
#include <math.h>

void intro332532(int n)
{
    int i;
    for(i=n;i>0;i--)
    {
        if(n%3==0 && n%5==0)
        {
            printf("UAB CS 332&532 \n");
        }
        else if(n%5==0)
        {
            printf("UAB \n");
        }
        else if(n%3==0)
        {
            printf("CS \n");
        }
        else if(n%i==0)
        {
            printf("Go Blazers!");
        }
        else
        {
            printf("%f", pow(n,3));
        }
        
        printf("\n");
    }
}
    /*Checks if input is a UAB NUmber*/
    int* UABNumber(int n2)
    {
        printf("Enter a number here: ");
        scanf("%d", &n2);
        int divisors ;
        int array[1000];
        int temp;
        int i,j;

        divisors=j=0;

        /*Iterates through input number and determines which numbers are divisors or the input*/
        for(i=1;i<n2;i++)
        {
          
        
          if(n2 % i==0)
          {
            

            array[j]=i;
            divisors += i;
            printf("%d ", array[j]);
            j++;
            
          }
          
        }
        printf("\n"); 
        printf("%d" ,array); 
        return 0;
    }
