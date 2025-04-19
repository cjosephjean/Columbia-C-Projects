//
//  prime.c
//  
//
//  Created by Christopher Jean on 2/3/21.
//
//

#include "prime.h"
#include <math.h>

bool isPrime(int a)
{
    double root = sqrt((double) a);
    int ceiling = (int) ceil(root);
    
    //1 is NOT a prime!
    if (a == 1)
    {
        return false;
    }
    
    //2 is the only even prime. Test if it is 2.
    if (a == 2)
    {
        return true;
    }
    
    //If the number is even, and it is NOT 2, it can't be prime.
    if (a % 2 == 0 && a != 2)
    {
        return false;
    }
    
    //Using Sieve of Eristophenes, test for all factors up to square root of N
    int factor = 3;
    while (factor <= ceiling)
    {
        if (a%factor==0)
        {
            return false;
        }
        factor+=2;
    }
    return true;
}
