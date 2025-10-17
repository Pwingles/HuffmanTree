#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "BinSearchTree.h"
#include "TreeNode.h"
#include "PriorityQueue.h"
#include "Scanner.hpp"
#include "utils.hpp"
#include <algorithm>
#include <random>
#include <climits> // For INT_MAX
#include <iomanip>


int main(int argc, char* argv[]) {

    // Command Line check
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_output/<base>.txt>\n";
        return 1;
    }   


    /**
     * Path setup
     * inPath: input_output/call_of_the_wild.txt
     * dir: input_output
     * base: call_of_the_wild
     * tokensPath: input_output/call_of_the_wild.tokens
     */

    // The instructor passes just the base filename (like "the_toil_of_trace_and_trail.txt")
    // so we prepend "input_output/" automatically.
    namespace fs = std::filesystem;
    const fs::path dir = "input_output";
    const fs::path inPath = dir / argv[1];
    const std::string base = inPath.stem().string();


    // Derived file for Part 1 (.tokens)
    const fs::path tokensPath = dir / (base + ".tokens");




    // SAFTEY CHECKS
    // Pre-flight checks using your utils (as your starter did)
    if (error_type st; (st = regularFileExistsAndIsAvailable(inPath.string())) != NO_ERROR)
        exitOnError(st, inPath.string());
    if (error_type st; (st = directoryExists(dir.string())) != NO_ERROR)
        exitOnError(st, dir.string());
    if (error_type st; (st = canOpenForWriting(tokensPath.string())) != NO_ERROR)
        exitOnError(st, tokensPath.string());

    // Scanning and writing
    std::vector<std::string> words;
    Scanner scanner(inPath); // IMPORTANT: pass the INPUT .txt here

    // Option A (keep your utils writer):
    if (error_type st; (st = scanner.tokenize(words)) != NO_ERROR)
        exitOnError(st, inPath.string());
    if (error_type st; (st = writeVectorToFile(tokensPath.string(), words)) != NO_ERROR)
        exitOnError(st, tokensPath.string());



    // Part 2 TESTING
    // BinSearchTree Section
    // Testing BinSearchTree Function
    std::vector<std::string> tokens; // holds tokens
    std::ifstream inTokens(tokensPath);
    std::string word;

    // Read in all tokens from the .tokens file and push them into the tokens vector
    while (inTokens >> word) {
        tokens.push_back(word);
    }

    // Shuffle the tokens to simulate random insertion (Used Provided Seed in project spec)
    constexpr unsigned SEED = 0xC0FFEE;
    std::mt19937 rng(SEED);
    std::shuffle(tokens.begin(), tokens.end(), rng);

    // Build the binary search tree
    BinSearchTree bst;
    bst.bulkInsert(tokens);

    // In-order traversal to collect words and counts
    std::vector<std::pair<std::string, int>> wordCounts;
    // Should be sorted alphabetically with this call
    bst.inorderCollect(wordCounts);

    // frequency
    int minFreq = INT_MAX;
    int maxFreq = 0;

    // Calculate min and max frequency
    for (const std::pair<std::string, int>& word : wordCounts) {
        minFreq = std::min(minFreq, word.second);
        maxFreq = std::max(maxFreq, word.second);
    }
    // Print out results
    std::cout << "BST height: " << bst.height() << "\n";
    std::cout << "BST unique words: " << bst.size() << "\n";
    std::cout << "Total tokens: " << tokens.size() << "\n";
    std::cout << "Min frequency: " << minFreq << "\n";
    std::cout << "Max frequency: " << maxFreq << "\n";


    /**
     * Priority Queue Section
    */

    // Convert std::vector<<std::pair<std::string, int>> wordCounts; to a vector<TreeNodes*>  to pass into PriorityQueue constructor
    std::vector<TreeNode*> nodes;
    for (const auto& [word, freq]: wordCounts) {
        TreeNode* node = new TreeNode(word); // Create a new node with values from wordCounts
        node -> freq = freq;
        nodes.push_back(node);
    }



    // === Write <base>.freq next to the .tokens file ===
    const fs::path freqPath = dir / (base + ".freq");

    // safety check like you did for .tokens
    if (error_type st; (st = canOpenForWriting(freqPath.string())) != NO_ERROR)
        exitOnError(st, freqPath.string());

    // write: one "word count" per line, alphabetical from inorderCollect
    std::ofstream freqOut(freqPath);
    for (const auto& [w, c] : wordCounts) {
        freqOut << std::setw(10) << c << ' ' << w << '\n';
    }
    freqOut.close();

    // Create a PriorityQueue with the nodes
    PriorityQueue pq(nodes);


    // Print the PriorityQueue testing purposes
   // pq.print();

    
 


    return 0;
}








/**
 * OLD Testing code
 *
 *
 *
*
    // Output testing PART 1 of program
    std::cout << "Tokenization complete. " << words.size() << " tokens found.\n";
    std::cout << "Tokens written to: " << tokensPath << "\n";
    std::cout << "----------------------------------------\n";


 *  //test countOf, and contains
    if (bst.contains("the")) {
        std::cout << "The word 'the' is in the tree.\n";

        // Access the count using .value().
        auto wordCount = bst.countOf("the").value();
        std::cout << "The word 'the' appears " << wordCount << " times.\n";
    }
    else
        std::cout << "The word 'the' is NOT in the tree.\n";



// Print out first 15 words to make sure it works.
    for (int i = 0; i < 15; ++i) {
        std::cout << wordCounts[i].first << " " << wordCounts[i].second << "\n";
    }
 *
 *
 *
 */