# Pet Center 2-3 Tree Database

## Description
This project is a C++ application that implements a custom 2-3 Tree to manage a database for a Pet Center. The primary architectural focus of this project is the strict avoidance of raw pointers; the entire tree and its payload are managed using standard library smart pointers (`std::unique_ptr`) to guarantee memory safety and prevent leaks. The tree stores a polymorphic class hierarchy consisting of an abstract `pet` base class and derived `dog`, `cat`, and `bunny` classes, making heavy use of dynamic binding and runtime type identification (`dynamic_cast`).

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Contributing](#contributing)

## Installation 🛠️

To compile and run this project, you will need a standard C++ compiler (such as GCC/g++) that supports C++14 or newer.

1. **Clone the repository and navigate to the project directory.**
2. **Compile the source files:**
   ```sh
   g++ main.cpp animal.cpp twoThreeTree.cpp -o pet_center

   ```

*(Note: You can also use the included `Makefile` if available by simply running `make` in the terminal).*

3. **Run the executable:**

   ```sh
   ./pet_center
   
   ```

## Usage 🚀

Upon running the application, you will enter the interactive Pet Center console menu. Follow the prompts to test the data structure:

* **(1) Add a pet**: Prompts you to select a specific animal type (cat, dog, or bunny) and asks for unique details like temperament, care level, and custom attributes (e.g., favorite toy for a dog, catnip addiction for a cat).
* **(2) Remove all pets**: Clears the entire 2-3 tree safely by resetting the root node's smart pointer.
* **(3) Display all pets**: Traverses the 2-3 tree and invokes the overridden display methods to print each animal's data to the console.
* **(0) Quit**: Exits the application.

## Features ✨

* **2-3 Tree Implementation:** Custom-built tree structure where nodes can hold up to two data items and manage three child branches (left, center, right).
* **Smart Pointers:** Replaces manual dynamic memory management (`new`/`delete`) with `std::unique_ptr` and `std::make_unique` to guarantee that memory is automatically and properly deallocated when objects fall out of scope.
* **Object-Oriented Design:** Implements an abstract `pet` class containing shared fields (name, temperament, history) and pure virtual functions for derived classes (`dog`, `cat`, `bunny`) to override.
* **Dynamic Casting:** Uses `typeid` and `dynamic_cast` during tree insertion to ensure the base smart pointers successfully invoke derived-class copies.
* **Exception Handling:** The console interface includes `try-catch` blocks to gracefully catch and handle input validation exceptions without crashing the program.

## Technologies Used 💻

* **Language:** C++
* **Libraries:** `<memory>` (for Smart Pointers), `<typeinfo>`

## Contributing 🤝

Contributions, issues, and feature requests are welcome! Feel free to check the issues page.
