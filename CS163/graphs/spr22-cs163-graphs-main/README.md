# Animal Graph Database

## Description
This project implements a custom Graph data structure in C++ to represent a network of animal profiles. The graph uses an adjacency list architecture, where a core `table` class manages a dynamically allocated array of vertices. Each vertex holds an `animal` object—which uses dynamically allocated C-strings to efficiently store attributes like breed, category, personality, and size—and a head pointer to an edge list of connected nodes. The project includes an interactive client menu to build and explore the graph at runtime.

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
   g++ main.cpp animal.cpp program5.cpp -o graph_app
   ```
3. **Run the executable:**
```sh
./graph_app

```



## Usage 🚀

When you run the application, you will be presented with a console-based interactive menu. Enter the corresponding numbers to interact with the graph:

* **1**: Insert a new vertex (prompts for animal details like breed, category, personality, purpose, size, keywords, and age).
* **2**: Display the adjacency list, which outputs all animals and their connected adjacent nodes.
* **3**: Insert a connection (edge) between two existing vertices by specifying their breeds.
* **4**: Quit the program.

## Features ✨

* **Adjacency List Graph:** The graph is efficiently structured as an array of `vertex` structs, each maintaining a linked list of adjacent `node` pointers.
* **Edge Insertion:** Supports locating vertices by a string key (the breed) and establishing directional edge connections between them.
* **Dynamic Memory Management:** Thoroughly implements manual memory management. The `animal` struct dynamically allocates exact string lengths for its fields, and custom destructors/remove functions prevent memory leaks when destroying the graph.
* **Deep Copying:** Safely duplicates node data using a custom `copy_entry` function when populating new vertices.

## Technologies Used 💻

* **Language:** C++

## Contributing 🤝

Contributions, issues, and feature requests are welcome! Feel free to check the issues page.


