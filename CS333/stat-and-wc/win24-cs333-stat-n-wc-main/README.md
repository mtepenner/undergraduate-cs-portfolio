# Linux File Utilities: mystat & mywc

## Description
This repository contains custom C implementations of two standard UNIX/Linux command-line utilities: `stat` and `wc`. 
* **`mystat`** uses the `lstat` system call to extract and format comprehensive metadata for one or more specified files. 
* **`mywc`** reads from a file or standard input to calculate line, word, and character counts, featuring a flexible command-line interface parsed via `getopt`.

## 🚀 Features

### mystat
* **Detailed Metadata**: Displays file type, device ID, inode number, link count, and block information.
* **Human-Readable Permissions**: Converts octal mode into standard `rwxrwxrwx` format.
* **Timestamp Formatting**: Formats access, modification, and status change times into local, human-readable dates.
* **Symbolic Link Handling**: Accurately detects symbolic links and warns if the destination is dangling.
* **Multi-file Support**: Capable of processing and displaying data for multiple files in a single execution.

### mywc
* **Text Counting**: Calculates the number of lines (`-l`), words (`-w`), and characters (`-c`) in a given input.
* **Flexible Input**: Reads from a specified file using the `-f` flag or falls back to `stdin` if no file is provided.
* **Custom Formatting**: Automatically scales its output based on the specific flags provided by the user.

## 🛠️ Installation

You can compile these utilities using a standard C compiler such as `gcc`.

To compile `mystat`:
```bash
gcc -Wall -Wextra -o mystat mystat.c

```

To compile `mywc`:

```bash
gcc -Wall -Wextra -o mywc mywc.c

```

## 💻 Usage

### mystat

Pass one or more file paths as arguments to view their metadata.

**Basic Command:**

```bash
./mystat <file1> [file2] ... [fileN]

```

*Example:*

```bash
./mystat mywc.c

```

### mywc

Use command-line flags to specify which counts you want to view. If no count flags are provided, it defaults to displaying all three (lines, words, characters).

**Basic Command:**

```bash
./mywc [options]

```

**Options:**

* `-c`: Display the number of characters.
* `-l`: Display the number of lines.
* `-w`: Display the number of words.
* `-f <file>`: Use `<file>` as input. If omitted, it reads from `stdin`.
* `-v`: Enable verbose tracing output.
* `-h`: Display the help message.

*Example:*
Count lines and words in `data.txt`:

```bash
./mywc -l -w -f data.txt

```

## 🧰 Technologies Used

* **Language**: C
* **System Calls & POSIX APIs**: `<sys/stat.h>`, `lstat()`, `getopt()`, `<pwd.h>`, `<grp.h>`
