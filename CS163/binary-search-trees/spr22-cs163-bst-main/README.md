# Animal Binary Search Tree Database

## Description
This project implements a custom Binary Search Tree (BST) data structure in C++ to store and manage a collection of animal profiles. The core `table` class encapsulates the BST logic, relying heavily on private recursive functions for operations like insertion, deletion, and searching. Each node in the tree holds an `animal` object, which utilizes dynamically allocated character arrays to efficiently store varying-length string details such as breed, category, personality, purpose, and size. To facilitate testing, the project includes an interactive client menu that allows users to manipulate and query the data structure at runtime.

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
   g++ main.cpp animal.cpp table.cpp -o bst_app

```

3. **Run the executable:**
```sh
./bst_app

```



## Usage 🚀

Upon running the application, you will be presented with a console-based interactive menu. Enter the corresponding numbers to execute various BST operations:

* **1**: Add an animal to the BST (prompts for breed, category, personality, purpose, size, keywords, and age).
* **2**: Remove an animal from the tree by specifying its breed.
* **3**: Display all animals currently stored in the BST.
* **4**: Display all animals matching a specific breed.
* **5**: Display all animals matching a specific size category.
* **6**: Retrieve and display animals that match both a specific breed and personality.
* **7**: Quit the program.

## Features ✨

* **Binary Search Tree Implementation:** Organizes data hierarchically to allow for efficient insertion and ordered retrieval, relying on alphabetical comparisons of string keys.
* **Recursive Operations:** Features private recursive functions wrapped by public methods for clean execution of traversing, adding, and removing nodes.
* **Dynamic Memory Allocation:** Uses dynamically allocated character arrays (`char *`) inside the `animal` struct to store strings precisely, conserving memory space.
* **Robust Node Removal:** Implements comprehensive removal logic for the BST, properly handling cases where a node to be deleted has zero, one, or two child nodes.
* **Memory Leak Prevention:** Includes robust destructors for both the tree structure (`remove_all`) and individual animal entries to safely deallocate memory.

## Technologies Used 💻

* **Language:** C++

## Contributing 🤝

Contributions, issues, and feature requests are welcome! Feel free to check the issues page.
