# Dog Park Directory

## Description
This project implements a custom Abstract Data Type (ADT) in C++ using a standard Linear Linked List (LLL) to catalog a directory of dog parks. The architecture utilizes nested data structures; each dog park node maintains its own head pointer to a secondary, internal linked list of associated amenities. An interactive client console program is provided, allowing users to build the lists dynamically, insert specific features, and recursively traverse the databases for queries.

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
   g++ main.cpp list.cpp -o dogparks

   ```

3. **Run the executable:**
  ```sh
  ./dogparks
  
  ```



## Usage 🚀

When you run the application, you will be greeted by an interactive menu. Enter the corresponding numbers to interact with the dog park lists:

* **1**: Add a dog park to the main list.
* **2**: Add a specific amenity (with a description and a rating) to a chosen dog park.
* **3**: Remove a dog park completely from the database.
* **4**: Display all recorded amenities for a specific dog park.
* **5**: Recursively display the names of all the dog parks in the database.
* **6**: Query the list to display all parks that feature a specific amenity.
* **0**: Terminate the program.
**

## Features ✨

* **Nested Linked Lists:** Structures the database using a primary linked list for parks, where each node contains an independent secondary linked list for park-specific amenities.
* **Dynamic Memory Management:** Exclusively uses dynamically allocated C-strings (`char *`) rather than fixed-size string classes to save exact byte sizes for park names, amenity names, and amenity details.
* **Recursive Traversal:** Implements wrapper functions and recursive core functions to sequentially traverse and display elements within the main list without loops.
* **Safe Deallocation:** The overarching destructor contains loop logic to safely cascade through nodes and release all dynamically allocated arrays to prevent memory leaks.

## Technologies Used 💻

* **Language:** C++

## Contributing 🤝

Contributions, issues, and feature requests are welcome! Feel free to check the issues page.

```

```
