Christopher Jean
cjj2126
Lab 6

Part 1:
My code works as intended for the core functionality. mdb-lookup-server.c
implements a TCP server that loads a binary database file into memory using the
generic linked list from Lab 3, then accepts client connections and responds to
search queries by traversing the list and sending matching records back over the
socket. SIGPIPE is ignored to prevent the server from terminating when a client
disconnects unexpectedly. The server frees and reinitializes the list between
client connections.

Part 2:
My code works as intended for the core functionality. http-client.c implements
an HTTP/1.0 client that constructs and sends a GET request to a specified host
and port, parses the response headers (including Content-Length), and writes the
response body to a local file. DNS resolution is handled via gethostbyname().
