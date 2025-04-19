Christopher Jean
cjj2126	
lab5

Part 1:

1.a:
This works as intended.

1.b:
Command executed:
ps ajxfww | grep "10273"
I did this so I didn't have a list of all the processes that are not mine. I
manually inserted the column headers.
I used this grep because I used port 10273, so grep would get all processes
that are using this port/are related to it (e. g. looking for it through
grep).

PPID  PID   PGID SID   TTY       TPGID STAT UID    TIME         COMMAND
8916  8917  8916 12102 pts/9     8916 S+    2237   0:00  |               \_ nc clac.cs.columbia.edu 10273
3116  8758  8758  3116 pts/169   8758 S+    2237   0:00  |           \_ ./mdb-lookup-server-nc-1 10273
8758  8759  8758  3116 pts/169   8758 S+    2237   0:00  |               \_ /bin/bash ./mdb-lookup-server-nc.sh 10273
8759  8762  8758  3116 pts/169   8758 S+    2237   0:00  |                   \_ nc -l 10273
13401 13403 13401  9113 pts/234  13401 S+    2237   0:00  |               \_ grep 10273

Understanding of output:
Process with PID 8197 is connecting to clac.cs.columbia.edu at port 10273.
Process with PID 8758 is running an executable program
./mdb-lookup-server-nc-1 with argument 10273.
This process spawned the shell command nc -l 10273 which came from
mdb-lookup-server-nc.sh
There is also another shell command grep, which I used to isolate the
processes that are only related to "10273", or the port number I used in
part b.

The shell script is the program that has a #!/bin/bash as their first
line and does not require to be compiled. So the only shell script that is
being submitted is:
- mdb-lookup-server-nc.sh
as mdb-lookup-server-nc-1 and mdb-lookup-server-nc-2 are programs that are
compiled via GCC.

1.c:
This works as intended. 

Part 2:
Left blank due to time.
