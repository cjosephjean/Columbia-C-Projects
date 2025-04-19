//
//  gcd.c
//  
//
//  Created by Christopher Jean on 2/3/21.
//
//



//The following code was found at: https://www.geeksforgeeks.org/c-program-find-gcd-hcf-two-numbers/ and https://www.programiz.com/c-programming/examples/hcf-gcd

// C program to find GCD of two numbers
#include "gcd.h"
 
// Recursive function to return gcd of a and b
int GCD(int a, int b)
{
    // Everything divides 0 
    if (a == 0)
    {
       return b;
    }
    if (b == 0)
    {
       return a;
    }

    while(a!=b)
    {
        if(a > b)
        {
            a -= b;
        }
        else
        {
            b -= a;
        }
    }
    return a;
}
