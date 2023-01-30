#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*Takes a number and prints out a string based on conditions*/
void intro332532(int n)
{
    int i;
    //iterates tthrough conditions
    for(i=n;i>0;i--)
    {
        if(n%3==0 && n%5==0)
        {
            printf("UAB CS 332&532 \n");//prints if numbers divisible by 3 & 5
        }
        else if(n%5==0)
        {
            printf("UAB \n");//prints if number divisible by 5
        }
        else if(n%3==0)
        {
            printf("CS \n");//prints if numbers divisble by 3
        }
        else if(n%i==1 && n!=3 && n!=5)
        {
            printf("Go Blazers! \n");//this prints if the number except 3 & 5 is prime.
        }
        else
        {
            printf("%.0f \n", powf(n,3));//cubes input number if all other conditions are false.
        }
        break;//stops iteration once condition met
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

/*Check in the value of an array is smaller than its index*/
int smallerThanIndex(int* numbers, int size)
{
    int i;
    int* num = numbers;//for making changes to original array
    int smallInd=0;//stores values smaler than its index

    /*iterates though array to find each number smaller than its index*/
    for(i=0;i<size;i++)
    {
        if(*(num+i)<i)//checks value against its index
        {
            smallInd += 1;//adds 1 for each value smaller than its index
            
        }
    }
    return smallInd;
}

/*Takes an array and returns a new array containing the details of the original array*/
//new array will contain: [size, minValue, minValue index, mean, maxValue, maxValue index]
int* arrayDetails(int *arr, int size)
{
    int i,j,k;
    int *newArr;//new array of details
    int newArrSize = 6;//new array size
    
    newArr=malloc(newArrSize*8);//allocated memory

    int arrSize=size;//stores original array size
    int arrMin;//stores minimum value of original array
    int arrMinInd;//stores minValue index of original array
    double arrMean;//stores mean of original array
    int arrMax;//stores maxValue of original array
    int arrMaxInd;//stores mavValue index of original array

    int temp=(*(arr+0));//constant variable for checking values of array
    int temp2=(*(arr+0));//constant variable for checking values of array

    /*Iterates to find minValue*/
        for(i=0;i<size;i++)
        {   
            if(*(arr+i)<temp)//checks fors minValue
            {
                temp=(*(arr+i));
                arrMin=temp;//stores minValue
                arrMinInd=i;  //stores minValue index

            }
            //Iterates to find maxValue
            for(j=0;j<size;j++)
            {
                if(*(arr+j)>temp2)//checks for minValue
                {
                    temp2=(*(arr+j));
                    arrMax=temp2;//stores minValue
                    arrMaxInd=j;//stores minValue index
                }
            }
        }
        /*Iterates to add values to arrMean variable*/
        for(k=0;k<size;k++)
        {
            arrMean+=(*(arr+k));
        }
        arrMean/=size;//divides by original array size to find mean
        
        /*Add values to newArray array*/
        *(newArr+0)=arrSize;
        *(newArr+1)=arrMin;
        *(newArr+2)=arrMinInd;
        *(newArr+3)=arrMean;
        *(newArr+4)=arrMax;
        *(newArr+5)=arrMaxInd;

        return newArr;
        free(newArr);//frees up allocated memory
    }


