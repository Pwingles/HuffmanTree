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
    
    // TODO: Implement Huffman tree construction algorithm
    // While queue has at least 2 items:
    //   - Extract two minimum nodes
    //   - Create internal node with combined frequency
    //   - Insert internal node back into queue
    // When one node remains, that's the root
    
    HuffmanTree tree;
    // tree.root_ = ... (set to final remaining node)
    return tree;
}

// Destructor - deletes the entire Huffman tree
HuffmanTree::~HuffmanTree() {
    // TODO: Implement this function
    
}

// Build a vector of (word, code) pairs by traversing the Huffman tree
void HuffmanTree::assignCodes(std::vector<std::pair<std::string,std::string>>& out) const {
    // TODO: Implement this function
    
}

// Header writer (pre-order over leaves; "word<space>code"; newline at end)
error_type HuffmanTree::writeHeader(std::ostream& os) const {
    // TODO: Implement this function
    
}

// Encode a sequence of tokens using the codebook derived from this tree
error_type HuffmanTree::encode(const std::vector<std::string>& tokens,
                               std::ostream& os_bits,
                               int wrap_cols) const {
    // TODO: Implement this function
    
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
    // TODO: Implement this function
    
}

// Helper: pre-order traversal for header writing
void HuffmanTree::writeHeaderPreorder(const TreeNode* n, std::ostream& os,
                                     std::string& prefix) {
    // TODO: Implement this function
    
}
