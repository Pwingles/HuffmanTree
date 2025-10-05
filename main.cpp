#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Scanner.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_output/<base>.txt>\n";
        return 1;
    }

    namespace fs = std::filesystem;
    const fs::path inPath = argv[1];

    // Directory and base name
    const fs::path dir  = inPath.parent_path();     // e.g., "input_output"
    const std::string base = inPath.stem().string(); // e.g., "call_of_the_wild"

    // Derived file for Part 1 (.tokens)
    const fs::path tokensPath = dir / (base + ".tokens");

    // Pre-flight checks using your utils (as your starter did)
    if (error_type st; (st = regularFileExistsAndIsAvailable(inPath.string())) != NO_ERROR)
        exitOnError(st, inPath.string());
    if (error_type st; (st = directoryExists(dir.string())) != NO_ERROR)
        exitOnError(st, dir.string());
    if (error_type st; (st = canOpenForWriting(tokensPath.string())) != NO_ERROR)
        exitOnError(st, tokensPath.string());

    // Scan
    std::vector<std::string> words;
    Scanner scanner(inPath); // IMPORTANT: pass the INPUT .txt here

    // Option A (keep your utils writer):
    if (error_type st; (st = scanner.tokenize(words)) != NO_ERROR)
        exitOnError(st, inPath.string());
    if (error_type st; (st = writeVectorToFile(tokensPath.string(), words)) != NO_ERROR)
        exitOnError(st, tokensPath.string());

    // Option B (also fine): use Scanner’s overload to write the file directly
    // if (error_type st; (st = scanner.tokenize(words, tokensPath)) != NO_ERROR)
    //     exitOnError(st, tokensPath.string());

    return 0;
}
