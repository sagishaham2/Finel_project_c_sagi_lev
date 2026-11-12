# 🧩 Connected Components Analyzer (C Project)

A robust C program designed to identify, analyze, and sort connected components within a 2D grid. Built with a strong emphasis on dynamic memory management and efficient bitwise operations.

## ✨ Features
- **Memory Efficiency:** Uses bitwise operations to store the grid, minimizing memory footprint (1 bit per cell).
- **Advanced Data Structures:** Implements Linked Lists to group connected cells (components) and a Binary Search Tree (BST) to sort these components by size and coordinates.
- **Robust Error Handling:** Strict memory allocation checks and input validation to prevent memory leaks and crashes.

## 🛠️ Tech Stack
- **Language:** C
- **Core Concepts:** Pointers, Dynamic Memory Allocation (`malloc`, `calloc`, `free`), Bitwise Operations, Linked Lists, Binary Search Trees (BST).

## 🚀 How to Run
1. Clone the repository:
   ```bash
   git clone [https://github.com/sagishaham2/Finel_project_c_sagi_lev.git](https://github.com/sagishaham2/Finel_project_c_sagi_lev.git)
   cd Finel_project_c_sagi_lev
   ```
2. Compile the project (using `gcc`):
   ```bash
   gcc -ansi -Wall -pedantic main.c func.c -o connected_components
   ```
3. Run the executable with grid dimensions (e.g., columns=10, rows=10):
   ```bash
   ./connected_components 10 10
   ```
