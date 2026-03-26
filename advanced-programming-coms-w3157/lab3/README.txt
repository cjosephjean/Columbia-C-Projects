Christopher Jean
cjj2126
Lab 3

Part 1:
My code works exactly as specified in the lab. I implemented a generic linked
list in C using void * data pointers, supporting addFront, addAfter, popFront,
removeAllNodes, traverseList, findNode, flipSignDouble, compareDouble, and
reverseList. The reverseList function reverses the list purely through pointer
manipulation without calling malloc.

Part 2:
My code works exactly as specified in the lab. revecho.c uses the linked list
from Part 1 to add command-line arguments to the front of the list, then
traverses and prints them (producing reverse order). It searches for the string
"dude" using findNode with strcmp passed as a function pointer, and reports
whether it was found. All nodes are freed via removeAllNodes before exit.
