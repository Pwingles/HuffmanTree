//
// Created by Kevin Rodriguez on 10/15/25.
//

#include "BinSearchTree.h"
#include "TreeNode.h"
#include <string>
#include <vector>
#include <utility>
#include <optional>
#include <string_view>
#include <iostream>

// ================================
// Constructor / Destructor
// ================================
BinSearchTree::~BinSearchTree() {
    destroy(root_);
    root_ = nullptr;
}





// ================================
// Public member functions
// ================================

void BinSearchTree::insert(const std::string& word) {
    // root_ is always the top of the tree
    root_ = insertHelper(root_, word);
}






void BinSearchTree::bulkInsert(const std::vector<std::string>& words) {
    // Loop over each word and insert it into the tree
    for (const std::string& word : words) {
        insert(word);
    }
}





// return true if found, false if not
bool BinSearchTree::contains(std::string_view word) const noexcept {
    return findNode(root_, word) != nullptr;
}




std::optional<int> BinSearchTree::countOf(std::string_view word) const noexcept {

    if (contains(word)) {
        return findNode(root_, word)->freq;
    }
    return std::nullopt;

}

void BinSearchTree::inorderCollect(std::vector<std::pair<std::string, int>>& out) const {
    inorderHelper(root_, out);
}

std::size_t BinSearchTree::size() const noexcept {
    return sizeHelper(root_);
}

unsigned BinSearchTree::height() const noexcept {
    return heightHelper(root_);
}






// ================================
// Private static helper functions
// =================================

void BinSearchTree::destroy(TreeNode* node) noexcept {
    if (node == nullptr) {
        return;
    }
    destroy(node->left);
    destroy(node->right);
    delete node;
}

TreeNode* BinSearchTree::insertHelper(TreeNode* node, const std::string& word) {

    if (node == nullptr) {
        return new TreeNode(word); // Create new node
    }

    // Compare the word with current node, if less, go left
    if (word < node->key_word) {
        node->left = insertHelper(node->left, word);
    }
    // Go right if greater
    else if (word > node->key_word) {
        node->right = insertHelper(node->right, word);
    }
    else { // If it is equal add to the count
        node->freq++;
    }

    return node;
}





// Find the node containing 'word' or nullptr if not found
const TreeNode* BinSearchTree::findNode(const TreeNode* node, std::string_view word) noexcept {

    if (node == nullptr) {
        return nullptr; // Not found
    }

    // word found return the node
    if (word == node->key_word) {
        return node;
    }

    // Search left or right based on comparison
    if (word < node->key_word) {
        return findNode(node->left, word);
    }
    else {
        return findNode(node->right, word);
    }
}






// Format L v R where v will be the nodes value
void BinSearchTree::inorderHelper(const TreeNode* node,
                                  std::vector<std::pair<std::string, int>>& out) {

    // Null
    if (node == nullptr) {
        return;
    }
    // L: Traverse left subtree
    inorderHelper(node->left, out);

    // v: Visit node
    out.emplace_back(node->key_word, node->freq); // clion recommended emplace_back vs push_back

    // R: Traverse right subtree
    inorderHelper(node->right, out);

}

std::size_t BinSearchTree::sizeHelper(const TreeNode* node) noexcept {

    if (node == nullptr) {
        return 0;
    }
    // Add up 1 + left subtree's and right subtree
    return 1 + sizeHelper(node->left) + sizeHelper(node->right);
}

unsigned BinSearchTree::heightHelper(const TreeNode* node) noexcept {

    if (node == nullptr) {
        return 0;
    }

    // Root + the max height of left and right subtree (whichever is taller)
    return 1 + std::max(heightHelper(node->left), heightHelper(node->right));
}