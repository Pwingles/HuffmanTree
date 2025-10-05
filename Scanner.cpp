//
// Created by Ali Kooshesh on 9/27/25.
//

#include "Scanner.hpp"

#include <utility>
#include <iostream>
#include <fstream>
#include "utils.hpp"

/* Helper functions */


/**
 * Anonymous namespace for internal helper functions.
 * These functions are not exposed outside this file.
 */
namespace {


inline bool is_ascii(unsigned char uc) {
    return uc <= 127;
}

inline bool is_ascii_letter(unsigned char uc) {
    return (uc >= 'a' && uc <= 'z') || (uc >= 'A' && uc <= 'Z');
}

inline bool is_apostrophe(char c) {
    return c == '\'';
}

inline char to_lower_ascii(unsigned char uc) {
    // Safe for ASCII letters; uc is already unsigned to avoid UB.
    return static_cast<char>(std::tolower(uc));
}

// Trim any leading/trailing apostrophes (safety net for cases like "'tis" or "rock'")
inline void strip_outer_apostrophes(std::string& s) {
    std::size_t i = 0, j = s.size();
    while (i < j && s[i] == '\'') ++i;
    while (j > i && s[j - 1] == '\'') --j;
    if (i != 0 || j != s.size()) s = s.substr(i, j - i);
}

// Consume characters until an ASCII letter is found or EOF.
// If found, writes the first lowercased letter to out_first and returns true.
// If EOF encountered without finding a letter, returns false.
inline bool skip_to_next_letter(std::istream& in, char& out_first) {
    int ci;
    while ((ci = in.get()) != EOF) {
        unsigned char uc = static_cast<unsigned char>(ci);
        if (!is_ascii(uc)) {
            continue;
        }
        if (is_ascii_letter(uc)) {
            out_first = to_lower_ascii(uc);
            return true;
        }
    }
    return false;
}

} // End of namespace




// Constructor: just stores the input path
Scanner::Scanner(std::filesystem::path inputPath)
    : inputPath_(std::move(inputPath)) {}

// Tokenize into memory
error_type Scanner::tokenize(std::vector<std::string> &words) {
    namespace fs = std::filesystem;

    if (inputPath_.has_parent_path() && !fs::exists(inputPath_.parent_path())) {
        return DIR_NOT_FOUND;
    }
    if (!fs::exists(inputPath_)) {
        return FILE_NOT_FOUND;
    }

    std::ifstream in(inputPath_, std::ios::binary);
    if (!in) {
        return UNABLE_TO_OPEN_FILE;
    }

    words.clear();


    // A different way to do while(true)
    for (;;) {
        std::string w = readWord(in);
        if (w.empty()) {
            if (!in.good()) break;   // EOF reached
            continue;                // skip separators
        }
        words.push_back(std::move(w));
    }

    return NO_ERROR;
}

// Tokenize and also write one token per line to outputFile
error_type Scanner::tokenize(std::vector<std::string> &words,
                             const std::filesystem::path &outputFile) {
    error_type err = tokenize(words);
    if (err != NO_ERROR) return err;

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) return UNABLE_TO_OPEN_FILE_FOR_WRITING;

    for (const std::string &tok : words) {
        out << tok << '\n';
        if (!out) return FAILED_TO_WRITE_FILE;
    }
    // File ends with a single trailing newline (done by the loop above)
    return NO_ERROR;
}



/**
 * Reads the next word-like token from the input stream.
 *
 * How it works:
 * - Skips over anything that's not a letter until it finds a letter.
 * - Starts building a word from that letter.
 * - Keeps adding letters, and only keeps apostrophes if they're inside the word (not at the start or end).
 * - Stops when it hits a separator (like punctuation, space, or non-ASCII character).
 * - Converts all letters to lowercase.
 * - Removes apostrophes at the start or end of the word.
 *
 * @param in The input stream to read from (e.g., a file or string stream).
 * @return The next cleaned word as a string, or an empty string if there are no more words.
 */
std::string Scanner::readWord(std::istream& in) {
    std::string token;

    // Step 1: Skip non-letter characters until a letter is found.
    char first;
    if (!skip_to_next_letter(in, first)) {
        return {}; // No more tokens in the stream.
    }
    token.push_back(first); // Start the token with the first letter.

    // Step 2: Build the token by reading letters and valid apostrophes.
    // Only allow apostrophes if they are inside the word (not at the start or end).
    for (;;) {
        int pk = in.peek();
        if (pk == EOF) break; // End of stream.

        unsigned char uc = static_cast<unsigned char>(pk);

        // If the next character is not ASCII, treat it as a separator and consume it.
        if (!is_ascii(uc)) {
            in.get(); break;
        }

        // If it's a letter, consume and add to the token (convert to lowercase).
        if (is_ascii_letter(uc)) {
            in.get();
            token.push_back(to_lower_ascii(uc));
            continue;
        }

        // If it's an apostrophe, only keep it if followed by a letter (internal apostrophe).
        if (is_apostrophe(static_cast<char>(uc))) {
            in.get(); // Consume apostrophe.
            int next = in.peek();
            if (next != EOF && is_ascii_letter(static_cast<unsigned char>(next))) {
                token.push_back('\''); // Keep apostrophe inside the word.
                continue; // Next loop will consume the letter.
            } else {
                // Apostrophe not followed by a letter: treat as trailing, end token.
                break;
            }
        }

        // Any other character (digit, whitespace, punctuation, etc.) ends the token.
        break;
    }

    // Step 3: Remove any leading or trailing apostrophes for safety.
    strip_outer_apostrophes(token);
    return token; // Return the cleaned word.
}

