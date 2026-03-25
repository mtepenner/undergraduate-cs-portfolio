# Portland Activity Center Management System

## Description
This repository contains a C++ application designed to manage events and activities for the Portland Activity Center. It implements an Object-Oriented class hierarchy centered around a base `Activity` class, which branches into specialized `Tour`, `Game`, and `Concert` categories. To efficiently store and manage these polymorphic objects, the project utilizes custom template-based data structures, specifically a Doubly Linked List (DLL). The system incorporates robust memory management, recursive list traversal, and custom exception handling.

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Contributing](#contributing)

## Installation 🛠️

To compile and run this project, you will need a standard C++ compiler (such as GCC/g++).

1. **Clone the repository:**
   ```sh
   git clone <repository-url>
   cd <repository-directory>

```

2. **Compile the source files:**
Using `g++`, compile the core files and the main executable:
```sh
g++ main.cpp hierarchy_functions.cpp interface.cpp -o activity_center

```


*(Note: A `Makefile` is also provided in the repository for automated builds.)*
3. **Run the executable:**
```sh
./activity_center

```



## Usage 🚀

Upon running the application, you will be greeted by the Portland Activity Center welcome screen. The main executable passes control to an `Interface` class, which handles the interactive console menu. Follow the on-screen prompts to instantiate `Tour`, `Game`, and `Concert` objects, add them to the system, and manipulate the doubly linked list.

## Features ✨

* **Template Data Structures:** Features a fully templated `DLL` (Doubly Linked List) and `Node` class. This allows the data structure to accept generic data types while performing recursive insertions, displays, and removals.
* **Advanced Operator Overloading:** Implements comprehensive operator overloading across the class hierarchy. This includes I/O streaming (`<<`, `>>`), relational comparisons (`<`, `>`, `<=`, `>=`, `==`, `!=`), and arithmetic traversal operators (`+`, `+=`, `-=`) for moving through nodes.
* **Class Hierarchy & OOP:** Enforces strong Object-Oriented principles by categorizing events into derived classes (`Tour`, `Game`, `Concert`) that inherit from the base `Activity` class.
* **Custom Exception Handling:** Includes a custom `ExceptionHandle` class inherited from the standard C++ `<exception>` library to safely manage runtime errors.
* **Dynamic Memory Management:** Deep copy constructors and overloaded assignment operators are rigorously implemented in both the data structures and the activity classes to prevent shallow copying of dynamically allocated character arrays (`char *`).

## Technologies Used 💻

* **Language:** C++

## Contributing 🤝

Contributions, issues, and feature requests are welcome! Feel free to check the issues page.
