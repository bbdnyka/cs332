#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
        else if(n%i==1)
        {
            printf("Go Blazers! \n");
        }
        else
        {
            printf("%.0f \n", powf(n,3));
        }
        break;
        printf("\n");
    }
}
    /*Checks if input is a UAB NUmber*/
    int UABNumber(int n2)
    {
        printf("Enter a number here: ");
        scanf("%d", &n2);
        int divisors=0 ;
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
          if(divisors==n2)//If equal returns true(1)
          {
            return 1;
          } 
          else{//if not equal returns false(0)
            return 0;
          }
        }
    }
    /*Take a number and returns the reverse. */
    int reverseNum(int n3)
    {
    int i;
    int temp;
    int reverse;
    int a = n3;
        /*Iterates through given number until it equals 0.*/
         while(a!=0)
        {
            temp = a%10;//gets individual nums through iterations
            reverse=reverse * 10 +temp;//iterate through different place values and adds temp
            a = a/10;//decrements a until 0 for counter;
        }
    return reverse;
    }

    int smallerThanIndex(int* numbers, int size)
    {
        int i;
        int* num = numbers;
        int smallInd=0;
        for(i=0;i<size;i++)
        {
            if(*(num+i)<i)
            {
                smallInd += 1;
                
            }
        }
        return smallInd;
    }
    int* arrayDetails(int *arr, int size)
    {
        int i,j,k;
        int *newArr;
        int newArrSize = 6;
        
        newArr=malloc(newArrSize*8);

        int arrSize=size;
        int arrMin;
        int arrMinInd;
        double arrMean;
        int arrMax;
        int arrMaxInd;

        int temp=arr[0];
        int temp2=arr[0];
            for(i=0;i<size;i++)
            {   
                if(arr[i]<temp)
                {
                    temp=arr[i];
                    arrMin=temp;
                    arrMinInd=i;  

                }
            for(j=0;j<size;j++)
                {
                    arr[j];
                    if(arr[j]>temp2)
                    {
                        temp2=arr[j];
                        arrMax=temp2;
                        arrMaxInd=j;
                    }
                }
            for(k=0;k<size;k++)
                {
                    arrMean+=arr[k];
                }
                arrMean/=arrSize;
            }
            *(newArr+0)=arrSize;
            *(newArr+1)=arrMin;
            *(newArr+2)=arrMinInd;
            *(newArr+3)=arrMean;
            *(newArr+4)=arrMax;
            *(newArr+5)=arrMaxInd;

            /*printf("%d \n", arrSize);
            printf("%d \n", arrMin);
            printf("%d \n", arrMinInd);
            printf("%d \n", arrMax);
            printf("%d \n", arrMaxInd);
            printf("%d \n", arrMean);*/
            return newArr;
            free(newArr);
        }

    
