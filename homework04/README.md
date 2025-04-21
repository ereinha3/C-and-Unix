# Homework 04 - Breadth-First Search Implementation

This homework assignment focuses on implementing Breadth-First Search (BFS) using two different approaches:
1. Linked List representation
2. Sparse Matrix-Vector multiplication (adjacency matrix)

## Assignment Overview

The assignment requires implementing several key functions for graph traversal and manipulation:
1. `construct_adj_list()`: Creates an adjacency list from an adjacency matrix
2. `bfs()`: Implements BFS using linked list representation
3. `bfs_spmv()`: Implements BFS using sparse matrix-vector multiplication
4. `matrix_transpose()`: Helper function for matrix operations

## Provided Functionality

The following functions are provided:
- `load_matrix()`: Loads adjacency matrix from file
- `save_result()`: Saves BFS results to file
- Various support functions for graph operations

## Files and Directories

- `main.c`: Main program file
- `matrix.c` and `matrix.h`: Matrix operations
- `graph.c` and `graph.h`: Graph data structures and operations
- `load.c` and `load.h`: File I/O operations
- `Makefile`: Build configuration
- `test1/` and `test2/`: Test directories containing:
  - `test1.txt`/`test2.txt`: Input adjacency matrices
  - `ans_X.txt`: Expected output for source vertex X

## Implementation Requirements

1. `construct_adj_list()`:
   - Convert adjacency matrix to linked list representation
   - Handle memory allocation appropriately

2. `bfs()`:
   - Implement BFS using linked list representation
   - Track color, distance, and parent information

3. `bfs_spmv()`:
   - Implement BFS using sparse matrix-vector multiplication
   - Include matrix transpose functionality

## Testing

Test the implementation using the provided test cases:
```bash
make
./bfs test1/test1.txt source_vertex
```

Compare output with corresponding ans_X.txt files.

## Important Notes

- Do not modify provided skeleton code
- New functions may be added as needed (unlike previous homework)
- Do not hard-code file names
- Code must compile with -std=c11 flag on ix-dev
- This assignment is more complex than previous ones - start early!

## Submission

1. Complete implementation of all required functions
2. Test thoroughly with provided test cases
3. Verify output matches expected results
4. Commit and push to Bitbucket
5. Verify submission on Bitbucket website 