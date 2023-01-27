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
    int UABNumber(int n2)
    {
        printf("Enter a number here: ");
        scanf("%d", &n2);
        int divisors=0 ;
        int inputTrue = 0;
        int inputFalse = 0;
        int i;

        /*Iterates through input number and determines which numbers are divisors or the input*/
        for(i=1;i<n2;i++)
        {
          if(n2 % i==0)//input divisors added to variable divisors
          {  
            divisors += i;
          } 
        }
        /*Checks if number stored in divisor is equal to input number */
        for(i=divisors;i>0;i--)
        {
          if(divisors==n2)//If equal returns true
          {
            inputTrue+=1;
            printf("%d \n", inputTrue);
            return 1;
          } 
          else{//if not equal returns false
            printf("%d \n", inputFalse);
            return 0;
          }
        }
    }
    /*Take a number and returns the reverse. */
    int reverseNum(int n3)
    {
    int size = sizeof(n3);
    int revNums[size];
    int i;
    
        /*iterates through given number and adds individuals nums to size*/
        for(i=0;i<n3;i++)
        {
            revNums+= *(revNums+i);
        } 
        printf("%ls", revNums);
    }
    
