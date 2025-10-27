//
// Created by Kevin Rodriguez on 10/15/25.
//

#include "HuffmanTree.h"
#include "PriorityQueue.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <fstream>

// Static factory method to build HuffmanTree from word counts
HuffmanTree HuffmanTree::buildFromCounts(const std::vector<std::pair<std::string,int>>& counts) {
    // Convert (word, count) pairs to TreeNode* objects
    std::vector<TreeNode*> nodes;
    for (const auto& [word, freq]: counts) {
        TreeNode* node = new TreeNode(word);
        node->freq = freq;
        nodes.push_back(node);
    }
    
    // Create PriorityQueue with the nodes
    PriorityQueue pq(nodes);
    
    //While more than one node exists, extract and combine
    while(pq.size() > 1) {
        // Extract 2 values and sum their frequencies
        TreeNode* a = pq.extractMin();
        TreeNode* b = pq.extractMin();

        TreeNode* parent = new TreeNode("");
        parent->freq = a->freq + b->freq;
        parent->key_word = min(a->key_word, b->key_word);
        parent->left = a;   // b as left child (matches reference implementation)
        parent->right = b;  // a as right child (matches reference implementation) 

        pq.insert(parent);
    }

    //Create the huffman tree and pass it the root node
    HuffmanTree tree;
    tree.root_ = pq.extractMin(); //last node
    return tree;
}

// Destructor - deletes the entire Huffman tree
HuffmanTree::~HuffmanTree() {
    destroy(root_);
}

// Build a vector of (word, code) pairs by traversing the Huffman tree
void HuffmanTree::assignCodes(std::vector<std::pair<std::string,std::string>>& out) const {
    out.clear();
    if(root_ == nullptr){
        return;
    }
    std::string prefix = "";
    assignCodesDFS(root_, prefix, out);
}

// Header writer (pre-order over leaves; "word<space>code"; newline at end)
error_type HuffmanTree::writeHeader(std::ostream& os) const {
    if(root_ == nullptr) {
        return NO_ERROR;
    }
    std::string prefix = "";
    writeHeaderPreorder(root_, os, prefix);
    return NO_ERROR;
}

// Encode a sequence of tokens using the codebook derived from this tree
error_type HuffmanTree::encode(const std::vector<std::string>& tokens,
                               std::ostream& os_bits,
                               int wrap_cols) const {
    

    // Build the codebook
    std::vector<std::pair<std::string, std:: string>> codebook;
    assignCodes(codebook);

    //Unordered map named codes
    std::unordered_map<std::string, std::string> codes;


    // Read the codebook now
    for (auto& [word, code] : codebook) {
        codes[word] = code; // map the word to its code
    }

    //Encode each word
    std::string encodedWords = "";
    for (const std::string& token : tokens) {
        encodedWords += codes[token]; //Grabs codes["the"] returns its code example: "101010" 
    }

    // Write the continuous encoded message out with 80 line limit
    int lineLength = 0;
    for (char bit : encodedWords) {
        os_bits << bit;
        lineLength++;

        //Size 80 is default for program
        if(lineLength == wrap_cols) {
            os_bits << '\n';
            lineLength = 0;
        }
    }
    
    //  end with new line 
    if (lineLength > 0) {
        os_bits << '\n';
    }

    return NO_ERROR;
}

// Helper: destroy the entire tree
void HuffmanTree::destroy(TreeNode* n) noexcept {
    if(n == nullptr) {
        return;
    }
    
    destroy(n->left);
    destroy(n->right);
    delete n;
}

// Helper: DFS traversal to assign codes
void HuffmanTree::assignCodesDFS(const TreeNode* n,
                                 std::string& prefix,
                                 std::vector<std::pair<std::string,std::string>>& out) {
                                    
        // Nothing left
        if(n == nullptr) {
            return;
        }   
        
        // This is if we hit a leaf node add it to out
        if(n->left == nullptr && n->right == nullptr){
            std::string code = prefix.empty() ? "0" : prefix; // single-word edge case
            out.push_back({n->key_word, code});
            return; // go back to previous call
        }

        // Goes all the way left until tree node
        if(n->left != nullptr) {
            prefix.push_back('0');
            assignCodesDFS(n->left, prefix, out);
            prefix.pop_back(); // Remove 0 we just added (backtrack then go right)
        }
        
        // Goes right by 1, then recursively goes all the way left above until it goes right again
        if(n->right !=nullptr) {
            prefix.push_back('1');
            assignCodesDFS(n->right, prefix, out);
            prefix.pop_back(); // Remove 1 we just added (back track)
        }

}

// Helper: pre-order traversal for header writing
// Write to .hdr file in which we word <Space> code
// WORD | CODE
// wolf 1011

void HuffmanTree::writeHeaderPreorder(const TreeNode* n, std::ostream& os,
                                     std::string& prefix) {
    
    if(n == nullptr) {
        return;
    }

    // Check if this is a leaf node (both children are nullptr)
    if(n->left == nullptr && n->right == nullptr) {
        std::string code = prefix.empty() ? "0" : prefix; // single-word edge case
        os << n->key_word << ' ' << code << '\n';
        return;
    }
    
    // Traverse left subtree (add '0' to code)
    if (n->left != nullptr) {
        prefix.push_back('0');
        writeHeaderPreorder(n->left, os, prefix);
        prefix.pop_back(); // backtrack
    }
    
    // Traverse right subtree (add '1' to code)
    if (n->right != nullptr) {
        prefix.push_back('1');
        writeHeaderPreorder(n->right, os, prefix);
        prefix.pop_back(); // backtrack
    }
}
