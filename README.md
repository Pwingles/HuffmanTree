#  Project 3 – Part 1: **Scanner**
**Course:** CS 315 — Fall 2025  
**Student:** Kevin Rodriguez 
**Student ID:** 008858727
**Instructor:** Prof. Ali Kooshesh

---

## 📘 Overview
This project implements the **tokenization phase** of a Huffman-coding pipeline.  
The program reads a plain-text input file, normalizes it to lowercase, extracts valid **word tokens** according to the project specification, and writes each token on its own line to a `.tokens` file in the same directory.

This submission covers **Part 1 – Scanner** only.  
Later phases (BST, frequency list, Huffman tree) will build upon this component.

---

## ⚙️ Build Instructions
Compile all source files with **C++20** support:

```bash
g++ -std=c++20 -Wall *.cpp -o huffman_part1
```

---

## ▶️ Run Instructions
Run the executable with **exactly one argument**, the path to an input `.txt` file in the `input_output/` directory:

```bash
./huffman_part1 input_output/the_call_of_the_wild.txt
```

### Example Output Files
After successful execution, the following file will be created:

```
input_output/the_call_of_the_wild.tokens
```

Each line in `.tokens` contains a single lowercase word token, stripped of punctuation, digits, dashes, and non-ASCII characters, with only internal apostrophes preserved (e.g., `camp's`, `o'keefe`).

---

## 🧩 Tokenization Rules (Summary)
- Convert input to lowercase (ASCII only).
- Valid tokens: `[a–z]+` or `[a–z]+’[a–z]+` (apostrophe only between letters).
- Treat digits, punctuation, quotes, whitespace, and dashes as separators.
- Remove leading/trailing apostrophes.
- Write **exactly one token per line**, end file with a newline.
- Return appropriate `error_type` values on failure.

---

## 🧪 Testing
The project was compiled and tested on **blue** using the provided scripts:

```bash
bash compile_and_test.bash the_call_of_the_wild.txt
```

Output matched the reference results (no `diff` output).

---

## 📁 Project Structure
```
project3_part1/
├── main.cpp
├── Scanner.cpp
├── Scanner.hpp
├── utils.cpp
├── utils.hpp
├── README.md
└── input_output/
    ├── the_call_of_the_wild.txt
    └── the_call_of_the_wild.tokens
```

---

## 🧾 Error Handling
- **FILE_NOT_FOUND**, **DIR_NOT_FOUND**, **UNABLE_TO_OPEN_FILE**
- **UNABLE_TO_OPEN_FILE_FOR_WRITING**, **FAILED_TO_WRITE_FILE**
- Prints human-readable message to `stderr` and exits non-zero.

---

## ✅ Verification
- Successfully produces identical `.tokens` outputs to instructor references.
- Matches tokenization examples from the project description.

# 🖥️ Proof of Successful Execution

Below is a transcript of my test runs on blue showing successful compilation,
execution, and matching outputs (no differences found by the provided test script).

```
Last login: Sun Oct  5 08:46:04 2025 from 
krodriguez@blue:~$ cd project3_part1/
krodriguez@blue:~/project3_part1$ g++ -std=c++20 -Wall *.cpp -o huffman_part1
krodriguez@blue:~/project3_part1$ ./huffman_part1 input_output/call_of_the_wild.txt
Error: File input_output/call_of_the_wild.txt doesn't exist. Terminating...
krodriguez@blue:~/project3_part1$ ./huffman_part1 input_output/the_call_of_the_wild.txt
krodriguez@blue:~/project3_part1$ ls input_output/
for_the_love_of_a_man.txt  into_the_primitive.txt  sample.txt                         TheBells.tokens  the_call_of_the_wild.tokens  the_dominant_primordial_beast.txt  the_sounding_of_the_call.txt     who_has_won_to_mastership.tokens
into_the_primitive.tokens  sample.tokens           tableOfContents_TheCallOfWild.txt  TheBells.txt     the_call_of_the_wild.txt     the_law_of_club_and_fang.txt       the_toil_of_trace_and_trail.txt  who_has_won_to_mastership.txt
krodriguez@blue:~/project3_part1$ pwd
/home/student/krodriguez/project3_part1
krodriguez@blue:~/project3_part1$ find . -name "*.tokens"
./input_output/TheBells.tokens
./input_output/the_call_of_the_wild.tokens
./input_output/into_the_primitive.tokens
./input_output/sample.tokens
./input_output/who_has_won_to_mastership.tokens
krodriguez@blue:~/project3_part1$ bash compile_and_test.bash the_call_of_the_wild.txt
Compiling project...
Running program with input file 'input_output/the_call_of_the_wild.txt'...
diff input_output/the_call_of_the_wild.tokens /home/faculty/kooshesh/cs315_f2025_p3_part1/part1_tokens_files//the_call_of_the_wild.tokens
krodriguez@blue:~/project3_part1$ bash compile_and_test.bash into_the_primitive.txt
Compiling project...
Running program with input file 'input_output/into_the_primitive.txt'...
diff input_output/into_the_primitive.tokens /home/faculty/kooshesh/cs315_f2025_p3_part1/part1_tokens_files//into_the_primitive.tokens
krodriguez@blue:~/project3_part1$ bash compile_and_test.bash who_has_won_to_mastership.txt
Compiling project...
Running program with input file 'input_output/who_has_won_to_mastership.txt'...
diff input_output/who_has_won_to_mastership.tokens /home/faculty/kooshesh/cs315_f2025_p3_part1/part1_tokens_files//who_has_won_to_mastership.tokens
krodriguez@blue:~/project3_part1$
```

---

# Sources
📚 Sources & Links
- Most Code written by me, Kevin Rodriguez

Other code snippets and logic were inspired by:
- [C++ Reference](https://cplusplus.com/doc/tutorial/files/) – File I/O in C++
- ChatGPT - Used for Generating a clean README template
- ChatGPT - As my code was getting messy I asked it to make helper function headers (no code) in which
I could fill in the logic myself to keep my code clean and organized.

**I learned more about casting**

| Reason for cast                | Example                                | Why it matters                               |
| ------------------------------ | -------------------------------------- | -------------------------------------------- |
| Make bytes non-negative        | `unsigned char uc = (unsigned char)c;` | Avoid negative values for non-ASCII bytes    |
| Feed safely to ctype functions | `std::tolower(uc)`                     | Prevent undefined behavior                   |
| Compare against ASCII range    | `uc <= 127`, `uc >= 'A' && uc <= 'Z'`  | Guarantees consistent results across systems |

---

**Acknowledgments:**  
Starter project framework and utilities provided by Prof. Ali Kooshesh.  
