# 📚 Computer Science Coursework Archive

A comprehensive portfolio of computer science projects, assignments, and coursework spanning multiple foundational and upper-division classes. This repository serves as a showcase of academic progression and technical skill, featuring implementations in C++, C, Python, and Rust. 

Each folder represents a specific course and contains various programs demonstrating theoretical concepts applied to practical software engineering problems.

## 📑 Table of Contents
- [Courses Included](#-courses-included)
- [Technologies Used](#-technologies-used)
- [Installation & Usage](#%EF%B8%8F-installation--usage)
- [Features & Highlights](#-features--highlights)
- [Contributing](#-contributing)
- [License](#-license)

## 🎓 Courses Included

* **CS163: Data Structures**
  * Implementations of core data structures including Binary Search Trees (BST), Hash Tables, Stacks, Queues, Graphs, and Linked Lists.
* **CS302: Advanced Data Structures & Algorithms**
  * Advanced concepts such as Hierarchical Data Structures, Templates, and 2-3 Trees.
* **CS314: Computer Systems & Assembly**
  * Low-level system operations, logic, and memory management algorithms.
* **CS333: Systems Programming & Operating Systems**
  * C-based projects exploring Client-Server architecture, custom Linux utilities (`stat` and `wc`), and multithreaded encryption.
* **CS358: Principles of Programming Languages**
  * Interpreter and parser design using Python, including an ES Interpreter, a Toylang compiler, and currying logic.
* **CS410 & CS410P: Advanced Software**
  * Various lab-based projects exploring modern software engineering practices.
* **CS423: Advanced Systems & Simulation**
  * Complex software systems including an Air Traffic Control (ATC) Simulator and a Rule 110 Cellular Automaton, primarily developed in Rust.

## 💻 Technologies Used

* **Languages:** C++, C, Python, Rust, TypeScript
* **Build Tools:** Make, Cargo
* **Concepts:** Data Structures, Object-Oriented Programming, Systems Programming, Parsing/Compilers, Multithreading, Network Sockets.

## 🛠️ Installation & Usage

Because this repository is an archive of diverse projects, installation and execution instructions vary by directory. 

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/mtepenner/undergraduate-cs-portfolio.git](https://github.com/mtepenner/undergraduate-cs-portfolio.git)
   cd courses
   ```

2. **Navigate to a specific project:**
   ```bash
   cd CS333/client-server/win24-cs333-clientserver-main
   ```

3. **Compile and Run (General Guidelines):**
   * **For C/C++ projects:** Most directories include a `Makefile`. Run `make` to compile the source code, then execute the output binary (e.g., `./main`).
   * **For Python projects:** Run using the Python interpreter: `python3 script.py`.
   * **For Rust projects (e.g., CS423):** Use Cargo to build and run: `cargo run`.

*(Please refer to the individual `README.md` files located within specific project subdirectories for detailed instructions).*

## 🚀 Features & Highlights

* **Algorithm Optimization:** Custom-built data structures (like 2-3 trees and Hash Tables) designed for maximum efficiency.
* **Concurrency:** Thread-safe encryption programs demonstrating safe memory management and POSIX threads.
* **Systems Architecture:** Custom client-server applications handling raw network traffic using C sockets.
* **Language Design:** Fully functional parsers and interpreters built from scratch to parse abstract syntax trees.
* **Modern Tooling:** Utilization of Rust's robust ownership model for safe, concurrent simulation systems.

## 🤝 Contributing

This repository primarily serves as a personal academic archive and portfolio. While external pull requests are not actively sought for past assignments, feedback, code reviews, and issue reports regarding bugs or optimizations are always welcome!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📄 License

Distributed under the MIT License. See `LICENSE` for more information.
