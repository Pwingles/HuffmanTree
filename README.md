

# CS 315 — Project 3: Huffman Coding (Final Version)
**Student:** Kevin Rodriguez  
**Instructor:** Prof. Ali Kooshesh  
**Semester:** Fall 2025  
**Student ID:** 008858727  
**Course:** CS 315 – Data Structures  
**Repository:** [https://github.com/Pwingles/Huffman](https://github.com/Pwingles/Huffman)

---

## Overview

This project implements a complete Huffman Coding system developed in three structured phases:

1. **Scanner (Tokenization)** – reads and extracts normalized word tokens from text files.  
2. **Binary Search Tree (BST) & Frequency Analysis** – counts token frequencies using a BST.  
3. **Huffman Coding** – constructs a Huffman tree and generates variable-length binary codes for compression.

Each phase builds upon the previous one, forming a pipeline that transforms plain text into compressed Huffman-encoded data.

---

## Phase 1 – Scanner: Tokenization

### Purpose
Implements a tokenizer that converts input text into normalized word tokens.

### Features
- Converts all input to lowercase.
- Extracts valid word tokens with optional internal apostrophes.
- Removes punctuation, digits, and non-alphabetic symbols.
- Writes one token per line to a `.tokens` file.

### Example Run
```bash
./huffman_part1 input_output/the_call_of_the_wild.txt
````

Output:

```
input_output/the_call_of_the_wild.tokens
```

Example token output:

```
buck
was
born
to
freedom
```

---

## Phase 2 – Binary Search Tree & Frequency Analysis

### Purpose

Builds a Binary Search Tree to store unique words and track their frequencies.

### Features

* Randomized insertion order (seed = `0xC0FFEE`) for deterministic results.
* In-order traversal for alphabetically sorted output.
* Outputs `.freq` file showing each word and its frequency.
* Displays BST height, total token count, and unique word count.
* Matches instructor reference outputs exactly.

### Example Run

```bash
./p3_part2.x input_output/the_call_of_the_wild.txt
```

Produces:

```
input_output/the_call_of_the_wild.tokens
input_output/the_call_of_the_wild.freq
```

Example `.freq` file:

```
        371 the
         92 of
         87 and
          1 camp's
```

---

## Phase 3 – Huffman Coding (Final Phase)

### Purpose

Implements Huffman’s algorithm to generate optimal prefix-free binary codes based on word frequency.

### Process

1. Reads `.freq` file from Phase 2.
2. Inserts words and frequencies into a min-priority queue.
3. Builds a Huffman Tree by merging the two least-frequent nodes repeatedly.
4. Assigns binary codes (`0` and `1`) to each unique word.
5. Produces:

   * `<base>.codetable` – mapping of words to binary codes
   * `<base>.huff` – compressed binary representation of the input text

### Example Code Table

```
the        → 10
of         → 110
and        → 111
camp's     → 011010
```

### Example Run

```bash
./p3_complete.x input_output/the_call_of_the_wild.txt
```

Output files:

```
input_output/the_call_of_the_wild.tokens
input_output/the_call_of_the_wild.freq
input_output/the_call_of_the_wild.codetable
input_output/the_call_of_the_wild.huff
```

---

## Build Instructions

### Compile

```bash
g++ -std=c++20 -Wall *.cpp -o huffman_final.x
```

### Run

```bash
./huffman_final.x input_output/the_call_of_the_wild.txt
```

---

## Testing and Verification

### Provided Scripts

```bash
bash compile_and_test.bash
bash compile_and_test_project3_part2.bash
bash compile_and_test_project3_final_version.bash
```

### Expected Output

```
tokens match
freq match
codetable match
huff match
Summary: All phases verified successfully.
```

All tests were executed successfully on the Blue (Sonoma) environment.

---

## Project Structure

```
Huffman/
├── input_output/
│   ├── *.txt
│   ├── *.tokens
│   ├── *.freq
│   ├── *.codetable
│   └── *.huff
├── BinSearchTree.cpp
├── BinSearchTree.h
├── PriorityQueue.cpp
├── PriorityQueue.h
├── HuffmanTree.cpp
├── HuffmanTree.h
├── TreeNode.h
├── Scanner.cpp
├── Scanner.hpp
├── utils.cpp
├── utils.hpp
├── main.cpp
├── compile_and_test.bash
├── compile_and_test_project3_part2.bash
├── compile_and_test_project3_final_version.bash
├── copy_files.bash
├── CMakeLists.txt
└── README.md
```

---

## Core Components

| File                       | Description                                                      |
| -------------------------- | ---------------------------------------------------------------- |
| **Scanner.cpp / .hpp**     | Tokenizes input text and generates `.tokens`                     |
| **BinSearchTree.cpp / .h** | Builds and manages BST for frequency counting                    |
| **PriorityQueue.cpp / .h** | Manages nodes ordered by frequency for Huffman tree construction |
| **HuffmanTree.cpp / .h**   | Implements Huffman encoding and code table generation            |
| **TreeNode.h**             | Defines structure for tree nodes (word, frequency, links)        |
| **utils.cpp / .hpp**       | Handles error checking, file I/O, and formatting                 |
| **main.cpp**               | Coordinates all phases in order: Scanner → BST → Huffman         |

---

## Sources and References

* Instructor-provided base code and project specifications.
* [C++ Reference](https://en.cppreference.com/) for `std::filesystem`, file I/O.
* Stack Overflow for algorithmic and debugging clarification.
* ChatGPT used for formatting README and suggesting function prototypes (no code generation).
* Testing performed on the Blue Linux Server (CS 315 environment).
* Algorith Structures provided by Instructor
* *.h Files provided my Instructor


---

## Summary

| Phase | Focus               | Output                | Verified |
| ----- | ------------------- | --------------------- | -------- |
| **1** | Tokenizer (Scanner) | `.tokens`             | Yes      |
| **2** | Binary Search Tree  | `.freq`               | Yes      |
| **3** | Huffman Coding      | `.codetable`, `.huff` | Yes      |

All components compile, execute, and match instructor reference outputs.


