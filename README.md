# Columbia-C-Projects

C programming assignments from Columbia University's **COMS W3157 Advanced Programming**, taught by Professor Jae Woo Lee. This course is widely regarded as one of the most rigorous undergraduate systems programming courses in Columbia's CS curriculum, and serves as a prerequisite for graduate-level systems courses.

---

## Course Overview

COMS W3157 covers systems-level programming in C with a strong emphasis on how software interacts directly with the operating system. Topics include memory management, pointer arithmetic, file I/O, process management, signals, inter-process communication, and network socket programming. All assignments are developed and tested on Linux using GCC, Make, and Git.

---

## Contents

All labs are contained in the `advanced-programming-coms-w3157/` directory.

---

### Lab 1 — Math Utilities & Integer Representation

**Part 1** (`gcd.c`, `prime.c`, `main.c`): Multi-file C project implementing number theory utilities.
- GCD computation via iterative Euclidean algorithm
- Primality testing via trial division up to √n
- Coprimality detection
- Separate `.h` header files and Makefile-based build

**Part 2** (`convert.c`): 32-bit integer representation tool.
- Prints a signed integer as signed decimal, unsigned decimal, hexadecimal, and binary
- Bitwise right-shift and masking (`(a >> i) & 1`) to extract individual bits
- Demonstrates signed vs. unsigned type semantics — foundational to understanding buffer overflows and binary exploitation

---

### Lab 2 — Pointer-Based Sorting & Command-Line Argument Processing

**Part 1** (`isort.c`, `sort.c`, `sort.h`): Selection sort implemented entirely via pointer arithmetic.
- `findMin` / `findMax` traversal using pointer bounds (no array indexing)
- Dynamic memory allocation with `malloc`, `free`, and `memcpy`
- Ascending and descending sort via function dispatch
- Multi-file project with header separation

**Part 2** (`twecho.c`): Command-line argument duplication and capitalisation.
- 2D dynamic array allocation — array of `char *` pointers
- String duplication and in-place ASCII manipulation (capitalisation via arithmetic on character codes)
- Manual memory management including proper freeing of a 2D heap structure

---

### Lab 3 — Generic Linked List & String Reversal

**Part 1** (`mylist.c`, `mylist.h`, `mylist-test.c`): A fully generic linked list implemented in C using `void *` data pointers.
- `addFront`, `addAfter`, `popFront`, `removeAllNodes`
- In-place list reversal by pure pointer manipulation — no additional memory allocation
- Generic traversal via function pointers: `void (*f)(void *)`
- Generic search via comparator function pointers: `int (*compar)(const void *, const void *)`
- This is the same interface pattern used in the C standard library (`qsort`, `bsearch`)

**Part 2** (`revecho.c`): Uses the Lab 3 linked list to reverse and search command-line arguments.
- `strcmp` passed as a function pointer for string-based node search
- Proper memory cleanup via `removeAllNodes`

---

### Lab 5 — Process Management & Inter-Process Communication

**Part 1** (`mdb-lookup-server-nc-1.c`, `mdb-lookup-server-nc-2.c`, `mdb-lookup-server-nc.sh`): A networked database lookup server using Unix process primitives and shell-based IPC.

- **`fork()` and `execl()`** — spawning child processes and replacing process image
- **`waitpid()`** — synchronous child reaping (version 1) and non-blocking reaping with `WNOHANG` (version 2)
- **Named pipes (FIFOs)** — `mkfifo` to create a bidirectional IPC channel between processes
- **`netcat` (`nc`)** — exposing a backend server over TCP via shell pipe composition
- **Signal handling** — `trap on_ctrl_c INT` to intercept and suppress SIGINT in the shell layer
- **Process tree analysis** — lab includes a live `ps ajxfww` capture with written explanation of the full process hierarchy (parent, child, shell, nc, grep)

This lab demonstrates hands-on understanding of the Unix process model, IPC mechanisms, and signal handling — core concepts in operating systems security and systems programming.

---

### Lab 6 — TCP Database Server & HTTP Client

**Part 1** (`mdb-lookup-server.c`): A persistent TCP server that loads a binary database into memory and serves client queries over the network.

- TCP server loop: `socket`, `bind`, `listen`, `accept`
- Binary file I/O — loading structured records from disk using `fread`
- In-memory database using the generic linked list from Lab 3
- Client query handling — substring search over linked list records, results sent via `send()`
- **SIGPIPE handling** — `signal(SIGPIPE, SIG_IGN)` to prevent server termination on broken connections
- Network byte order conversion — `htonl`, `htons`
- Per-connection memory cleanup — full list teardown and reinitialization between clients
- Multi-lab integration: combines socket programming, linked lists, and signal handling

**Part 2** (`http-client.c`): A from-scratch HTTP/1.0 client that downloads files from a web server.

- DNS resolution via `gethostbyname()`
- Constructs and transmits well-formed HTTP GET requests
- Parses HTTP response headers — status line, `Content-Length` extraction
- Downloads and writes response body to a local file using buffered `fread` / `fwrite`
- Handles buffer boundary conditions between HTTP headers and file content

---

### Lab 7 — HTTP/1.0 Server

(`http-server.c`): An HTTP server implementation built incrementally across three submission parts, derived from a TCP receiver skeleton.

- TCP accept loop with `socket`, `bind`, `listen`, `accept`
- HTTP/1.0 request parsing — method, URI, and version extraction via `strtok()`
- HTTP error responses — 400 Bad Request and 501 Not Implemented
- **Path traversal attack detection** — explicit rejection of `/../` in request URIs
- Socket-to-FILE abstraction via `fdopen()`
- Structured access logging — client IP, request line, and response status formatted per connection
- Makefile with incremental build targets

---

## Skills Demonstrated Across the Lab Sequence

- Systems programming in C (memory management, pointers, pointer arithmetic)
- TCP/IP socket programming (client and server)
- Unix process model (fork, exec, wait, signals, IPC)
- HTTP protocol implementation (client and server)
- Data structures in C (generic linked list with function pointers)
- Build automation (Makefile)
- Version control (Git, incremental development via diffs)
- Security awareness (path traversal detection, SIGPIPE handling, signed/unsigned integer semantics)

---

## Languages & Tools

- C (C99)
- GNU GCC with `-Wall`
- GNU Make
- Bash
- Git
- Linux (tested on Columbia's CLAC computing cluster)

---

## Context

COMS W3157 is a required course for Columbia CS majors and a prerequisite for graduate-level systems courses. Professor Jae Woo Lee's curriculum is widely respected in the Columbia CS community for its depth and practical emphasis on real Unix systems programming.
