//
//  main.c
//  
//
//  Created by Christopher Jean on 2/3/21.
//
//

#include <stdio.h>
#include "gcd.h"
#include "prime.h"

int main()
{
    //Starting variables
    int a, b;
    float avg;
    
    printf("Please enter two numbers:\n");
    
    //To read both inputs
    scanf("%d", &a);
    scanf("%d", &b);
    
    avg = (float) a + b;
    avg = avg/2.0;
    
    //To print Inputs
    printf("You entered %d and %d\n", a, b);
    
    //To compute the average of both inputs
    printf("The average of these is: %f\n", avg);
    
    //To test whether a is prime
    if (isPrime(a))
    {
        printf("a is a prime number.\n");
    }
    else
    {
        printf("a is NOT a prime number.\n");
    }
    
    //To test whether b is prime
    if (isPrime(b))
    {
        printf("b is a prime number.\n");
    }
    else
    {
        printf("b is NOT a prime number.\n");
    }
    
    //To find the gcd of both a and b
    int gcd = GCD(a, b);
    
    //If gcd = 1, the numbers are coprime i.e relatively prime; otherwise they are NOT
    if (gcd == 1)
    {
        printf("a and b are coprime i.e. relatively prime.\n");
    }
    else
    {
        printf("a and b are NOT coprime i.e. relatively prime.\n");
    }
    
}
