# Homework 03 - Sparse Matrix-Vector Multiplication

This homework assignment focuses on implementing sparse matrix-vector multiplication using the Compressed Sparse Row (CSR) format.

## Assignment Overview

The assignment involves implementing two main functions:
1. `convert_coo_to_csr()`: Converts a matrix from Coordinate (COO) format to CSR format
2. `spmv()`: Performs sparse matrix-vector multiplication using the CSR format

## Provided Functionality

The following functions are provided and should be studied:
- `mm_read_mtx_crd()`: Reads sparse matrices in Matrix Market format
- `read_info()` and `print_matrix_info()`: Handles matrix information
- `read_vector()`: Reads vectors in Matrix Market-like format
- `store_result()`: Writes results in Matrix Market-like format

## Files and Directories

- `main.c`: Contains the main program and functions to be implemented
- `main.h`: Header file with function declarations
- `mmio.c` and `mmio.h`: Matrix Market I/O functions
- `Makefile`: Build configuration
- `test1/` and `test2/`: Test directories containing:
  - `A.mtx`: Input sparse matrix
  - `x.mtx`: Input vector
  - `ans.mtx`: Expected output

## Implementation Requirements

1. `convert_coo_to_csr()`:
   - Must use O(N) algorithm
   - No sorting algorithms allowed
   - Must work with randomly arranged non-zero elements
   - Must complete within 10 minutes for large matrices

2. `spmv()`:
   - Implement sparse matrix-vector multiplication
   - Use CSR format for efficient computation

## Testing

Test the implementation using the provided test cases:
```bash
make
./spmv test1/A.mtx test1/x.mtx output.mtx
diff output.mtx test1/ans.mtx
```

## Important Notes

- Do not modify provided skeleton code
- Do not add new functions
- Do not hard-code file names
- Code must compile with -std=c11 flag on ix-dev
- Use the provided Makefile for compilation

## Submission

1. Complete implementation of both functions
2. Test thoroughly with provided test cases
3. Verify output matches expected results
4. Commit and push to Bitbucket
5. Verify submission on Bitbucket website 