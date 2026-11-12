Connected Components Analyzer in C

This project is a C-based application that analyzes a 2D grid of characters to find, group, and sort connected components (shapes) made of specific target characters. It utilizes advanced data structures and memory optimization techniques to perform its tasks efficiently.

🚀 Features

Bitwise Matrix Representation: To optimize memory usage, the 2D grid is stored using bitwise operations, meaning each cell occupies exactly 1 bit in memory rather than a full byte.

Connected Component Labeling: Scans the grid and groups adjacent # characters using dynamically allocated Linked Lists. It efficiently merges lists when disconnected parts of a shape meet.

Binary Search Tree (BST) Sorting: All identified shapes are inserted into a Binary Search Tree. They are sorted primarily by their size (area). If two shapes have the same size, they are sorted by their top-left-most coordinate.

Memory Safe: Strict dynamic memory allocation checks and comprehensive memory deallocation (no memory leaks).

📁 Project Structure

maic.c: The main entry point of the program. Handles command-line arguments and orchestrates the program flow.

func.c: Contains the core implementation of all algorithms, data structures (Matrix, Linked Lists, BST), and memory management functions.

func.h: The header file containing structure definitions and function prototypes.

🛠️ Compilation and Execution

Compilation

Use gcc to compile the source files into an executable. Run the following command in your terminal:

gcc -Wall -ansi -pedantic maic.c func.c -o components_analyzer


Execution

The program requires the dimensions of the grid (Columns and Rows) to be passed as command-line arguments.

./components_analyzer <columns_N> <rows_M>


Note: The arguments must be natural numbers.

Input Format

After running the executable, input the matrix characters row by row.

# represents a filled cell (part of a shape).

. represents an empty cell.

White spaces and newlines are ignored.

After the matrix is fully entered, provide a single integer k (between 1 and the total number of unique shapes found).

Output

The program will output the characteristics of the k-th smallest shape in the format:

<size> <y_coordinate> <x_coordinate>


📝 Example

Running the program:

./components_analyzer 5 4


Input:

. # . . #
. # # . #
. . . . .
# # . . .
2


(Explanation: We look for the 2nd smallest shape out of the 3 shapes present in the grid).

Output:

2 4 1


(Explanation: The 2nd smallest shape has a size of 2, starting at Y=4, X=1).
