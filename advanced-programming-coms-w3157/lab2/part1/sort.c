#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

/*
FindMin changes the pointer of *array to point to the minimum value and iterates until it is out-of-bounds
*/

void findMin(int *min, int *BOUND1)
{
	if (min == NULL)
	{
		printf("NULL pointer exception at findMin");
		exit(1);
	}

	//Temp traverses the array to find the minimum value
	int *temp = min;
	temp++;

	while(temp != BOUND1) //Equivalent to while(temp != NULL)
	{
		if(*min > *temp)
		{
			swap(temp,min);	
		}
		temp++;
	}
}

/*
FindMax changes the pointer of *array to point to the maximum value and iterates until it is out-of-bounds
*/

void findMax(int *max, int *BOUND2)
{
	if (max == NULL)
	{
		printf("NULL pointer exception at findMax");
		exit(1);
	}
	
	//Temp traverses the array to find the maximum value
	int *temp = max;
	temp++;

	while(temp != BOUND2) //Equivalent to while(temp != NULL)
	{
		if(*max < *temp)
		{	
			swap(temp,max);
		}
		temp++;
	}
}

/*
Swap switches the integer values in from and to assuming that they both point to the same array
*/
void swap(int *from, int *to)
{
	int x = *from;
	int y = *to;
	*from = y;
	*to = x;
}

/*
 * To sort the array, starting from array[0], traverse from left to right while swapping minimum or maximum values
 * Note that both sortAscending and sortDescending include the same Insertion Sort algorithm
*/

//Sorting by passing in &array[0] and &array[n]
void sortAscending(int *start, int *end)
{
	int *min = start;
	while(start != end)
	{
		findMin(min, end);
		swap(min, start);
		start++;
		min = start;
	}
}

//Sorting by passing in &array[0], &array[n]
void sortDescending(int *start, int *end)
{
	int *max = start;
	while(start != end)
	{
		findMax(max, end);
		swap(max, start);
		start++;
		max = start;
	}
}
