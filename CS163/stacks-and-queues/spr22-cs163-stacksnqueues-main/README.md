# Stack and Queue Data Structures

## Description
This project implements custom Abstract Data Types (ADTs) in C++ to manage a collection of academic assignments and their associated reference books. The `stack` class is implemented as a Linear Linked List (LLL) where each node contains a dynamically allocated array of book objects. The `queue` class is implemented as a Circular Linked List (CLL) using a rear pointer, which stores assignments and pairs them with a stack of books used for each project. A fully interactive console menu is provided to test the functionality of both data structures.

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Contributing](#contributing)

## Installation 🛠️

To compile and run this project, you will need a standard C++ compiler (such as GCC/g++).

1. **Clone the repository and navigate to the project directory.**
2. **Compile the source files:**
   ```sh
   g++ main.cpp stack.cpp queue.cpp entry.cpp -o app

```

3. **Run the executable:**
```sh
./app

```



## Usage 🚀

Upon running the program, you will be greeted by an interactive menu. You can enter the corresponding numbers to interact with the stacks and queues:

* **1**: Add a book to the stack.
* **2**: Display all books currently in the stack.
* **3**: Remove (pop) a book from the top of the stack.
* **4**: Create an assignment and add (enqueue) it to the queue.
* **5**: Display all assignments in the queue.
* **6**: Peek at the book at the top of the stack.
* **7**: Remove (dequeue) an assignment from the front of the queue.
* **8**: Peek at the next assignment due.
* **0**: Terminate the program.

## Features ✨

* **Array-Based LLL Stack:** Manages books using an array size of 2 per node, handling dynamic allocation and deep copying for title, author, and publisher data.
* **Circular Queue:** Enqueues and dequeues items efficiently in O(1) time complexity using a single `rear` pointer structure.
* **Recursive Traversal:** Display functions for both the stack and queue utilize recursive wrapper functions to traverse the nodes.
* **Dynamic Memory Management:** Carefully engineered constructors and destructors ensure proper deallocation of linked list nodes and inner dynamically sized character arrays to prevent memory leaks.

## Technologies Used 💻

* **Language:** C++

## Contributing 🤝

Contributions, issues, and feature requests are welcome! Feel free to check the issues page.
