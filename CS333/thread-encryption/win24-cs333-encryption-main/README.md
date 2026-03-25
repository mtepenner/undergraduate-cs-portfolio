# Thread Crypt

## Description
Thread Crypt is a multi-threaded password hashing utility written in C. It reads a list of words from an input file and generates cryptographic hashes using the `crypt_r` library. The program leverages `pthreads` to distribute the hashing workload across multiple threads, allowing for efficient parallel processing. 

## 🚀 Features
* **Multi-threaded Performance**: Utilizes `pthreads` to spin up a user-defined number of threads (up to 20) for concurrent hashing.
* **Broad Algorithm Support**: Supports a wide range of hashing algorithms, including DES (default), MD5, NT, SHA-256, SHA-512, bcrypt, yescrypt, and gost-yescrypt.
* **Configurable Parameters**: Allows precise control over the hashing process, including customizable salt lengths, algorithm rounds, and yescrypt-specific parameters.
* **Thread-Safe**: Uses `crypt_r` and mutex locks to ensure safe concurrent processing of the input word list.

## 🛠️ Installation

This project includes a `Makefile` for easy compilation. 

To build the executable, simply run:
```bash
make

```

This will compile the `thread_crypt.c` source file, linking the necessary `-lcrypt` and `-pthread` libraries, and output the `thread_crypt` executable.

To clean up the compiled object files and the executable, run:

```bash
make clean

```

## 💻 Usage

The program requires an input file containing the words to be hashed. By default, it outputs to standard output (`stdout`), but an output file can be specified.

**Basic Command:**

```bash
./thread_crypt -i <input_file.txt>

```

**Options:**

* `-i file`: Input file name (required)
* `-o file`: Output file name (defaults to stdout)
* `-t #`: Number of threads to create (default 1, max 20)
* `-a char`: Algorithm to use for hashing (default DES):
* `0`: DES
* `1`: MD5
* `3`: NT
* `5`: SHA-256
* `6`: SHA-512
* `b`: bcrypt
* `y`: yescrypt
* `g`: gost-yescrypt


* `-l #`: Length of the salt (valid lengths depend on the algorithm)
* `-r #`: Number of rounds for SHA-256, SHA-512, and bcrypt
* `-p str`: Parameters to use for yescrypt or gost-yescrypt (default is "j9T")
* `-R #`: Seed used for random salt generation via `rand_r()` (default 3)
* `-v`: Enable verbose mode for debugging output
* `-h`: Display the help text

**Example:**
Hash words from `passwords.txt` using SHA-512 with 4 threads and save the results to `hashes.txt`:

```bash
./thread_crypt -i passwords.txt -o hashes.txt -t 4 -a 6

```

## 🧰 Technologies Used

* **Language**: C
* **Libraries**: `<pthread.h>`, `<crypt.h>`
* **Build System**: GNU Make

