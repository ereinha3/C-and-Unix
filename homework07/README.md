# Homework 07 - Binary Search Tree and Student Database

This homework assignment focuses on implementing a Binary Search Tree (BST) and a student database system using C++ classes, demonstrating object-oriented programming concepts like composition and inheritance.

## Assignment Overview

The assignment involves two main components:
1. Binary Search Tree implementation
2. Student database system using inheritance

## Implementation Requirements

### Binary Search Tree (BST)
- Implement the BST class declared in `bst.h`
- Must follow the provided class declaration
- Support all required BST operations
- May include the "transplant" function from CLRS
- Must handle memory management properly

### Student Database
- Implement the DB class using inheritance
- Student ID serves as the base class's key member
- Automatic ID assignment:
  - ID = n for nth student to join
  - IDs are not reassigned after student deletion
  - Last student's ID reflects total historical enrollment

## Files and Directories

- `main.cc`: Main program with test functions
- `bst.h` and `bst.cc`: Binary Search Tree implementation
- `db.h` and `db.cc`: Student Database implementation
- `Makefile`: Build configuration
- Test files:
  - `unittest_ans_t100_s100.txt`: BST unit test answers
  - `students_1.txt` and `students_1_ans.txt`: Database test files
  - `unit_test.txt`: Additional test cases

## Testing

### BST Testing
```bash
./bst -t 100 -s 100
```
Where:
- `-t`: Number of elements to add
- `-s`: Random seed value

### Database Testing
```bash
./bst students_1.txt
```

## Important Notes

- Do not modify provided class declarations
- Code must work beyond provided test cases
- Handle memory management properly (Valgrind will check for leaks)
- BST implementation must be robust and handle all edge cases
- Student IDs must be assigned sequentially and never reused
- Code should work with different test parameters

## Submission

1. Complete implementation of BST and Database classes
2. Test thoroughly with provided test cases
3. Verify memory management with Valgrind
4. Test with different parameters beyond provided tests
5. Commit and push to Bitbucket
6. Verify submission on Bitbucket website 