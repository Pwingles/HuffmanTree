
````markdown
# Project 3 — Part 2 : Binary Search Tree & Word Frequencies  
**CS 315 – Data Structures**  
**Author:** P. Wingles  
**Repository:** [HuffmanPart2 (GitHub)](https://github.com/Pwingles/HuffmanPart2/tree/master)

---

## 🧩 Overview
Part 2 extends Part 1’s tokenization system into a full **Binary Search Tree (BST)**–based frequency analyzer.  
The program reads a text file, tokenizes the contents into words, builds a BST to count occurrences,  
and produces two output files per input:

1. `<base>.tokens` – every token extracted from the text (from Part 1)  
2. `<base>.freq` – alphabetically sorted words with their corresponding counts  

This stage provides the structured word-frequency data used later for Huffman coding.

---

## 🧠 Concepts & Goals
- **Data Structures:** Binary Search Tree (`BinSearchTree`) and custom nodes (`TreeNode`)  
- **Algorithms:** In-order traversal for alphabetic output  
- **File I/O:** Read `.txt`, write `.tokens` and `.freq`  
- **Utility Modules:** `Scanner`, `PriorityQueue`, `utils`  
- **Deterministic Behavior:** Tokens are shuffled with seed `0xC0FFEE` before insertion for reproducible results  

---

## ⚙️ Build & Run Instructions

### Compile manually
```bash
g++ -std=c++20 -Wall *.cpp -o p3_part2.x
````

### Run on a single file

```bash
./p3_part2.x input_output/the_call_of_the_wild.txt
```

This generates:

```
input_output/the_call_of_the_wild.tokens
input_output/the_call_of_the_wild.freq
```

### Verify against instructor reference

```bash
diff -u input_output/the_call_of_the_wild.freq \
  /home/faculty/kooshesh/cs315_fall2025/project3/part2/freq/the_call_of_the_wild.freq
```

✅ No output from `diff` ⇒ files match perfectly.

---

## 🧪 Testing on Blue

1. Copy the provided scripts:

```bash
cp /home/faculty/kooshesh/cs315_fall2025/project3/part2/copy_files.bash .
cp /home/faculty/kooshesh/cs315_fall2025/project3/part2/compile_and_test_project3_part2.bash .
```

2. Copy sample inputs:

```bash
bash copy_files.bash
```

3. Compile + run + compare all:

```bash
bash compile_and_test_project3_part2.bash
```

Expected output:

```
tokens matches
freq matches
Summary: 20 match(es), 0 diff(s)
```

---

## 🧱 Core Components

| File                       | Description                                                                                           |
| -------------------------- | ----------------------------------------------------------------------------------------------------- |
| **main.cpp**               | Controls overall flow: tokenization → BST build → frequency file output                               |
| **BinSearchTree.h / .cpp** | Implements BST with `insert`, `bulkInsert`, `inorderCollect`, `contains`, `countOf`, `height`, `size` |
| **TreeNode.h**             | Defines node structure (word + frequency + links)                                                     |
| **PriorityQueue.h / .cpp** | Stores `TreeNode*` by frequency (prep for Part 3 Huffman coding)                                      |
| **Scanner.hpp / .cpp**     | Reads and tokenizes input text                                                                        |
| **utils.hpp / .cpp**       | Error-checking and file-I/O helpers                                                                   |
| **CMakeLists.txt**         | Build configuration for CLion / CMake                                                                 |

---

## 📊 Program Output Example

```bash
./p3_part2.x input_output/the_toil_of_trace_and_trail.txt
```

Output:

```
BST height: 28
BST unique words: 1432
Total tokens: 5471
Min frequency: 1
Max frequency: 371
```

Files produced:

```
input_output/the_toil_of_trace_and_trail.tokens
input_output/the_toil_of_trace_and_trail.freq
```

---

## ✅ Verification Status

All reference comparisons pass on Blue:

```
Summary: 20 match(es), 0 diff(s)
```

This confirms tokenization, BST logic, and `.freq` formatting are correct and ready for Part 3.

---

## 📦 Project Structure

```
Project3_Part2/
├── BinSearchTree.cpp / .h
├── PriorityQueue.cpp / .h
├── Scanner.cpp / .hpp
├── TreeNode.h
├── utils.cpp / .hpp
├── main.cpp
├── CMakeLists.txt
├── input_output/
│   ├── *.txt
│   ├── *.tokens
│   └── *.freq
├── compile_and_test_project3_part2.bash
└── copy_files.bash
```

---

## 🧾 Notes

* BST insertion order is randomized with a fixed seed for consistent grading.
* `.freq` output format matches instructor spec:

  ```
         <right-aligned count> <word>
  ```

  (10-character padded numeric field).

---

## 🔗 Repository

**GitHub:** [https://github.com/Pwingles/HuffmanPart2/tree/master](https://github.com/Pwingles/HuffmanPart2/tree/master)

---


## 📚 Sources
- **Instructor-provided base code and project specifications**  
  `/home/faculty/kooshesh/cs315_fall2025/project3/part2/`  

- **C++ References:**  
  - [cppreference.com – std::filesystem](https://en.cppreference.com/w/cpp/filesystem)  
  - [cppreference.com – std::vector](https://en.cppreference.com/w/cpp/container/vector)  
  - [cppreference.com – std::ofstream](https://en.cppreference.com/w/cpp/io/basic_ofstream)  
- **Testing Environment:** Blue Linux server (CS 315)  
- **ChatGPT** Generating README.md - Proofread after by me
- **Author’s GitHub Repository:**  
  [https://github.com/Pwingles/HuffmanPart2/tree/master](https://github.com/Pwingles/HuffmanPart2/tree/master)



