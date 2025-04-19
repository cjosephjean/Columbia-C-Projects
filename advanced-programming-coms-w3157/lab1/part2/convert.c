//
//  convert.c
//  
//
//  Created by Christopher Jean on 2/3/21.
//
//

#include <stdio.h>

int main()
{
    int a;
    
    scanf("%d", &a);

    printf("signed dec:   %d\n", a);
    
    printf("unsigned dec: %u\n", a);
    
    printf("hex:          %x\n", a);
    
    printf("binary:       ");
    
    for (int i=31; i>=0; i--)
    {
        printf("%d", (a>>i) & 1);
    
        if (i % 4==0)
        
            printf(" ");
    }
    printf("\n");
    
    return 0;
}
