# Homework 05 - Simple AI Response System

This homework assignment focuses on implementing a simple AI system that responds to messages based on keywords and emotional states.

## Assignment Overview

The assignment involves implementing a C++ class hierarchy for an AI response system that:
1. Reads keyword-response pairs with associated emotional states
2. Processes messages to detect keywords
3. Generates appropriate responses based on the emotional state
4. Stores responses in an output file

## Implementation Requirements

The following components need to be implemented:

1. `HappyResponse` class definition in `response.h`
2. `Response::checkAndRespond()` method
3. `Response::respond()` method
4. `AngryResponse::respond()` method
5. `HappyResponse::respond()` method

## Files and Directories

- `main.cc`: Main program file
- `response.h`: Header file with class definitions
- `response.cc`: Implementation file
- `Makefile`: Build configuration
- `test1/` and `test2/`: Test directories containing:
  - `input.txt`: Keyword-response-emotion tuples
  - `message.txt`: Input messages
  - `result.txt`: Expected output

## Program Flow

1. Read keyword-response pairs from first input file
2. Process each message from second input file
3. For each message:
   - Check for keywords
   - Generate appropriate responses based on emotional state
   - Handle multiple keyword matches
4. Store responses in output file

## Testing

Test the implementation using the provided test cases:
```bash
make
./ai test1/input.txt test1/message.txt output.txt
```

Compare output with corresponding result.txt files.

## Important Notes

- Do not modify provided skeleton code
- Look for "TODO" comments for implementation points
- Code must compile with provided Makefile on ix-dev
- Understand the C++ class hierarchy and inheritance
- Handle multiple keyword matches in messages

## Submission

1. Complete implementation of all required classes and methods
2. Test thoroughly with provided test cases
3. Verify output matches expected results
4. Commit and push to Bitbucket
5. Verify submission on Bitbucket website 