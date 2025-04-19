#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>


static void die(char *message)
{
    fprintf(stderr, "%s", message);
    exit(1);
}

int main(int argc, char ** argv)
{
  
    if (argc != 4)
    {
        fprintf(stderr, "%s usage: <hostname> <port> <file> ", argv[0]);
        exit(1);
    }

//=======================Variable Initialization==============================================
    //Extract arguments
    char * serverName = argv[1];
    unsigned short port = atoi(argv[2]);
    char * filepath = argv[3];

    //Starting variables
    int sock;
    struct sockaddr_in httpServerAddr;

    //Extract file name
    //filename points to LAST OCCURANACE OF /
    //otherwise /make.html
    char * filename = strrchr(filepath, '/');
    
    if (filename == NULL)
    {
        sprintf(filename, "/%s", filename);
        //die("Null Pointer Exception caused by strrchar()");
    }
    filename = filename + 1;//So I only have "make.html" NOT "/make.html"
    //fprintf(stderr,"filename: %s\n", filename);

    //Code from Jae
    struct hostent *he;

    //get Server IP from Server Name
    if((he = gethostbyname(serverName)) == NULL)
    {
        die ("gethostbyname failed");
    }
    char *serverIP = inet_ntoa(*(struct in_addr *)he -> h_addr);

    char HTTPhead1[4096];
    char HTTPhead2[4096];
    //HTTP arguments
    static char blank [] = "\r\n";
    int HTTPget1 = sprintf(HTTPhead1, "GET %s HTTP/1.0\r\n", filepath);
    int HTTPget2 = sprintf(HTTPhead2, "Host: %s:%d\r\n", serverName, port);
    
    FILE * input;
    char buffer[4096];
    FILE * output;
    int fileLength = 0;
    //Using Baylor Code from lab6 part1

    //Build client socket
    if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
            die("Error at creating Client Socket");

    //Build server address structure
    memset(&httpServerAddr, 0, sizeof(httpServerAddr));

    httpServerAddr.sin_family = AF_INET;
    httpServerAddr.sin_addr.s_addr = inet_addr(serverIP);
    httpServerAddr.sin_port = htons(port);

    if(connect(sock, (struct sockaddr *) &httpServerAddr, sizeof(httpServerAddr)) < 0)
    {
        die("Error with connect!");
    }
    //Send HTTP-GET request
    send(sock, HTTPhead1, HTTPget1, 0);
    send(sock, HTTPhead2, HTTPget2, 0);
    send(sock, blank, sizeof(blank), 0);

    //Wrap socket into a file
    input = fdopen(sock, "r");
  
    fgets(buffer, sizeof(buffer), input);

    int strayBytes = strlen(buffer);

    //Print the 200
    if((strstr(buffer,"200")) == NULL)
    {
        fprintf(stderr, "%s", buffer);
    }
    else
    {
        //Find  blank(stuck here?) using strstr()
        while(fgets(buffer, sizeof(buffer),input)!= NULL)
        {
            strayBytes += strlen(buffer);

            if(strstr(buffer, "Content-Length") != NULL)
            {
                //Go 16 bytes to the right
                char * temp = strrchr(buffer, ' ');
                temp = temp + 1;//Move over 1 more

                //Get file length
                fileLength = atoi(temp);
            }
            //If \r\n is detected HTTP file reading is done
            if(strcmp(buffer,"\r\n") == 0)
            {
                break;
            }
        }
        output = fopen(filename, "wb");

        /*
        There is some stuff in my buffer already!
        It is 4096 Bytes - Size of HTTP packets.
        */
        int leftover = sizeof(buffer) - strayBytes;
        if (fread(buffer, 1, leftover, input) != leftover)
        {
            die("First fread failed");
        }
        if(fwrite(buffer, 1, leftover, output) != leftover)
        {
            die("First fwrite failed");
        }

        int receiveSize = 1; 
        int remaining = fileLength;
        int limit = 0;

        remaining -= (sizeof(buffer) - strayBytes);//Subtract leftover over 4,096 bytes already printed...

        //Using code from tcp.recver
        while(remaining > 0)
        {
            limit = remaining > sizeof(buffer) ? sizeof(buffer) : remaining;

            receiveSize = recv(sock, buffer, limit, 0);
            
            if (receiveSize < 0)
            {
                die("receive failed");
            }
            else if(receiveSize == 0)
            {
                die("connection closed prematurely\n");
            }
            else
            {
                remaining -= receiveSize;
                if(fwrite(buffer, 1, receiveSize, output) != receiveSize)
                {
                    die("fwrite failed");
                }
            }
        }
        fclose(output);
    }
    fclose(input);
    return 0;
}
