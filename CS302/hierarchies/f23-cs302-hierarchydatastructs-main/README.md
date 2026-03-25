# Comic-Con Celebrity Database

## Description
This project implements custom Abstract Data Types (ADTs) and an Object-Oriented class hierarchy in C++ to manage attendees at a Comic-Con event. The system features a base `Name` class, a derived `Celebrity` class, and specialized sub-classes for `Actor`, `Artist`, and `Cosplayer`. To demonstrate different memory management techniques, each category is managed by a distinct data structure: Actors are stored in a Circular Linked List (CLL), Artists in an Array of Linear Linked Lists (ARR), and Cosplayers in a standard C++ Vector.

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
   g++ main.cpp celebrity.cpp ARR.cpp CLL.cpp -o comic_con

   ```

3. **Run the executable:**
   ```sh
   ./comic_con
   
   ```



## Usage 🚀

Upon running the application, an interactive console menu will guide you through managing the Comic-Con database. You can input the corresponding numbers to execute actions:

* **Manage Actors:** Options 1-8 allow you to add an Actor, display all Actors, remove records, schedule autographs, and query specific traits like awards or selfie permissions.
* **Manage Artists:** Options 9-13 allow you to insert an Artist into the Array of Linked Lists, retrieve specific artists, and purge the list.
* **Manage Cosplayers:** Options 20-27 cover Cosplayer functionalities, such as adding entries, viewing favorite outfits, retrieving experience levels, and scheduling stunt sessions.

## Features ✨

* **Class Hierarchy & OOP:** Implements a multi-level inheritance structure where specialized celebrity types inherit and expand upon base traits like name, age, and wealth.
* **Circular Linked List (CLL):** Manages `Actor` data using a dynamically linked ring structure driven by a `rear` pointer, with recursive insertion, removal, and retrieval methods.
* **Array of Linear Linked Lists (ARR):** Stores `Artist` records in an array of head pointers. It functions similarly to a hash table but relies on standard insertion logic to distribute nodes among lists.
* **Dynamic Memory Management:** Uses manually allocated character arrays (`char *`) for names and text fields, complete with robust copy constructors and overloaded assignment operators to ensure proper deep copying.
* **Recursive Operations:** All major traversal and manipulation logic across the bespoke data structures is accomplished using recursion.

## Technologies Used 💻

* **Language:** C++

## Contributing 🤝

Contributions, issues, and feature requests are welcome! Feel free to check the issues page.
