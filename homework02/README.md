# Homework 02 - Integer Array Operations

This homework assignment focuses on implementing functions for handling integer arrays, including memory allocation, file I/O, and arithmetic operations.

## Assignment Overview

The assignment requires implementing five key functions to handle integer arrays:
1. `get_num_ints()`: Determines the number of integers to process
2. `allocate_mem()`: Allocates memory for input and output arrays
3. `get_ints()`: Reads integers from input files
4. `sum_ints()`: Performs addition on the input arrays
5. `save_output()`: Saves the results to an output file

## Files and Directories

- `main.c`: Contains the main program and the five functions to be implemented
- `main.h`: Header file with function declarations
- `file_1.txt` and `file_2.txt`: Input files containing integers
- `file_3.txt`: Example output file for testing
- `test.txt`: Additional test file

## Implementation Requirements

1. Do not modify any provided skeleton code
2. Implement all five required functions
3. Do not add new functions
4. Do not make assumptions about the number of integers
5. Do not hard-code file names
6. Do not hard-code array sizes
7. Code must compile with -std=c11 flag on ix-dev

## Testing

The program can be tested using the provided input files:
```bash
./a.out file_1.txt file_2.txt output.txt
```

Compare the output with file_3.txt to verify correctness.

## Important Notes

- Remove the debug print statement before submission:
  ```c
  for(int i = 0; i < num_ints; i++) printf("%ld\n", output[i]);
  ```
- Ensure proper memory allocation and deallocation
- Handle file I/O operations carefully
- Test with various input file sizes

## Submission

1. Complete implementation of all five functions
2. Test thoroughly with provided input files
3. Remove debug print statement
4. Commit and push to Bitbucket
5. Verify submission on Bitbucket website 