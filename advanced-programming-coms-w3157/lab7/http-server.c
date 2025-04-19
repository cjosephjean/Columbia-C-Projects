/*
I created http-server based on tcp-recver.c 
code from Jae
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

static int reply(char *response, const char *IP, const char *get, const char * status)
{
    int size = sprintf(response, "%s \"%s\" %s", IP, get, status);
    return size;
}

static void die(const char *s)
{
    perror(s);
    exit(1);
}


int main(int argc, char **argv)
{
    //Error Checking
    if (argc != 5) 
    {
        fprintf(stderr, "usage: %s <server-port> <web_root> <mdb-lookup-host> <mdb-lookup-port>\n", argv[0]);
        exit(1);
    }

    unsigned short serverPort = atoi(argv[1]);//Convert String to unsigned Short
    //const char *webroot = argv[2];
    //const char * mdb-lookup-host = argv[3];
    //unsigned short mdbPort = atoi(argv[4]);

    // Create a listening socket (also called server socket) 
    // Will be passed to accept() which you can consider as a new child socket
    int servsock;
    if ((servsock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        die("socket failed");

    // Construct local address structure
    // Same way as the Client does it...
    
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;

    //CAUTION: LINE IS DIFFERENT
    //In Client: you put the IP Address of Server
    //HERE I PUT MY OWN IP
    //INADDR_ANY, whatever my IP Address is.
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // any network interface
    servaddr.sin_port = htons(serverPort);

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
    int sock;
    socklen_t clntlen;//size of structure
    struct sockaddr_in clntaddr;
    FILE inputFromClient;
    FILE * input;
 
    char * clientIP;

    char buffer[4096];

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

        //Wrap the File around the Socket...
        //Also get the IP
        clientIP = inet_ntoa(clntaddr.sin_addr);
        input = fdopen(clntsock, "r");

        

        //Obtain the HTTP Request
        fgets(buffer,sizeof(buffer), input);

        //Process HTTP Request and Error Check
        char *token_separators = "\t \r\n";//tab, space, new line
        char *method = strtok(buffer, token_separators);
        char *requestURI = strtok(NULL, token_separators);
        char *httpVersion = strtok(NULL, token_separators);
        char *response = NULL;
        int responseSize = 0;

        printf("%s\n %s\n %s\n", method, requestURI, response);

        //This is NOT a GET Request!
        if(strcmp(method,"GET") != 0)
        {
            char res1 [] = "HTTP/1.0 501 Not Implemented";
            send(sock, res1, sizeof(res1), 0);
            send(sock, "\r\t", sizeof("\r\t") ,0);
            char res2 [] = "<html><body><h1>501 Not Implemented </hi></body></html>";
            send(sock, res2, sizeof(res2), 0);
           
            //Format Standard response
            responseSize = reply(response, clientIP, buffer, "501 Not Implemented");
            fprintf(stdout, "%s\n", response);
            
            //Close Socket, Get the Next Client
            fclose(input);
            continue;
        }
        //This is NOT HTTP/1.0
        if(strcmp(httpVersion, "HTTP/1.0") != 0 || strcmp(httpVersion, "HTTP/1.1") != 0)
        {
            responseSize = reply(response, clientIP, buffer, "501 Not Implemented");
            fprintf(stdout, "%s\n", response);

            //Close the Socket, Get the Next Client
            fclose(input);
            continue;
        }
        if(requestURI[0] != '/')
        {
            responseSize = reply(response, clientIP, buffer, "400 Bad Request");
            fprintf(stdout, "%s\n", response);

            //Close the Socket, Get the Next Client
            fclose(input);
            continue;
        }
        //There is a security risk
        if(strstr(requestURI, "/../")!= NULL)
        {
            responseSize = reply(response, clientIP, buffer, "400 Bad Request");
            fprintf(stdout, "%s\n", response);

            //Close the Socket, Get the Next Client
            fclose(input);
            continue;
        }
        printf("%lu\n", strlen(requestURI));
        
        responseSize = reply(response, clientIP, buffer, "200 OK");
        fprintf(stdout, "%s\n", response);
        {
/*            while (remaining > 0)
            {
            limit = remaining > sizeof(buf) ? sizeof(buf) : remaining;
            //into buffer from client socket
            //limit is keeping track of bytes I have left.
            r = recv(clntsock, buf, limit, 0);
            if (r < 0)
                die("recv failed");
            else if (r == 0)
                die("connection closed prematurely");
            else 
            {
                remaining -= r;
                //Write to file from buffer
                if (fwrite(buf, 1, r, fp) != r) 
                    die("fwrite failed");
            }
        }
        assert(remaining == 0);
        fclose(fp);

        // Third, send the file size back as acknowledgement

        stat(filename, &st);
        size = st.st_size;//Recalculating File Size I just wrote

        fprintf(stderr, "file size on disk:  %u\n\n", size);
        size_net = htonl(size);

        if (send(clntsock, &size_net, sizeof(size_net), 0) 
                != sizeof(size_net))
            die("send size failed");

        // Finally, close the client connection and go back to accept()
 
 */
        close(clntsock);
    }
}
