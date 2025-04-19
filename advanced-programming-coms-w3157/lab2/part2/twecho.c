#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void caps(char *input)
{
	char *p = input;//To keep the pointer of input from pointing to the end of character array
	int x;
	while(*p)
	{
		x = (int)*p;
		//To capitalise a lowercase letter
        //Capital and lowercase letters are 32 apart in the ASCII table: https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html
		if (x >= 97 && x <= 122)
		{
			*p = *p - 32;
		}
		p++;
	}
}

static char **duplicateArgs(int argc, char **argv)
{
	//Generates 2D arrays for each argument
	int size = 0;
	
	char **argCopy;
	argCopy = malloc((argc) * sizeof(char *));//i.e. number of arguments * byte size of each pointer

	for (int i = 0; i < argc; i++)
	{
		size = strlen(*argv);//To get the size of the string
		*argCopy = malloc(size);

		if (*argCopy == NULL)
		{
			printf("Error: NULL pointer exception at duplicateArgs");
			exit(1);
		}
		strcpy(*argCopy, *argv);
		caps(*argCopy);//Capitalisation
		argv++;//Next argument from command line
		argCopy++;//Moves pointer to next row
	}
	for (int i = 0; i < argc; i++)
	{
		argCopy--;
	}
	return argCopy;
}

static void freeDuplicatedArgs(char **copy)
{
	char *rows = *copy;
	//Frees all of the strings
	while(*rows)
	{
		free((void *)rows);
		rows++;
	}
	//Frees 2D array
	free((void *)copy);
    //Frees overall array
    free(copy);
}

int main(int argc, char **argv)
{
    if (argc <= 1)
    	return 1;

    char **copy = duplicateArgs(argc, argv);
    char **p = copy;

    argv++;
    p++;
   
    while (*argv) {
        printf("%s %s\n", *argv++, *p++);
    }
    freeDuplicatedArgs(copy);
    return 0;
}
