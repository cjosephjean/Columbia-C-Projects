//
//  mylist.c
//  
//
//  Created by Christopher Jean on 3/1/21.
//
//

#include <stdio.h>
#include <stdlib.h>
#include "mylist.h"


//Create a node holding the given data pointer and add node to the front of the list
struct Node *addFront(struct List *list, void *data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("addFront: ERROR MALLOC");
        exit(1);
    }
    
    (*newNode).data = data;
    
    struct Node *currentHead = list -> head;
    if(currentHead == NULL)
    {
        (*newNode).next = NULL;
        (*list).head = newNode;
        return newNode;
    }
    
    (*newNode).next = currentHead;
    (*list).head = newNode;
    return newNode;
}


//Traverse the list and call f() with each item of data
void traverseList(struct List *list, void (*f)(void *))
{
    struct Node *currentNode = list -> head;
    while (currentNode)
    {
        f((*currentNode).data);
        currentNode = (*currentNode).next;
    }
}


//Flip the sign of the double data points to by first multipying by -1 and placing the result in the memory location
void flipSignDouble(void *data)
{
    double value = (*(double *)data) * -1.0;
    *(double *)data = value;
}


//Compare two doubles pointed two by two pointers then return 0 if they are the same and 1 if not
int compareDouble(const void *data1, const void *data2)
{
    double a = *((double *) data1);
    double b = *((double *) data2);
    if (a == b)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


//Traverse the list and use compar to compare each item of data with dataSought
//Return the first node with matching data and NULL if not found
struct Node *findNode(struct List *list, const void *dataSought, int (*compar)(const void *, const void *))
{
    struct Node* current = list -> head;
    
    while (current)
    {
        if (compar((*current).data, dataSought) == 0)
        {
            return current;
        }
        current = current -> next;
    }
    return 0;
}


//Remove the first node from the list, deallocate memory for the node, and return the pointer (i.e. data) stored in the node
void *popFront(struct List *list)
{
    if (isEmptyList(list) == 1)
    {
        return NULL;
    }
    struct Node *head = list -> head;
    void *data = (*head).data;
    
    (*list).head = (*head).next;
    
    free(head);
    return data;
}


//Remove and deallocate memory for all nodes
void removeAllNodes(struct List *list)
{
    while (isEmptyList(list) == 0)
    {
        popFront(list);
    }
}


//Create a node holding the given data pointer and add it after the node passed in as prevNode parameter
//Function is equivalent to addFront() if prevNode is NULL
struct Node *addAfter(struct List *list, struct Node *prevNode, void *data)
{
    struct Node *newNode;
    if (prevNode == NULL)  
    {    
        newNode = addFront(list,data);
        return newNode;
    }
         
    newNode = (struct Node *) malloc(sizeof(struct Node));
        
   
    struct Node *oldNext = prevNode -> next;
    
    (*newNode).data = data;
    
    (*prevNode).next = newNode;
    
    (*newNode).next = oldNext;
    return newNode;  
}

//Reverse the list through modification of pointers
void reverseList(struct List *list)
{
      struct Node *prv = 0;
      struct Node *cur = list -> head;
      struct Node *next;

      while (cur)
      {
          if (cur == list -> head)
          {
              next = cur -> next;
              (*cur).next = prv;
              prv = list -> head;
              cur = next;
              continue;
          }
          
          next = cur -> next;
          (*cur).next = prv;
          prv = cur; 

          cur = next;
      }
      (*list).head = prv;
}
