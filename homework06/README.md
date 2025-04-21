# Homework 06 - Cipher Implementation

This homework assignment focuses on implementing various encryption and decryption ciphers in C++, demonstrating object-oriented programming concepts like inheritance and polymorphism.

## Assignment Overview

The assignment involves implementing five different cipher types:
1. Substitution cipher (base class)
2. Caesar cipher
3. ROT13 cipher
4. Running Key cipher
5. Vigenere cipher

## Implementation Requirements

### Class Structure
- All cipher classes must inherit from either:
  - The substitution cipher class, or
  - One of the other cipher classes (e.g., Caesar from Substitution, ROT13 from Caesar)
- Each class must implement:
  - Appropriate constructor(s)
  - Default constructor (except ROT13)
  - Destructor
  - Encrypt and decrypt functions

### Constructor Requirements
1. Substitution cipher:
   - Cipher alphabet (26 lowercase letters, no duplicates)
2. Caesar cipher:
   - Positive shift/rotation integer
3. ROT13:
   - No input required (default constructor only)
4. Running Key:
   - Vector of strings (cipher "book")
5. Vigenere:
   - String key word (lowercase letters only)

### Default Constructors
- ROT13: Only has default constructor
- Others: Initialize to return plain text through proper encryption method

### Data Hiding
- All cipher classes must use the Cheshire smile pattern
- Data members must be hidden

### Input Validation
- Each cipher must validate its inputs
- Exit with EXIT_FAILURE for invalid inputs
- Match error messages with test cases

## Files and Directories

- `main.cc`: Main program (do not modify)
- `cipher.h` and `cipher.cc`: Base substitution cipher
- `ccipher.h` and `ccipher.cc`: Caesar cipher
- `rcipher.h` and `rcipher.cc`: ROT13 cipher
- `kcipher.h` and `kcipher.cc`: Running Key cipher
- `vcipher.h` and `vcipher.cc`: Vigenere cipher
- `test1/`, `test2/`, `test3_error/`: Test directories

## Testing

Test the implementation using the provided test cases:
```bash
./cipher -m [cipher_type] -i input.txt -o output.txt
```

Where:
- `-m`: Cipher method (c=Caesar, r=ROT13, k=Running Key, v=Vigenere)
- `-i`: Input file containing shift/key and plain text
- `-o`: Output file for encrypted and decrypted text

## Important Notes

- Do not modify provided skeleton code
- Handle memory management properly (Valgrind will check for leaks)
- Maintain case sensitivity in encryption/decryption
- Preserve spaces in text
- Use inheritance and polymorphism effectively
- Start early due to complexity

## Submission

1. Complete implementation of all cipher classes
2. Test thoroughly with provided test cases
3. Verify error handling matches test3_error examples
4. Commit and push to Bitbucket
5. Verify submission on Bitbucket website 