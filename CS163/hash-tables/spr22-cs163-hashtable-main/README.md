# Animal Hash Table Organizer

## Description
The Animal Hash Table Organizer is a C++ application that implements a custom hash table data structure to store and manage a collection of animals. It resolves collisions using an array of linked lists (chaining) and dynamically allocates memory for all string attributes to ensure efficient memory usage. The program includes an interactive command-line interface (CLI) that allows users to seamlessly add, remove, search, and display animal records based on specific traits such as breed, personality, and keywords. It also features file I/O capabilities to load initial data from an external text file.

## 📑 Table of Contents
- [Features](#-features)
- [Installation](#️-installation)
- [Usage](#-usage)
- [Technologies Used](#-technologies-used)
- [License](#-license)

## 🚀 Features
* **Custom Hash Table**: Implements a dynamically allocated array of head pointers with linked-list chaining for collision resolution.
* **Dynamic Memory Management**: Utilizes deep copying and dynamic allocation (`new` and `delete`) for all string data to prevent memory leaks and optimize storage.
* **Interactive CLI**: Provides a user-friendly, menu-driven interface for database interaction.
* **Advanced Querying**: Search for animals by specific attributes such as personality type or descriptive keywords.
* **Persistent Loading**: Automatically loads an initial dataset from `external.txt` upon startup.

## 🛠️ Installation

To compile the source code, you will need a standard C++ compiler (such as `g++`). 

1. Clone the repository and navigate to the project directory.
2. Compile the source files using the following command:
```bash
g++ -Wall -Wextra main.cpp animal.cpp program3.cpp -o animal_organizer

```

3. Ensure that `external.txt` is in the same directory as the executable to allow the program to load the initial data.

## 💻 Usage

Run the compiled executable to start the application:

```bash
./animal_organizer

```

Upon launching, you will be presented with the following menu:

1. **Adding an animal**: Manually enter the breed, category, personality, purpose, size, keywords, and age of a new animal.
2. **Removing an animal using a keyword**: Delete specific animals from the database that match a provided keyword.
3. **Display all animals**: Recursively print all animals currently stored in the hash table.
4. **Displaying all animals that match a specified personality**: Filter and display animals by their personality trait.
5. **Retrieving if animals exist based on inputted keywords**: Search and retrieve animal records matching a specific keyword.
6. **Displaying all animals that match specified keywords**: Output all animals that match a given keyword.
7. **Ending the program**: Enter `0` to safely deallocate all memory and exit the application.

## 🧰 Technologies Used

* **Language**: C++
* **Concepts**: Data Structures (Hash Tables, Linked Lists), Dynamic Memory Allocation, File I/O (`<fstream>`), Recursion
