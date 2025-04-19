
/*
 * mdb-lookup-server-nc-2.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

static void die(const char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char **arg)
{
    char buffer [1000];
    char input [33]; // Port numbers are limited to size of ints.
    int portNumber = 0;
    pid_t pid;

    printf("port number: ");
    while(fgets(buffer, sizeof(input), stdin) != NULL)
    {
        //This will be the Parent PID...
        pid = getpid();
        fprintf(stderr, "port number: ");
        
        pid_t childPID = waitpid((pid_t)-1, NULL, WNOHANG);
        while(childPID > 0)
        {
            // Keep Looping in case you have 2+ children that
            // have died
            fprintf(stderr, "[pid=%d] ", (int) childPID);
            fprintf(stderr, "mdb-lookup-server terminated\n");
            childPID = waitpid((pid_t)-1, NULL, WNOHANG);
        }

        // Copy 32 bytes from stdin
        // See if it can be turned to an integer
        input[strlen(input) - 1] = '\0';

        // Enter Key Pressed. Loop
        if(input[0] == '\n')
        {
            continue;
        }
        
        // Convert char * to int
        portNumber = atoi(input);
        pid = fork();
        
        if (pid < 0) 
        {
            die("fork failed");
        }
        else if (pid == 0) 
        {
            // child process information
            fprintf(stderr, "[pid=%l] ", getpid());
            fprintf(stderr, "mdb-lookup-server started on port %s\n", input);
            execl("./mdb-lookup-server-nc.sh", "mdb-lookup-server-nc.sh", input, (char *)0);
            die("execl failed");
        }
        else 
        {
            // Parent process will keep looping round
            continue;
        }
    }
    return 0;
}
