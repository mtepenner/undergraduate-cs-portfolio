# Rockem Client-Server File Transfer

## Description
Rockem is a multi-threaded, TCP socket-based client-server application written in C. It enables concurrent file transfers (`put` and `get`) and remote directory polling (`dir`) between a client and a server. Both the client and server leverage `pthreads` to handle multiple operations simultaneously, making it an excellent demonstration of concurrent network programming, synchronization, and socket communication.

## 🚀 Features
* **Multi-threaded Architecture**: Both client and server spawn detached threads to handle concurrent file uploads and downloads, preventing blocking on massive transfers.
* **Bi-directional File Transfer**: Supports fetching files from the server (`get`) and uploading files to the server (`put`).
* **Remote Directory Listing**: Allows the client to request a detailed directory listing (`dir`) of the server's current working directory.
* **Interactive Server Terminal**: The server features an interactive command-line interface to monitor active connections, toggle verbosity, and manage the server instance in real-time.
* **Concurrency Testing**: Includes a configurable sleep delay (`-u`) to simulate network latency, making it easier to observe and test thread synchronization and concurrent connection handling.

## 🛠️ Installation

To compile the source files, you will need a standard C compiler (like `gcc`) and the `pthread` library. 

Compile the server:
```bash
gcc -Wall -Wextra -pthread -o rockem_server rockem_server.c

```

Compile the client:

```bash
gcc -Wall -Wextra -pthread -o rockem_client rockem_client.c

```

*(Note: If your project includes a `Makefile`, you can typically just run `make` to build both executables).*

## 💻 Usage

### Starting the Server

The server must be running before the client can connect. It listens on port `10001` by default.

**Basic Command:**

```bash
./rockem_server

```

**Options:**

* `-p #`: Port on which the server will listen (default: 10001)
* `-u`: Add a 1000 microsecond delay after each read/write (useful for testing concurrency)
* `-v`: Enable verbose output
* `-h`: Show the help message

**Server Interactive Commands:**
While the server is running, you can interact with its terminal:

* `count`: Display total connections and current active connections
* `v+` / `v-`: Increment or decrement the verbosity level
* `help`: Display available commands
* `exit`: Safely shut down the server

### Running the Client

The client connects to the server to execute a specified command.

**Basic Command:**

```bash
./rockem_client -i <server_ip> -c <command> [file1 file2 ...]

```

**Options:**

* `-i str`: IPv4 address of the server (default: 131.252.208.23)
* `-p #`: Port the server is listening on (default: 10001)
* `-c str`: Command to run (`get`, `put`, or `dir`)
* `-u`: Add a 1000 microsecond delay after read/write calls
* `-v`: Enable verbose output
* `-h`: Show the help message

**Examples:**

1. **Upload multiple files to the server:**

```bash
./rockem_client -i 127.0.0.1 -c put data1.txt data2.txt

```

2. **Download a file from the server:**

```bash
./rockem_client -i 127.0.0.1 -c get report.pdf

```

3. **Get a directory listing from the server:**

```bash
./rockem_client -i 127.0.0.1 -c dir

```

## 🧰 Technologies Used

* **Language**: C
* **Networking**: TCP/IP Sockets, `<arpa/inet.h>`, `<netdb.h>`
* **Concurrency**: POSIX Threads (`<pthread.h>`) and Mutex Locks
