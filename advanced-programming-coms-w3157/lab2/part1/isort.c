#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"sort.h"

void generateArray(int size, int * array)
{
    for (int i = 0; i < size;i++)
    {
        array[i] = random()%100;
    }
}

void printArray(int size, int * array)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d", array[i]);
		printf(" ");
	}
}

/* This function sorts an integer array.
 
   begin points to first element of the array.
   end points to ONE PAST the last element of the array.

   If ascending is 1, the array will be sorted in ascending order.
   If ascending is 0, the array will be sorted in descending order.
*/
void sort_integer_array(int *begin, int *end, int ascending)
{
	/* In here, you will call your real sorting function (your own
	 * or qsort()). Basically I want you to make sure that you
	 * know how to translate the begin/end parameter to whatever
	 * is required for your sorting function.
	*/
	if (ascending == 1)
	{
		sortAscending(begin, end);	
	}
	else
	{
		sortDescending(begin, end);
	}
}

int main()
{
	int size;
	int *generateRandom;
	int *sortAsc;
	int *sortDesc;

    //Sets the random number generator to NULL
	srandom(time(NULL));

	printf("Please insert the size of the array to be generated:\n");
	scanf("%d", &size);

	//Initialises the array with random integers
	generateRandom = malloc(size * sizeof(int));
    
	if(generateRandom == NULL)
	{
		perror("malloc returned NULL: generateRandom");
		exit(1);
	}
	generateArray(size, generateRandom);
	
	//Generates the arrays to be sorted
	sortAsc = malloc(size * sizeof(int));
	sortDesc = malloc(size * sizeof(int));

	if (sortAsc == NULL)
	{
		perror("malloc returned NULL: sortAsc");
		exit(1);
	}
	if (sortDesc == NULL)
	{
		perror("malloc returned NULL: sortDesc");
		exit(1);
	}
	
//Copies the original to arrays to be sorted
	memcpy(sortAsc, generateRandom, size * sizeof(int));
	memcpy(sortDesc, generateRandom, size * sizeof(int));
	

//To sort in ascending order
	int *begin = &sortAsc[0];//Points to the first element of the array
	int *end = begin;
	end += size;//Points to the last element i.e. (NULL)
	sort_integer_array(begin, end, 1);
	
    //To sort in descending order
	begin = &sortDesc[0];//Points to the first element of the array
	end = begin;
    end += size;//Points to the last element i.e. (NULL)
	sort_integer_array(begin, end, 0);


    //To print the outputs of all of the arrays
	printf("Original array: ");
	printArray(size, generateRandom);
	printf("\n");

	printf("Array in ascending order: ");
	printArray(size, sortAsc);
	printf("\n");
	
	printf("Array in descending order: ");
	printArray(size, sortDesc);
	printf("\n");
		
	//To free all of the arrays
	free(generateRandom);
	free(sortAsc);
	free(sortDesc);

	return 0;
}
