//
//  revecho.c
//  
//
//  Created by Christopher Jean on 3/1/21.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "mylist.h"

void static printString(void *p)
{
    printf("%s\n", (char *)p);
}

int main(int argc, char **argv)
{
    char *find = "dude";
    bool dudeFound = false;
    
    //Note: Code from Jae's Part 1 skeleton code
    struct Node *node;
    
    struct List list;
    initList(&list);
      
    argv++;
     
    while(*argv)
    {
        addFront(&list, (void *)*argv);
        printf("start: %s\n", *argv);
        argv++;
    }
    
    //Note: Textbook Page 119
    node = findNode(&list, (void *)find, (int (*)(const void*, const void*)) &strcmp);
    if (node != NULL)
    {
        dudeFound = true;
    }

    //Mitigate leaks, print
    traverseList(&list, printString);
    printf("\n");

    //If dude was(not) found:
    if(dudeFound)
    {
        printf("%s found\n", find);
    }
    else
    {
        printf("%s not found\n", find);
    }
    
    //Free everything
    removeAllNodes(&list);
    return 0;
}
