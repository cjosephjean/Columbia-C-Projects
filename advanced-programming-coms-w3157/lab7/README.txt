Christopher Jean
cjj2126
Lab 7

Part 1 (Part A):
I set up the basic TCP server socket structure and the initial http-server.c
file, including socket creation, bind, listen, and the accept loop. The Makefile
was configured with compilation targets for http-server.o and http-server.

Part 2 (Part B):
I implemented HTTP request parsing, extracting the method, request URI, and HTTP
version from the incoming request line using strtok(). I added error handling for
non-GET requests (501 Not Implemented), invalid HTTP versions (501 Not
Implemented), URIs not beginning with '/' (400 Bad Request), and URIs containing
'/../' as a path traversal security check (400 Bad Request). I wrapped the client
socket as a FILE * using fdopen() and added client IP logging via inet_ntoa().

Part 3 (Part C):
I added a reply() helper function to format structured access log entries
containing the client IP, request line, and response status. I also corrected
variable naming and typos from Part 2. Full file serving (reading and sending
file content from the web root) was not completed within the submission window.
