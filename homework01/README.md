# Homework 01 - File Search Implementation

This homework assignment focuses on implementing a recursive file search function in C. The goal is to create a program that can locate files within a directory structure by name.

## Assignment Overview

The main task is to implement the `find_file()` function that recursively searches through directories to find files matching a given name. The program should be able to:
- Search through the current directory and all subdirectories
- Match files by name
- Handle different directory structures
- Produce output matching the provided answer files

## Files and Directories

- `main.c`: Contains the main program and the `find_file()` function to be implemented
- `description.txt`: Original assignment description
- `ans1` and `ans2`: Example output files for testing
- Various test directories (a/, b/, c/, etc.) containing test files

## Testing

The program can be tested using the following commands:
```bash
./a.out . b.out    # Should match ans1
./a.out . a.out    # Should match ans2
```

## Requirements

- C compiler (gcc)
- Unix-like operating system
- Understanding of directory structures and file operations in C

## Implementation Notes

1. Read through the provided code in main.c before starting
2. Implement the `find_file()` function to handle recursive directory traversal
3. Ensure proper error handling
4. Test with various directory structures and file names

## Submission

The completed assignment should be:
1. Tested thoroughly with different inputs
2. Committed to your repository
3. Pushed to Bitbucket
4. Verified on the Bitbucket website 