/*
Inherited from: tcp-recver.c
Now: mdb-server-lookup.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "mylist.h"
#include "mdb.h"
#define KEYMAX 5

static void die(const char *s) { perror(s); exit(1); }

//Free data, nodes in linked list

void freemdb(struct List * list)
{
    traverseList(list, &free);
    removeAllNodes(list);
}

//Read data from database into linked list

int loadmdb(FILE * fp, struct List *dest)
{
    struct MdbRec r;
    struct Node *node = NULL;
    int count = 0;

    if (fp == NULL || dest == NULL)
    {
        return -1;
    }

    while(fread(&r, sizeof(r), 1, fp))
    {
        struct MdbRec *rec = (struct MdbRec *)malloc(sizeof(r));
        if(rec == NULL)
        {
            return -1;
        }
        memcpy(rec, &r, sizeof(r));

        node = addAfter(dest, node, rec);
        if (node == NULL)
        {
            return -1;
        }
        ++count;
    }
    if(ferror(fp))
        return -1;

    return count;
}

int main(int argc, char **argv)
{
    //Ignore SIGPIPE so it does not terminate when called
    
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
    {
        die("signal() failed");
    }

    //Check errors
    if (argc != 3) 
    {
        fprintf(stderr, "usage: %s <database_file> <Server Port>\n", argv[0]);
        exit(1);
    }

    char *database = argv[1];
    unsigned short port = atoi(argv[2]);//Convert String to unsigned Short

    // Create listening/server socket
    // Pass to accept() i.e. a new child socket
    int servsock;
    if ((servsock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        die("socket failed");

    // Construct local address structure
    
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    //CAUTION: LINE IS DIFFERENT
    //In Client: you put the IP Address of Server
    //HERE I PUT MY OWN IP
    //INADDR_ANY, whatever my IP Address is.
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // any network interface
    servaddr.sin_port = htons(port);

    // Bind to the local address/Server (Bind to self)
    if (bind(servsock, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        die("bind failed");

    // Start listening for incoming connections
    // Client can't communicate until Server is Listening. 
    // Error: Connection Refused.
    // Allocate enough memory for 5 pending requests
    // Can not server 5 connections at a time...
    // 1 is connecting, 4 will wait

    if (listen(servsock, 5 /* queue size for connection requests */ ) < 0)
        die("listen failed");

    //Prepare for Client Connection
    int clntsock;
    socklen_t clntlen;//size of structure
    struct sockaddr_in clntaddr;


    //Variables for Communication
    int returnValue = 0;//storing return values
    char buf[4096];//Getting input from Socket
    //uint32_t size, size_net, remaining, limit;
    //struct stat st;

    //Prepare the LinkedList (Lab 4 code)
    struct List list;
    initList(&list);
    char key [KEYMAX + 1];
    int databaseSize = 0;
    FILE * fp;//File to read database from
    
    FILE * input; //Use this to communicate with Socket
    char output [4096];
    int outputSize = 0;

    while (1)
    {
        // Accept an incoming connection
        clntlen = sizeof(clntaddr); // initialize the in-out parameter

        //Obtain Client Info
        //clntlen will be over-written here
        if ((clntsock = accept(servsock,
                        (struct sockaddr *) &clntaddr, &clntlen)) < 0)
            die("accept failed");

        // accept() returned a connected socket (also called client socket)
        // and filled in the client's address into clntaddr

        fprintf(stderr, "client ip: %s\n", inet_ntoa(clntaddr.sin_addr));

        //Using mdblookup code from lab4
        fp = fopen(database, "rb");
        if (fp == NULL)
        {
            die("ERROR: NULL FILE FP");
        }
        if (ferror(fp))
        {
            die("ERROR AT OPENING DATABASE FILE");
        }
     
        databaseSize = loadmdb(fp, &list);
        if (databaseSize < 0)
        {
            die("ERROR AT loadmdb");
        }
        fprintf(stderr, "Size of Database: %d\n", databaseSize * 40);
        fclose(fp);
        //End of mdblookup initilaisation
        //Wrap input FILE * to socket 
        input = fdopen(clntsock, "r");

        //Begin while loop as in lab4
        while(fgets(buf,sizeof(buf),input) != NULL)
        {
            //Mull null terminate string manually after strncpy()
            strncpy(key, buf, sizeof(key)-1);
            key[sizeof(key) - 1] = '\0';

            //Remove newline if present
            size_t last = strlen(key) - 1;
            if (key[last] == '\n')
            {
                key[last] = '\0';
            }

            //Traverse list and print matches
            struct Node * node = list.head;
            int recNo = 1;

            while(node)
            {
                struct MdbRec * rec = (struct MdbRec *) node -> data;
                if(strstr(rec -> name, key) || strstr(rec -> msg, key))
                {
                    outputSize = sprintf(output, "%4d: {%s} said {%s}\n", recNo, rec -> name, rec -> msg);
 
                    returnValue = send(clntsock, output, outputSize, 0);
                  
                    
                    if(returnValue != outputSize)
                    {

                    } 
                }
                ++recNo;
                node = node -> next;
            }
        }
        if(ferror(input))
        {
            die("ferror detect at input file (SOCKET?)");
        }

        fprintf(stderr, "connection terminated: %s\n", inet_ntoa(clntaddr.sin_addr));
        //Close client connection and go back to accept()
        //Free list and start again
        freemdb(&list);
        fclose(input);
    }
    return 0;
}
